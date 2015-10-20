#include "cpu/exec/template-start.h"

#define instr push

static void do_execute(){
    DATA_TYPE val = op_src -> val;
    reg_l(R_ESP) -= DATA_BYTE;
    printf("val is 0x%x!\n", val); 
    MEM_W( reg_l(R_ESP), val);
}

make_instr_helper(i)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
make_instr_helper(rm)
#endif

#include "cpu/exec/template-end.h"
