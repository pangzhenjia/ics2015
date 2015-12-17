#include "cpu/exec/helper.h"

int lgdt_rm2r_l(swaddr_t eip){
    uint32_t addr  = instr_fetch(eip+2, 4);
    uint16_t limit = hwaddr_read(addr, 2);
    uint32_t base  = hwaddr_read(addr + 2, 4);

    cpu._gdtr.limit = limit / 8;
    cpu._gdtr.base = base;
    return 6;
}

int lgdt_rm2r_w(swaddr_t eip){
    Assert(0, "lgdt is not defined");
    return 6;
}

make_helper_v(lgdt_rm2r)
    
