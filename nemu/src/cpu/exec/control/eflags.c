#include "cpu/exec/helper.h"
#include "cpu/helper.h"

void eflags_zspf(int result){
    //ZF
    cpu.zf = !result;
    //SF
    cpu.sf = (result >> 31) & 1;
    //PF
    int last_bit = result & 0xff;
    int val4 = last_bit ^ (last_bit >> 4);
    int val2 = val4 ^ (val4 >> 2);
    int val1 = val2 ^ (val2 >> 1);
    cpu.pf = !val1;
}
