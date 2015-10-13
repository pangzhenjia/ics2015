#define instr add
#include "add_adc_sub_sbb_cmp-template-c.h"
#undef instr

#define instr adc
#include "add_adc_sub_sbb_cmp-template-c.h"
#undef instr

#define instr sub
#include "add_adc_sub_sbb_cmp-template-c.h"
#undef instr

#define instr sbb
#include "add_adc_sub_sbb_cmp-template-c.h"
#undef instr

#define instr cmp
#include "add_adc_sub_sbb_cmp-template-c.h"
#undef instr
