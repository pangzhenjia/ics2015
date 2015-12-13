#include "cpu/exec/helper.h"

int mov_r2cr(swaddr_t eip){
    int len = decode_rm_l(eip + 1);
    uint8_t instr = instr_fetch(eip+1, 1);
    instr = (instr >> 3) & 7;
    if(instr == 0){
        cpu.cr0 = op_src -> val;
    }
    else if(instr == 3){
        cpu.cr3 = op_src -> val;
    }
    else {
        Assert(0, "eip: 0x%x\nmov_r2cr %d fault!\n", cpu.eip, instr);
    }
    return len+1;
}

#define DATA_BYTE 4
#include "cpu/exec/template-start.h"

int mov_cr2r(swaddr_t eip){
    int len = decode_rm_l(eip + 1);
    uint8_t instr = instr_fetch(eip+1, 1);
    instr = (instr >> 3) & 7;
    if(instr == 0){
        OPERAND_W(op_src, cpu.cr0);
    }
    else if(instr == 3){
        OPERAND_W(op_src, cpu.cr3);
    }
    else {
        Assert(0, "eip: 0x%x\nmov_cr2r %d fault!\n", cpu.eip, instr);
    }
        
    return len+1;
}

#include "cpu/exec/template-end.h"
#undef DATA_BYTE
