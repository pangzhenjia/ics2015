#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"

int igdt_rm2r_l(swaddr_t eip){
    ModR_M m;
    m.val = instr_fetch(eip+1, 1);
    int len = load_addr(eip+1, &m, op_src);

    uint32_t addr  = op_src -> addr;
    uint16_t limit = lnaddr_read(addr, 2);
    uint32_t base  = lnaddr_read(addr + 2, 4);

    cpu._idtr.limit = limit / 8;
    cpu._idtr.base = base;
    return len+1;
}

