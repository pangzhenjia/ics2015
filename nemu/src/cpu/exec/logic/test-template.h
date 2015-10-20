#include "cpu/exec/template-start.h"

#define instr test

void eflags_zspf(int val);

static void do_execute(){
    DATA_TYPE_S val = op_dest->val & op_src->val;
    eflags_zspf(val);
    cpu.cf = 0;
    cpu.of = 0;
    print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"
