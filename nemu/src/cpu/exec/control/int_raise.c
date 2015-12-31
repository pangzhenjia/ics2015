#include "cpu/exec/helper.h"
#include <setjmp.h>
extern jmp_buf jbuf;

uint64_t decode_gdt(uint32_t index);

void raise_intr(uint8_t NO){

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

    print_asm("int 0x%x", NO);

    /* decode int */
    Assert(NO <= cpu._idtr.limit, "NO %d in idtr is out of range!\n", NO);
    uint32_t base = cpu._idtr.base;
    uint32_t addr = base + NO * 8;

    uint32_t val1 = lnaddr_read(addr, 4);
    uint16_t selector = val1 >> 16;
    uint32_t offset1 = val1 & 0xffff;

    cpu.Sreg[SR_CS].val = selector;
    
    uint32_t val2 = lnaddr_read(addr+4, 4);
    uint32_t offset2 = val2 >> 16;
    
    uint32_t offset = (offset2 << 16) | offset1;

    uint64_t base_limit = decode_gdt(cpu.Sreg[SR_CS].index);
    cpu.Sreg[SR_CS].base = base_limit >> 32;
    cpu.Sreg[SR_CS].limit = base_limit & 0xffffffff;

    cpu.eip = cpu.Sreg[SR_CS].base + offset;

    /* directly jump back to cpu_exec()*/
    longjmp(jbuf, 1);
}


