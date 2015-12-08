#include "cpu/exec/helper.h"

int mov_r2cr0(swaddr_t eip){
    int len = decode_rm_l(eip + 1);
    cpu.cr0 = op_src -> val;
	print_asm_template2();
    return len+1;
}

#define DATA_BYTE 4
#include "cpu/exec/template-start.h"

int mov_cr02r(swaddr_t eip){
    int len = decode_rm_l(eip + 1);
    OPERAND_W(op_src, cpu.cr0);
	print_asm_template2();
    return len+1;
}

#include "cpu/exec/template-end.h"
#undef DATA_BYTE
