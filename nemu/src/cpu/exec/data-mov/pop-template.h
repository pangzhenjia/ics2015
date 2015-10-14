#include "cpu/exec/template-start.h"

#define instr pop

static void do_execute(){
    int val = MEM_R(reg_l(R_ESP));
    OPERAND_W(op_src, val);
    reg_l(R_ESP) += DATA_BYTE;
}

make_instr_helper(r)
make_instr_helper(rm)

#include "cpu/exec/template-end.h"
