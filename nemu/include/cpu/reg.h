#ifndef __REG_H__
#define __REG_H__

#include "common.h"

enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI };
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };

/* TODO: Re-organize the `CPU_state' structure to match the register
 * encoding scheme in i386 instruction format. For example, if we
 * access cpu.gpr[3]._16, we will get the `bx' register; if we access
 * cpu.gpr[1]._8[1], we will get the 'ch' register. Hint: Use `union'.
 * For more details about the register encoding scheme, see i386 manual.
 */

typedef struct {
	union{
        union {
	    	uint32_t _32;
		    uint16_t _16;
		    uint8_t _8[2];
	    } gpr[8];

	/* Do NOT change the order of the GPRs' definitions. */

        //uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
        struct{
            union{uint32_t eax; uint16_t ax;  uint8_t al, ah;};
            union{uint32_t ecx; uint16_t cx;  uint8_t cl, ch;};
            union{uint32_t edx; uint16_t dx;  uint8_t dl, dh;};
            union{uint32_t ebx; uint16_t bx;  uint8_t bl, bh;};
            union{uint32_t esp; uint16_t sp;};
            union{uint32_t ebp; uint16_t bp;};
            union{uint32_t esi; uint16_t si;};
            union{uint32_t edi; uint16_t di;};
        };
    };
	swaddr_t eip;
    union{
        uint32_t eflags;
        struct{
            unsigned cf:1;
            unsigned   :1;
            unsigned pf:1;
            unsigned   :1;
            unsigned af:1;
            unsigned   :1;
            unsigned zf:1;
            unsigned tf:1;
            unsigned If:1;
            unsigned df:1;
            unsigned of:1;
        };
    };

} CPU_state;

extern CPU_state cpu;

static inline int check_reg_index(int index) {
	assert(index >= 0 && index < 8);
	return index;
}

#define reg_l(index) (cpu.gpr[check_reg_index(index)]._32)
#define reg_w(index) (cpu.gpr[check_reg_index(index)]._16)
#define reg_b(index) (cpu.gpr[check_reg_index(index) & 0x3]._8[index >> 2])

extern const char* regsl[];
extern const char* regsw[];
extern const char* regsb[];

#endif
