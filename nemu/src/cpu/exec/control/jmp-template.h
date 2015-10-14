#include "cpu/exec/template-start.h"

#define instr jmp

make_helper(concat(jmp_i_, SUFFIX)){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    int val = op_src->val;
    return len + val + 1;
}

#if DATA_BYTE == 2 || DATA_BYTE == 4

make_helper(concat(jmp_rm_, SUFFIX)){
    concat(decode_rm_, SUFFIX)(eip + 1);
    DATA_TYPE val = (DATA_TYPE)op_src->val;
    return val - eip;
}

#endif

#include "cpu/exec/template-end.h"
