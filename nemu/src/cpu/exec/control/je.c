#include "cpu/exec/helper.h"
#include "cpu/helper.h"
#include "cpu/decode/decode.h"

int je_i2r_b(swaddr_t eip){
    int len = decode_i_b(eip + 1);
    len += 1;
    if (cpu.zf == 1){
        int val = op_src -> val;
        return len + val;
    }
    return len;
}

