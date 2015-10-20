#include "cpu/exec/helper.h"
#define DATA_BYTE 4
#include "cpu/exec/template-start.h"

int ret(swaddr_t eip){
    int val = MEM_R(reg_l(R_ESP));
    reg_l(R_ESP) += 4;
    printf("here!\n");
    cpu.eip = val;
    return 1;
}

int ret_i_w(swaddr_t eip){
    int val = MEM_R(reg_l(R_ESP));
    reg_l(R_ESP) += 4;
    val = val & 0xffff;
    return val - eip;
}

#include "cpu/exec/template-end.h"

