#include "common.h"
#include "nemu.h"

extern uint32_t tlb_translate(lnaddr_t addr);

uint32_t page_translate(lnaddr_t addr, size_t len){
    /* if data cross the page boundary */
    //if ((addr % PAGE_SIZE) + len > PAGE_SIZE){
        Assert(0, "eip: 0x%x\ndata cross the page boundary!\n", cpu.eip);
    //}

    /* no page mode */
    if(!(cpu.CR0.pe == 1 && cpu.CR0.pg == 1)){
        return addr;
    }

    /* page translate */
    uint32_t hw_addr = tlb_translate(addr);
    
    return hw_addr;
}
