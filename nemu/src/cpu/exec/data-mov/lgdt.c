#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"

int lgdt_rm2r_l(swaddr_t eip){
    ModR_M m;
    m.val = instr_fetch(eip+1, 1);
    int len = load_addr(eip+1, &m, op_src);

    uint32_t addr  = op_src -> addr;
    uint16_t limit = lnaddr_read(addr, 2);
    uint32_t base  = lnaddr_read(addr + 2, 4);

    cpu._gdtr.limit = limit / 8;
    cpu._gdtr.base = base;
    return len+1;
}

int lgdt_rm2r_w(swaddr_t eip){
    Assert(0, "lgdt is not defined");
    return 6;
}

make_helper_v(lgdt_rm2r)
    
