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

void eflags_ocf_sub(int be_sub, int sub){
    int result = be_sub - sub;
    int sign1 = !!((result >> 31) ^ ( be_sub >> 31));
    int sign2 = !!((result >> 31) ^ ( sub >> 31));
    cpu.of = sign1 & sign2;
    //for CF
    unsigned sub1 = sub;
    unsigned be_sub1 = be_sub;
    cpu.cf = be_sub1 < sub1;
}
