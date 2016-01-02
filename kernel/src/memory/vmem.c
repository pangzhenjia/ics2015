#include "common.h"
#include "x86.h"
#include "memory.h"
#include <string.h>

#define VMEM_ADDR 0xa0000
#define SCR_SIZE (320 * 200)

/* Use the function to get the start address of user page directory. */
inline PDE* get_updir();

//static PTE vptable[(VMEM_ADDR + SCR_SIZE) / PAGE_SIZE + 1]  align_to_page;

void create_video_mapping() {
	/* TODO: create an identical mapping from virtual memory area 
	 * [0xa0000, 0xa0000 + SCR_SIZE) to physical memory area 
	 * [0xa0000, 0xa0000 + SCR_SIZE) for user program. You may define
	 * some page tables to create this mapping.
	 */
/* 
    PDE *pdir = va_to_pa(get_updir());
    PTE *ptable = va_to_pa((PTE *)vptable);
    uint32_t addr = VMEM_ADDR;

    uint32_t nr_pt = (addr + SCR_SIZE) / PAGE_SIZE + 1;
    memset(ptable, 0, nr_pt * sizeof(PTE));
    
    uint32_t pdir_idx = addr >> 22;
    uint32_t pt_idx = (addr << 10) >> 22;

    if(pdir[pdir_idx].val != 0){
        PDE *pde = (PDE *)(pdir[pdir_idx].val & 0xfffff);
        memcpy(ptable, pde, nr_pt * sizeof(PTE));
    }

    pdir[pdir_idx].val = make_pde(ptable);

    int i;
    for(i=0; i< (SCR_SIZE / PAGE_SIZE)+1; i++){
        ptable[pt_idx + i].val = make_pte(addr);
        addr += PAGE_SIZE;
    }
*/
}

void video_mapping_write_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		buf[i] = i;
	}
}

void video_mapping_read_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		assert(buf[i] == i);
	}
}

void video_mapping_clear() {
	memset((void *)VMEM_ADDR, 0, SCR_SIZE);
}

