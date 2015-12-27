#include "cpu/exec/helper.h"

int fldz(swaddr_t eip){
    return 2;
}

int fstpl(swaddr_t eip){
    int len = decode_rm_l(eip+1);
    return len+1;
}
