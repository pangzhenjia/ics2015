#include "cpu/exec/template-start.h"

int concat(movs_, SUFFIX)(swaddr_t eip){
    DATA_TYPE val = MEM_R(reg_l(R_ESI));
    MEM_W(reg_l(R_EDI), val);
    
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
