#include "cpu/exec/helper.h"

uint64_t decode_gdt(uint32_t index);

int mov_rm2sr(swaddr_t eip){
    /* decode rm */
    int len = decode_rm_w(eip + 1);

    /* decode sreg */
    uint8_t addr = instr_fetch(eip + 1, 1);
    int sr_index = (addr << 2) >> 5;
    cpu.Sreg[sr_index].val = op_src -> val;

    /* decode sreg */
    uint64_t base_limit = decode_gdt(cpu.Sreg[sr_index].index);
    cpu.Sreg[sr_index].base = base_limit >> 32;
    cpu.Sreg[sr_index].limit = (base_limit << 32) >> 32;

    return len+1;
}
