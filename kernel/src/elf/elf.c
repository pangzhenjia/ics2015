#include "common.h"
#include "memory.h"
#include <string.h>
#include <elf.h>

#define ELF_OFFSET_IN_DISK 0

#ifdef HAS_DEVICE
void ide_read(uint8_t *, uint32_t, uint32_t);
#else
void ramdisk_read(uint8_t *, uint32_t, uint32_t);
#endif

#define STACK_SIZE (1 << 20)

void create_video_mapping();
uint32_t get_ucr3();

uint32_t loader() {
	Elf32_Ehdr *elf;
	Elf32_Phdr *ph = NULL;

	uint8_t buf[4096];

#ifdef HAS_DEVICE
	ide_read(buf, ELF_OFFSET_IN_DISK, 4096);
#else
	ramdisk_read(buf, ELF_OFFSET_IN_DISK, 4096);
#endif

	elf = (void*)buf;

	/* TODO: fix the magic number with the correct one */
	//const uint32_t elf_magic = 0x7f454c46;
	//uint32_t *p_magic = (void *)buf;

	/* Load each program segment */
    ph = (Elf32_Phdr *)elf + elf->e_phoff;
    int i;
	for(i=0; i< elf->e_phnum; i++) {
		/* Scan the program header table, load each segment into memory */
		if(ph[i].p_type == PT_LOAD) {

			/* TODO: read the content of the segment from the ELF file 
			 * to the memory region [VirtAddr, VirtAddr + FileSiz)
			 */
            memcpy((void *)ph[i].p_vaddr, (void *)ph[i].p_offset, ph[i].p_filesz);
			if(ph[i].p_flags == PF_W){
                int size = ph[i].p_memsz - ph[i].p_filesz;
                char bss[size];
                int j;
                for(j=0; j<size; j++){
                    bss[j] = 0;
                }
                memcpy((void *)(ph[i].p_vaddr + ph[i].p_filesz), bss, size);
            }
			 
			/* TODO: zero the memory region 
			 * [VirtAddr + FileSiz, VirtAddr + MemSiz)
			 */


#ifdef IA32_PAGE
			/* Record the program break for future use. */
			extern uint32_t brk;
			uint32_t new_brk = ph[i].p_vaddr + ph[i].p_memsz - 1;
			if(brk < new_brk) { brk = new_brk; }
#endif
		}
	}

	volatile uint32_t entry = elf->e_entry;

#ifdef IA32_PAGE
	mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);

#ifdef HAS_DEVICE
	create_video_mapping();
#endif

	write_cr3(get_ucr3());
#endif

	return entry;
}
