#include "cpu/exec/helper.h"
#include "cpu/helper.h"
#include "cpu/decode/decode.h"
#include "sub.h"

int cmp_i2rm_w(swaddr_t eip);
int cmp_i2rm_l(swaddr_t eip);
void eflags_zspf(int result);
void eflags_ocf_sub(int be_sub, int sub);
void do_cmp_l();
int decode_i2rm_bi_lr(swaddr_t eip);

make_helper_v(cmp_i2rm);

int cmp_i2rm_w(swaddr_t eip){
    return 1;
}

int cmp_i2rm_l(swaddr_t eip){
    return idex(eip, decode_i2rm_bi_lr, do_cmp_l);
}

void do_cmp_l(){
    int val1 = op_src -> val;
    int val2 = op_dest -> val;
    int result = val1 - val2;
    //for flags setting
    //zf, sf, pf
    eflags_zspf(result);
    //of, cf
    eflags_ocf_sub(val1, val2);
}
