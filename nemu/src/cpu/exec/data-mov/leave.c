#include "cpu/exec/helper.h"

int leave_r_l(swaddr_t eip){
    cpu.esp = cpu.ebp;
    cpu.ebp = swaddr_read(cpu.esp, 4);
    cpu.esp += 4;
    return 1;
}
