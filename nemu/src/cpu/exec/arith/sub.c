#include "cpu/exec/helper.h"
#include "cpu/helper.h"
#include "cpu/decode/decode.h"

int sub_i2rm_w(swaddr_t eip);
int sub_i2rm_l(swaddr_t eip);
int sub_i2rm_b(swaddr_t eip);
void eflags_zspf(int result);

make_helper_v(sub_i2rm)
static int decode_i2rm_bi_lr(swaddr_t eip);
static void do_sub_l();

int sub_i2rm_w(swaddr_t eip){
    return 1;
}
int sub_i2rm_b(swaddr_t eip){
    return 1;
}

int sub_i2rm_l(swaddr_t eip){
    return idex(eip, decode_i2rm_bi_lr, do_sub_l);
}

static int decode_i2rm_bi_lr(swaddr_t eip){
    decode_i2rm_l(eip);
    decode_i_b(eip+1);
    return 2;
}


static void do_sub_l(){
    int sub = op_src -> val;
    int be_sub = op_dest -> val;
    int result = be_sub - sub;
    write_operand_l(op_dest, result);
    //for eflags setting
    eflags_zspf(result);
    //OF
    int sign1 = !((result >> 31) ^ ( be_sub >> 31));
    int sign2 = !((result >> 31) ^ ( sub >> 31));
    cpu.of = sign1 & sign2;
    //CF
    unsigned sub1 = sub;
    unsigned be_sub1 = be_sub;
    cpu.cf = be_sub1 < sub1;
    //printf("be_sub is 0x%x!\n", be_sub);
    //printf("sub is 0x%x!\n", sub);
    //printf("result is 0x%x!\n", result);
    //printf("esp is 0x%x!\n", cpu.esp);
}

