#include "cpu/exec/helper.h"

uint64_t decode_gdt(uint32_t );

int iret(swaddr_t eip){

    /* pop eip */
    cpu.eip = swaddr_read(cpu.esp, 4, SR_SS);
    cpu.esp += 4;

    /* pop CS */
    cpu.Sreg[SR_CS].val = swaddr_read(cpu.esp, 4, SR_SS);
    cpu.esp += 4;
    
    /* update CS cache */
    uint64_t base_limit = decode_gdt(cpu.Sreg[SR_CS].index);
    cpu.Sreg[SR_CS].base = base_limit >> 32;
    cpu.Sreg[SR_CS].limit = base_limit & 0xffffffff;

    /* pop eflags */
    cpu.eflags = swaddr_read(cpu.esp, 4, SR_SS);
    cpu.esp += 4;

    print_asm("iret");

    return 0;
}
