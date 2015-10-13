#include "cpu/exec/template-start.h"

#define instr dec

void eflags_zspf(int result);
void eflags_ocf_sub(int val1, int val2);

static void do_execute () {
	DATA_TYPE result = op_src->val - 1;
	OPERAND_W(op_src, result);

	/* TODO: Update EFLAGS. */
    eflags_zspf(result);
    eflags_ocf_sub(op_src->val, 1);

	print_asm_template1();
}

make_instr_helper(rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
#endif

#include "cpu/exec/template-end.h"
