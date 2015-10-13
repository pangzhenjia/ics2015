#include "cpu/exec/template-start.h"
#include "add_adc_sub_sbb_cmp-macro-start.h"

void eflags_zspf(int result);
void concat(eflags_ocf_, add_sub_flags) (int val1, int val2);

static void do_execute(){
    DATA_TYPE val1 = op_dest -> val;
    DATA_TYPE val2 = op_src -> val;
    DATA_TYPE val = val1 add_sub_op (val2 + CF);
    eflags_zspf(val);
    printf("val is 0x%x! add_sub_op \n", val);
    concat(eflags_ocf_, add_sub_flags)(val1, val2);
#if instr == sub
    printf("write: instr !\n ");
    OPERAND_W(op_dest, val);
#endif
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif

#include "add_adc_sub_sbb_cmp-macro-end.h"
#include "cpu/exec/template-end.h"
