#include "cpu/exec/helper.h"
#define DATA_BYTE 4
#include "cpu/exec/template-start.h"

int ret(swaddr_t eip){
    int val = MEM_R(reg_l(R_ESP));
    reg_l(R_ESP) += 4;
    cpu.eip = val;
    return 0;
}

int ret_i_w(swaddr_t eip){
    decode_i_w(eip + 1);
    short imm = op_src -> val;
    int val = MEM_R(reg_l(R_ESP));
    reg_l(R_ESP) += 4;
    reg_l(R_ESP) += imm;
    cpu.eip = val;
    return 0;
}

#include "cpu/exec/template-end.h"

