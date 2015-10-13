#include "cpu/exec/template-start.h"

#define instr add
void eflags_zspf(int result);
void eflags_ocf_add(int val1, int val2);

static void do_execute(){
    DATA_TYPE val1 = op_src -> val;
    DATA_TYPE val2 = op_dest -> val;
    DATA_TYPE val = val1 + val2;
    eflags_zspf(val);
    eflags_ocf_add(val1, val2);
    OPERAND_W(op_dest, val);
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif

#include "cpu/exec/template-end.h"
