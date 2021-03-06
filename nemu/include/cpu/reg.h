#ifndef __REG_H__
#define __REG_H__

#include "common.h"
#include "x86-inc/cpu.h"
#include "x86-inc/mmu.h"


enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI };
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };

enum { SR_ES, SR_CS, SR_SS, SR_DS };

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
            union{uint32_t eax; uint16_t ax;  struct{ uint8_t al; uint8_t ah;}; };
            union{uint32_t ecx; uint16_t cx;  struct{ uint8_t cl; uint8_t ch;}; };
            union{uint32_t edx; uint16_t dx;  struct{ uint8_t dl; uint8_t dh;}; };
            union{uint32_t ebx; uint16_t bx;  struct{ uint8_t bl; uint8_t bh;}; };
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
            unsigned sf:1;
            unsigned tf:1;
            unsigned If:1;
            unsigned df:1;
            unsigned of:1;
        };
    };

    union{
        uint64_t idtr:48;
        struct {
            unsigned limit:16;
            unsigned base :32;
        } _idtr;
    };
    
    /* for segment */
    union{
        uint64_t gdtr:48;
        struct {
            unsigned limit:16;
            unsigned base :32;
        } _gdtr;
    };

    union{
        uint32_t cr0;
        struct{
            unsigned pe:1;
            unsigned mp:1;
            unsigned em:1;
            unsigned ts:1;
            unsigned et:1;
            unsigned   :26;
            unsigned pg:1;
        } CR0;
    };

    union{
        uint32_t cr3;
        struct{
		    uint32_t pad0                : 3;
		    uint32_t page_write_through  : 1;
		    uint32_t page_cache_disable  : 1;
		    uint32_t pad1                : 7;
		    uint32_t page_directory_base : 20;
        } CR3;
    };

    
    struct{
        union{
            uint16_t val;

            struct{
            unsigned rpl:2;
            unsigned ti :1;
            unsigned index : 13;
            };
        };
        struct{
            uint32_t base;
            uint32_t limit;
        };

    } Sreg[4];
    
    bool INTR;
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
