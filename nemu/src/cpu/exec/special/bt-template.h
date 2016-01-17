#include "cpu/exec/template-start.h"

#define instr bt

static void do_execute(){
    DATA_TYPE val = op_dest -> val;
    DATA_TYPE offset = op_src -> val;

    Assert(offset < 32, "offset is %d\n", offset);

    cpu.cf = (val >> offset) & 1;

    print_asm("btl %d 0x%x\n", offset, val);
}

make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"
