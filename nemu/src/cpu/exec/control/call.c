#include "cpu/exec/helper.h"
#include "cpu/helper.h"
#include "cpu/decode/decode.h"

void do_push_l_eip(swaddr_t eip);
int call_i_w(swaddr_t eip);
int call_i_l(swaddr_t eip);

make_helper_v(call_i)
void do_push_l_eip(swaddr_t eip);

int call_i_w(swaddr_t eip){
    return 1;
}

int call_i_l(swaddr_t eip){
    do_push_l_eip(eip + 5);
    int len = decode_i_l(eip + 1);
    len += 1; // opcode
    int val = op_src -> val;
    return len + val;
}


