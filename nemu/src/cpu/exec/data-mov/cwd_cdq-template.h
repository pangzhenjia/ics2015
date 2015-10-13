#include "cpu/exec/template-start.h"

make_helper(concat(cwd_cdq_r_, SUFFIX)){
    DATA_TYPE sign0 = 0;
    DATA_TYPE_S val = REG(R_AX);
    if(val < 0){
        REG(R_DX) = ~sign0;
    }
    else{
        REG(R_DX) = sign0;
    }
    return 1;
}

#include "cpu/exec/template-end.h"
