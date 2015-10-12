#include "cpu/exec/helper.h"
#include "cpu/helper.h"
#include "cpu/decode/decode.h"
#include "eflags.h"

int test_rm2r_w(swaddr_t eip);
int test_rm2r_l(swaddr_t eip);

make_helper_v(test_rm2r)
static void do_test_l();

int test_rm2r_w(swaddr_t eip){
    return 1;
}

int test_rm2r_l(swaddr_t eip){
    return idex(eip, decode_rm_l, do_test_l);
}

static void do_test_l(){
    int val = op_src -> val;
    int result = val & val;
    //CF OF
    cpu.cf = 0;
    cpu.of = 0;
    eflags_zspf(result);
    printf("ZF is %d!\n", cpu.zf);
}
