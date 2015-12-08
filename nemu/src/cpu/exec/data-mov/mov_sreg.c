#include "cpu/exec/helper.h"

uint32_t decode_gdt(uint32_t index, size_t len);

int mov_rm2sr(swaddr_t eip){
    /* decode rm */
    int len = decode_rm_w(eip + 1);

    /* decode sreg */
    uint8_t addr = instr_fetch(eip + 1, 1);
    int sr_index = (addr << 2) >> 5;
    cpu.Sreg[sr_index].val = op_src -> val;

    /* decode sreg */
    uint32_t seg_base = decode_gdt(cpu.Sreg[sr_index].index, 4);
    cpu.sr_cache[sr_index].base = seg_base;

    return len+1;
}
