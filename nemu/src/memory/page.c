#include "common.h"
#include "nemu.h"
#include "x86-inc/mmu.h"

struct {
    uint32_t addr;
    union{
        uint32_t offset: 12;
        uint32_t page  : 10;
        uint32_t dir   : 10;
    };
}page_addr;

uint32_t page_translate(lnaddr_t addr, size_t len){
    /* if data cross the page boundary */
    if ((addr % PAGE_SIZE) + len > PAGE_SIZE){
        Assert(0, "data cross the page boundary!\n");
    }

    /* no page mode */
    if(!(cpu.CR0.pe == 1 && cpu.CR0.pg == 1)){
        return addr;
    }

    /* page translate */
    page_addr.addr = addr;
    uint32_t dir    = page_addr.dir;
    uint32_t page   = page_addr.page;
    uint32_t offset = page_addr.offset;
    
    uint32_t cr3_addr = (cpu.cr3 >> 12) << 12;

    uint32_t pde_addr = cr3_addr | (dir << 2);
    uint32_t pde_val = hwaddr_read(pde_addr, 4);
    PDE pde;
    pde.val = pde_val;

    uint32_t pte_addr = (pde.page_frame << 12) | (page << 2);
    uint32_t pte_val = hwaddr_read(pte_addr, 4);
    PTE pte; 
    pte.val = pte_val;

    uint32_t hw_addr = (pte.page_frame << 12) | offset;
    return hw_addr;
}