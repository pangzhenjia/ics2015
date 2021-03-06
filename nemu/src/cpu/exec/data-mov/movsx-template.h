#include "cpu/exec/template-start.h"

make_helper(concat(movsx_b_rm2r_, SUFFIX)) {
    int len = decode_rm2r_b(eip + 1);
    char val0 = op_src->val;
    DATA_TYPE_S val = (DATA_TYPE_S)val0;
    REG(op_dest->reg) = val;

#define instr movsx
    print_asm_template2();
#undef instr

    return len + 1;
}

#if DATA_BYTE == 4
make_helper(movsx_w_rm2r_l){
    int len = decode_rm2r_w(eip + 1);
    int val = (int)(op_src->val & 0xffff);
    reg_l(op_dest->reg) = val;

#define instr movsx
    print_asm_template2();
#undef instr

    return len + 1;
}
#endif

#include "cpu/exec/template-end.h"
