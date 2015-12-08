#include "cpu/exec/helper.h"

extern uint64_t decode_gdt(uint32_t index);

int ljmp(swaddr_t eip){
    uint32_t addr = instr_fetch(eip+1, 4);
    cpu.eip = addr;

    uint16_t cs = instr_fetch(eip+5, 2);
    cpu.Sreg[SR_CS].val = cs;
    
    uint32_t limit = decode_gdt(cpu.Sreg[SR_CS].index);
    uint32_t base  = decode_gdt(cpu.Sreg[SR_CS].index);
    printf("limit is 0x%x, base is 0x%x\n", limit, base);

    return 0;
}
