#include "cpu/exec/template-start.h"

void pio_write(ioaddr_t addr, size_t len, uint32_t data);

int concat(out_a2imm_, SUFFIX)(swaddr_t eip){
    uint8_t ioaddr = instr_fetch(eip+1, 1);
    DATA_TYPE val = REG(R_EAX);
    pio_write(ioaddr, DATA_BYTE, val);
    
    print_asm("out 0x%x", val);

    return 2;
}


int concat(out_a2d_, SUFFIX)(swaddr_t eip){
    uint16_t ioaddr = cpu.dx;
    DATA_TYPE val = REG(R_EAX);
    pio_write(ioaddr, DATA_BYTE, val);

    print_asm("out 0x%x", val);

    return 1;
}

#include "cpu/exec/template-end.h"

    
