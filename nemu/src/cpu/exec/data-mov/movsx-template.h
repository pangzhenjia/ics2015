#include "cpu/exec/template-start.h"

make_helper(concat(movsx_b_rm2r_, SUFFIX)) {
    int len = decode_rm2r_b(eip + 1);
    int val = (int)op_src->val;
    printf("val is 0x%x!", val);
    REG(op_dest->reg) = val;
    return len + 1;
}

#if DATA_BYTE == 4
make_helper(movsx_w_rm2r_l){
    int len = decode_rm2r_w(eip + 1);
    int val = (int)(op_src->val & 0xffff);
    reg_l(op_dest->reg) = val;
    return len + 1;
}
#endif

#include "cpu/exec/template-end.h"
