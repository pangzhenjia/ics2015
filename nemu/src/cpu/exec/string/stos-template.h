#include "cpu/exec/template-start.h"

int concat(stos_, SUFFIX)(swaddr_t eip){
    DATA_TYPE val = REG(R_EAX);
    MEM_W(reg_l(R_EDI), val);
    reg_l(R_EDI) += DATA_BYTE;
    return 1;
}

#include "cpu/exec/template-end.h"
