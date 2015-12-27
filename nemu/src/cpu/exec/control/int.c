#include "cpu/exec/helper.h"
#include "int_raise.h"

void raise_intr(uint8_t );

int int80(swaddr_t eip){
   
    /* push eflags */
    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, SR_SS, cpu.eflags);

    cpu.If = 0;
    cpu.tf = 0;

    /* push CS */
    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, SR_SS, cpu.Sreg[SR_CS].val);

    /* push eip */
    cpu.esp -= 4;
    swaddr_write(cpu.esp, 4, SR_SS, cpu.eip + 2);

    print_asm("int80");

    int NO = instr_fetch(eip+1, 1);
    raise_intr(NO);

    return 0;
}

