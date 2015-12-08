#include "cpu/exec/helper.h"

int lgdt_rm2r_l(swaddr_t eip){
    cpu._gdtr.limit = instr_fetch(eip, 2);
    cpu._gdtr.base  = instr_fetch(eip+2, 4);
    return 6;
}

int lgdt_rm2r_w(swaddr_t eip){
    Assert(0, "lgdt is not defined");
    return 6;
}

make_helper_v(lgdt_rm2r)
    
