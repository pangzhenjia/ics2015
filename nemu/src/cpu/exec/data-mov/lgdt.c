#include "cpu/exec/helper.h"

int lgdt_rm2r_l(swaddr_t eip){
    uint32_t addr = instr_fetch(eip+1, 4);
    uint32_t val_limit = swaddr_read(addr, 2);
    uint32_t val_base  = swaddr_read(addr+2, 4);
    cpu._gdtr.limit = val_limit;
    cpu._gdtr.base  = val_base;
    return 5;
}

int lgdt_rm2r_w(swaddr_t eip){
    Assert(0, "lgdt is not defined");
    return 5;
}

make_helper_v(lgdt_rm2r)
    
