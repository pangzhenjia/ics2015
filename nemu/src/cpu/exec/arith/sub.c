#include "cpu/exec/helper.h"
#include "cpu/helper.h"
#include "cpu/decode/decode.h"
int sub_i2rm_w(swaddr_t eip);
int sub_i2rm_l(swaddr_t eip);

make_helper_v(sub_i2rm)
static void do_sub_l();

int sub_i2rm_w(swaddr_t eip){
    return 1;
}

int sub_i2rm_l(swaddr_t eip){
    return idex(eip, decode_i2rm_l, do_sub_l);
}

static void do_sub_l(){
    int sub = op_src -> val;
    int be_sub = op_dest -> val;
    int result = be_sub - sub;
    write_operand_l(op_dest, result);
    //for eflags setting
    //ZF
    if(result == 0){ cpu.zf = 0; }
    //OF
    int sign1 = !((result >> 31) ^ ( be_sub >> 31));
    int sign2 = !((result >> 31) ^ ( sub >> 31));
    cpu.of = sign1 & sign2;
    //SF
    cpu.sf = (result >> 31) & 1;
    //CF
    unsigned sub1 = sub;
    unsigned be_sub1 = be_sub;
    cpu.cf = be_sub1 < sub1;
    //PF
    int last_bit = result & 0xff;
    int val4 = last_bit ^ (last_bit >> 4);
    int val2 = val4 ^ (val4 >> 2);
    int val1 = val2 ^ (val2 >> 1);
    cpu.pf = !val1;
    printf("be_sub is 0x%x!\n", be_sub);
    printf("sub is 0x%x!\n", sub);
    printf("result is 0x%x!\n", result);
    printf("esp is 0x%x!\n", cpu.esp);
}

