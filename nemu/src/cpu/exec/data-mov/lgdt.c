#include "cpu/exec/helper.h"

int lgdt_rm2r_l(swaddr_t eip){
    int len = decode_rm_w(eip + 1);
    uint32_t val_limit = op_src->val;
    uint32_t val_base  = swaddr_read(op_src->addr+2, 4);
    cpu._gdtr.limit = val_limit;
    cpu._gdtr.base  = val_base;
    return len+1;
}

int lgdt_rm2r_w(swaddr_t eip){
    Assert(0, "lgdt is not defined");
    return 5;
}

make_helper_v(lgdt_rm2r)
    
