#define instr_num 1
#define instr add
#include "add_adc_sub_sbb_cmp-template-c.h"
#undef instr_num
#undef instr 

#define instr adc
#define instr_num 2
#include "add_adc_sub_sbb_cmp-template-c.h"
#undef instr_num
#undef instr

#define instr sub
#define instr_num 3
#include "add_adc_sub_sbb_cmp-template-c.h"
#undef instr_num
#undef instr

#define instr sbb
#define instr_num 4
#include "add_adc_sub_sbb_cmp-template-c.h"
#undef instr_num
#undef instr

#define instr cmp
#define instr_num 5
#include "add_adc_sub_sbb_cmp-template-c.h"
#undef instr_num
#undef instr
