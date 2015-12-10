#include "cpu/exec/helper.h"

extern uint64_t decode_gdt(uint32_t index);

int ljmp(swaddr_t eip){
    uint32_t addr = instr_fetch(eip+1, 4);
    cpu.eip = addr;

    uint16_t cs = instr_fetch(eip+5, 2);
    cpu.Sreg[SR_CS].val = cs;
    
    return 0;
}
