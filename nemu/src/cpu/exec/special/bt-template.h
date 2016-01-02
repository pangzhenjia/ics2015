#include "cpu/exec/template-start.h"

#define instr bt

static void do_execute(){
    DATA_TYPE val = op_src -> val;
    DATA_TYPE offset = op_dest -> val;

    Assert(offset < 32, "offset is %d\n", offset);

    val = (val >> offset) & 1;
    cpu.cf = val;

    print_asm_template2();
}

make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"
