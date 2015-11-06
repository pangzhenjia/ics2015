#include "cpu/exec/template-start.h"

make_helper(concat(call_i_, SUFFIX)){
    reg_l(R_ESP) -= DATA_BYTE;
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    MEM_W(reg_l(R_ESP), eip + len + 1);
    int val = op_src -> val;
    cpu.eip += val;
    return len + 1;
}

make_helper(concat(call_rm_, SUFFIX)){
    reg_l(R_ESP) -= DATA_BYTE;
    int len = concat(decode_rm_, SUFFIX)(eip + 1);
    MEM_W(reg_l(R_ESP), eip + len + 1);
    DATA_TYPE val = (DATA_TYPE)op_src -> val;
    cpu.eip = val;
    return 0;
}


#include "cpu/exec/template-end.h"
