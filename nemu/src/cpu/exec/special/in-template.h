#include "cpu/exec/template-start.h"
#include "device/port-io.h"


int concat(in_imm2a_, SUFFIX)(swaddr_t eip){
    uint8_t ioaddr = instr_fetch(eip+1, 1);
    DATA_TYPE val = pio_read(ioaddr, DATA_BYTE);
    REG(R_EAX) = val;
    
    print_asm("in 0x%x 2 eax", val);

    return 2;
}


int concat(in_d2a_, SUFFIX)(swaddr_t eip){
    uint16_t ioaddr = cpu.dx;
    DATA_TYPE val = pio_read(ioaddr, DATA_BYTE);
    REG(R_EAX) = val;

    print_asm("in 0x%x 2 eax", val);

    return 1;
}

#include "cpu/exec/template-end.h"

    
