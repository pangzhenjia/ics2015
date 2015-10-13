#include "cpu/exec/template-start.h"


#if DATA_BYTE == 2 || DATA_BYTE == 4

make_helper(concat(call_i_, SUFFIX)){
    reg_l(R_ESP) -= DATA_BYTE;
    MEM_W(reg_l(R_ESP), eip + DATA_BYTE + 1);
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    int val = op_src -> val;
    return len + val + 1;
}

#endif

#include "cpu/exec/template-end.h"
