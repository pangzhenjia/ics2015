#include "common.h"
#include "nemu.h"

uint64_t decode_gdt(uint32_t index){

    Assert(index < cpu._gdtr.limit, "index 0x%x in gdtr is out of range!", index);
    uint32_t base = cpu._gdtr.base;
    uint32_t addr = base + index * 8;
    
    uint32_t val1 = lnaddr_read(addr, 4);
    uint32_t base1 = val1 >> 16;
    uint32_t limit1 = val1 & 0xffff;

    uint32_t val2 = lnaddr_read(addr + 4, 4);
    uint32_t base2 = val2 & 0xff;
    base2 = base2 << 16;
    uint32_t base3 = val2 & 0xff000000;
    uint32_t limit2 = val2 & 0xf0000;

    uint32_t seg_base = (base1 | base2 | base3);
    uint32_t seg_limit = limit1 | limit2;

    uint64_t base_limit = seg_base;
    base_limit = (base_limit << 32) | seg_limit;
    return base_limit; 
}



uint32_t seg_translate(swaddr_t addr, size_t len, uint8_t sreg){
    /* do some check */
    Assert(sreg < 4, "sreg %d is out of range!", sreg);
    Assert(cpu.Sreg[sreg].rpl == 0, "privilege %d fault!", cpu.Sreg[sreg].rpl);
    /* we assume all the privilege is 0 ring */

    if(cpu.CR0.pe == 0){ return addr; }

    uint32_t index = cpu.Sreg[sreg].index;

    uint64_t base_limit = decode_gdt(index);
    uint32_t seg_base = base_limit >> 32;

    return addr + seg_base;
}


