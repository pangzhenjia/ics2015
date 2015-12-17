#include "cpu/exec/helper.h"

int std(swaddr_t eip){
    cpu.df = 1;
    return 1;
}
