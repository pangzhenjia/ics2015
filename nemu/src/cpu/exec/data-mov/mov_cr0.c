#include "cpu/exec/helper.h"

int mov_to_cr0(swaddr_t eip){
    int len = decode_r_l(eip + 1);
    cpu.cr0 = op_src -> val;
    return len+1;
}

#define DATA_BYTE 4
#include "cpu/exec/template-start.h"

int mov_from_cr0(swaddr_t eip){
    int len = decode_r_l(eip + 1);
    OPERAND_W(op_src, cpu.cr0);
    return len+1;
}

#include "cpu/exec/template-end.h"
#undef DATA_BYTE
