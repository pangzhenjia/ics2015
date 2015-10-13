#include "cpu/exec/helper.h"
#define DATA_BYTE 1
#include "cpu/exec/template-start.h"

int seta_rm_b(swaddr_t eip){
    int len = decode_rm_b(eip + 1);
    if((cpu.cf == 0) && (cpu.zf == 0)){
        OPERAND_W(op_src, 1);
    }
    else { OPERAND_W(op_src, 0); }
    return len + 1;
}

#undef DATA_BYTE
#include "cpu/exec/template-end.h"
