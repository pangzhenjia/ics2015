#include "cpu/exec/template-start.h"

void eflags_zspf(int val);
void eflags_ocf_sub(int val1, int val2);

int concat(cmps_, SUFFIX)(swaddr_t eip){
    DATA_TYPE_S val10 = MEM_R(reg_l(R_ESI));
    DATA_TYPE_S val20 = MEM_R(reg_l(R_EDI));
    int val1 = val10;
    int val2 = val20;
    eflags_zspf(val1 - val2);
    eflags_ocf_sub(val1, val2);

    if(cpu.df == 0){
        reg_l(R_ESI) += DATA_BYTE;
        reg_l(R_EDI) += DATA_BYTE;
    }
    else{
        reg_l(R_ESI) -= DATA_BYTE;
        reg_l(R_EDI) -= DATA_BYTE;
    }

    return 1;
}

#include "cpu/exec/template-end.h"


