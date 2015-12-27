#include "cpu/exec/helper.h"

int popa(swaddr_t eip){

    cpu.edi = swaddr_read(cpu.esp, 4, SR_SS);
    cpu.esp += 4;

    cpu.esi = swaddr_read(cpu.esp, 4, SR_SS);
    cpu.esp += 4;

    cpu.ebp = swaddr_read(cpu.esp, 4, SR_SS);
    cpu.esp += 4;
    
    /* throw away esp */
    cpu.esp += 4;

    cpu.ebx = swaddr_read(cpu.esp, 4, SR_SS);
    cpu.esp += 4;

    cpu.edx = swaddr_read(cpu.esp, 4, SR_SS);
    cpu.esp += 4;

    cpu.ecx = swaddr_read(cpu.esp, 4, SR_SS);
    cpu.esp += 4;

    cpu.eax = swaddr_read(cpu.esp, 4, SR_SS);
    cpu.esp += 4;

    print_asm("popa");

    return 1;
}
