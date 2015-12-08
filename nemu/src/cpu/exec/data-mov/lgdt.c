#include "cpu/exec/helper.h"

int lgdt_rm2r_l(swaddr_t eip){
    printf("yes!\n");
    uint32_t addr = instr_fetch(eip+1, 4);
    addr >>= 8;
    cpu._gdtr.limit = hwaddr_read(addr, 2);
    cpu._gdtr.base  = hwaddr_read(addr+2, 4);
    return 4;
}

int lgdt_rm2r_w(swaddr_t eip){
    Assert(0, "lgdt is not defined");
    return 5;
}

make_helper_v(lgdt_rm2r)
    
