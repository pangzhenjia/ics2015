#include "cpu/exec/helper.h"
#include "cpu/helper.h"
#include "cpu/decode/decode.h"

int je_rm2r_b(swaddr_t eip){
    int len = decode_rm_b(eip + 1);
    if (cpu.zf == 0){
        int val = op_src -> val;
        eip += val;
        printf("je: the next eip is 0x%x!\n", eip);
    }
    return len + 1;
}

