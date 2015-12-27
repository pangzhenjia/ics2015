#include "cpu/exec/helper.h"

int pusha(swaddr_t eip){

    /* push all the gpr */
    uint32_t temp = cpu.esp;

    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, SR_SS, cpu.eax);

    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, SR_SS, cpu.ecx);

    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, SR_SS, cpu.edx);

    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, SR_SS, cpu.ebx);

    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, SR_SS, temp);

    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, SR_SS, cpu.ebp);

    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, SR_SS, cpu.esi);

    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, SR_SS, cpu.edi);

    print_asm("pusha");

    return 1;
}

