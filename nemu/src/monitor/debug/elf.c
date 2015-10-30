#include "common.h"
#include "nemu.h"
#include <stdlib.h>
#include <elf.h>

char *exec_file = NULL;

static char *strtab = NULL;
static Elf32_Sym *symtab = NULL;
static int nr_symtab_entry;

void load_elf_tables(int argc, char *argv[]) {
	int ret;
	Assert(argc == 2, "run NEMU with format 'nemu [program]'");
	exec_file = argv[1];

	FILE *fp = fopen(exec_file, "rb");
	Assert(fp, "Can not open '%s'", exec_file);

	uint8_t buf[4096];
	/* Read the first 4096 bytes from the exec_file.
	 * They should contain the ELF header and program headers. */
	ret = fread(buf, 4096, 1, fp);
	assert(ret == 1);

	/* The first several bytes contain the ELF header. */
	Elf32_Ehdr *elf = (void *)buf;
	char magic[] = {ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3};

	/* Check ELF header */
	assert(memcmp(elf->e_ident, magic, 4) == 0);		// magic number
	assert(elf->e_ident[EI_CLASS] == ELFCLASS32);		// 32-bit architecture
	assert(elf->e_ident[EI_DATA] == ELFDATA2LSB);		// littel-endian
	assert(elf->e_ident[EI_VERSION] == EV_CURRENT);		// current version
	assert(elf->e_ident[EI_OSABI] == ELFOSABI_SYSV || 	// UNIX System V ABI
			elf->e_ident[EI_OSABI] == ELFOSABI_LINUX); 	// UNIX - GNU
	assert(elf->e_ident[EI_ABIVERSION] == 0);			// should be 0
	assert(elf->e_type == ET_EXEC);						// executable file
	assert(elf->e_machine == EM_386);					// Intel 80386 architecture
	assert(elf->e_version == EV_CURRENT);				// current version


	/* Load symbol table and string table for future use */

	/* Load section header table */
	uint32_t sh_size = elf->e_shentsize * elf->e_shnum;
	Elf32_Shdr *sh = malloc(sh_size);
	fseek(fp, elf->e_shoff, SEEK_SET);
	ret = fread(sh, sh_size, 1, fp);
	assert(ret == 1);

	/* Load section header string table */
	char *shstrtab = malloc(sh[elf->e_shstrndx].sh_size);
	fseek(fp, sh[elf->e_shstrndx].sh_offset, SEEK_SET);
	ret = fread(shstrtab, sh[elf->e_shstrndx].sh_size, 1, fp);
	assert(ret == 1);

	int i;
	for(i = 0; i < elf->e_shnum; i ++) {
		if(sh[i].sh_type == SHT_SYMTAB && 
				strcmp(shstrtab + sh[i].sh_name, ".symtab") == 0) {
			/* Load symbol table from exec_file */
			symtab = malloc(sh[i].sh_size);
			fseek(fp, sh[i].sh_offset, SEEK_SET);
			ret = fread(symtab, sh[i].sh_size, 1, fp);
			assert(ret == 1);
			nr_symtab_entry = sh[i].sh_size / sizeof(symtab[0]);
		}
		else if(sh[i].sh_type == SHT_STRTAB && 
				strcmp(shstrtab + sh[i].sh_name, ".strtab") == 0) {
			/* Load string table from exec_file */
			strtab = malloc(sh[i].sh_size);
			fseek(fp, sh[i].sh_offset, SEEK_SET);
			ret = fread(strtab, sh[i].sh_size, 1, fp);
			assert(ret == 1);
		}
	}

	free(sh);
	free(shstrtab);

	assert(strtab != NULL && symtab != NULL);

	fclose(fp);
}

uint32_t data_addr(char *argv){
    int i;
    for (i = 0; i < nr_symtab_entry; i++){
        if((symtab[i].st_info & 0xf) == STT_OBJECT){
            uint32_t name_val = symtab[i].st_name;
            if(strcmp(argv, strtab+name_val) == 0){
                return symtab[i].st_value;
            }
        }
    }
    printf("Can not find the the value %s\n", argv);
    return 0;
}

typedef struct {
    swaddr_t prev_ebp;
    swaddr_t ret_addr;
    uint32_t args[4];
} PartOfStackFrame;
PartOfStackFrame stack_frame;


char *get_str(swaddr_t eip){
    int i;
    for(i = 0; i < nr_symtab_entry; i++){
        if((symtab[i].st_info & 0xf) == STT_FUNC){
            uint32_t addr = symtab[i].st_value ;
            uint32_t val  = eip - addr;
            if(val > 0 && val < symtab[i].st_size){
                uint32_t name_addr = symtab[i].st_name;
                char *e = (char *)(strtab + name_addr);
                return e;
            }
        }
    }
    return NULL;
}

void print_bt(int i){
    char *name = get_str(stack_frame.ret_addr);
    if(strcmp(name, "main") != 0){
        printf("#%d   0x%08x in %s (0x%08x, 0x%08x, 0x%08x, 0x%08x)\n", i, stack_frame.ret_addr, name, stack_frame.args[0],  stack_frame.args[1], stack_frame.args[2], stack_frame.args[3]);
    }
    else{
        printf("#%d   0x%08x in %s ( )\n", i, stack_frame.ret_addr, name);
    }
}

void init_stack(swaddr_t eip, uint32_t ebp){
    stack_frame.prev_ebp = ebp;
    stack_frame.ret_addr = eip;
    printf("eip is 0x%08x\n", eip);
    if(eip == 0x100000){ 
        printf("The program has not runed.\n");
        assert(0);
    }
    int i = 0;
    for(i = 0; i < 4; i++){
        stack_frame.args[i] = swaddr_read(ebp + 8 + 4*i, 4);
    }
}

int reset_stack(){
    uint32_t ebp = swaddr_read(stack_frame.prev_ebp, 4);
    printf("ebp is 0x%08x\n", ebp);
    if(ebp == 0){ return 0; }
    if(swaddr_read(ebp, 4) == 0){ return 1; }
    stack_frame.prev_ebp = ebp;
    stack_frame.ret_addr = swaddr_read(ebp + 4, 4);
    int i;
    for(i = 0; i < 4; i++){
        stack_frame.args[i] = swaddr_read(ebp + 8 + 4*i, 4);
    }
    return 1;
}
    

void stack_bt(swaddr_t eip, uint32_t ebp){

    /* initialize the stack_frame */
    init_stack(eip, ebp);

    /* print out the current state */
    int i = 0;
    print_bt(i);

    /* print out all the pre stack state */
    for(i = 1; ; i++){
        int reset = reset_stack();
        if( reset == 0 ){ break; }
        print_bt(i);
    }
}





