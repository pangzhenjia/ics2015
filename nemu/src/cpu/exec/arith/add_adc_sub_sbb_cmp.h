#ifndef __ADD_ADC_SUB_SBB_CMP_H__
#define __ADD_ADC_SUB_SBB_CMP_H__

#define instr add
#define instr_num 1
#include "add_adc_sub_sbb_cmp-template-h.h"
#undef instr_num
#undef instr 

#define instr adc
#define instr_num 2
#include "add_adc_sub_sbb_cmp-template-h.h"
#undef instr_num
#undef instr

#define instr sub
#define instr_num 3
#include "add_adc_sub_sbb_cmp-template-h.h"
#undef instr_num
#undef instr

#define instr sbb
#define instr_num 4
#include "add_adc_sub_sbb_cmp-template-h.h"
#undef instr_num
#undef instr

#define instr cmp
#define instr_num 5
#include "add_adc_sub_sbb_cmp-template-h.h"
#undef instr_num
#undef instr

#endif
