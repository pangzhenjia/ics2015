#include "cpu/exec/helper.h"

int ljmp(swaddr_t eip){
    uint16_t cs = instr_fetch(eip+1, 2);
    cpu.Sreg[SR_CS].val = cs;

    uint32_t addr = instr_fetch(eip+3, 4);
    cpu.eip = addr;

    return 0;
}
