#include "cpu/exec/helper.h"
#include "cpu/helper.h"
#include "cpu/decode/decode.h"

int push_i2rm_w(swaddr_t eip);
int push_i2rm_l(swaddr_t eip);

make_helper_v(push_i2rm);
static void do_push_l_r();

int push_i2rm_w(swaddr_t eip){
    return 1;
}

int push_i2rm_l(swaddr_t eip){
    return idex(eip, decode_r_l, do_push_l_r);
}


static void do_push_l_r(){
    int val = op_src -> val;
    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, val);
}

void do_push_l_eip(swaddr_t eip){
    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, eip);
}
