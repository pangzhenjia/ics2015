#include "cpu/exec/helper.h"
#include "int_raise.h"

void raise_intr(uint8_t );

int int80(swaddr_t eip){

    int NO = instr_fetch(eip+1, 1);
    cpu.eip += 2;

    raise_intr(NO);

    return 0;
}

