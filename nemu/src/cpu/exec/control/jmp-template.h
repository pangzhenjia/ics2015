#include "cpu/exec/template-start.h"

#define instr jmp

make_helper(concat(jmp_si_, SUFFIX)){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    DATA_TYPE_S val0 = op_src->val;
    int val = val0;
    return len + val + 1;
}

#if DATA_BYTE == 2 || DATA_BYTE == 4

make_helper(concat(jmp_rm_, SUFFIX)){
    concat(decode_rm_, SUFFIX)(eip + 1);
    DATA_TYPE val = (DATA_TYPE)op_src->val;
    cpu.eip = val;
    return 0;
}

#endif

#include "cpu/exec/template-end.h"
