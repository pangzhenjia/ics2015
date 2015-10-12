#include "cpu/exec/helper.h"
#include "cpu/helper.h"
#include "cpu/decode/decode.h"

int sub_i2rm_w(swaddr_t eip);
int sub_i2rm_l(swaddr_t eip);
int sub_i2rm_b(swaddr_t eip);
void eflags_zspf(int result);
void eflags_ocf_sub(int be_sub, int sub);

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
    //zf, sf, pf
    eflags_zspf(result);
    //of, cf
    eflags_ocf_sub(be_sub, sub);
    //printf("be_sub is 0x%x!\n", be_sub);
    //printf("sub is 0x%x!\n", sub);
    //printf("result is 0x%x!\n", result);
    //printf("esp is 0x%x!\n", cpu.esp);
}

