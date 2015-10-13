#ifndef __ADD_ADC_SUB_SBB_CMP_H__
#define __ADD_ADC_SUB_SBB_CMP_H__

#define instr add
#include "add_adc_sub_sbb_cmp-template-h.h"
#undef instr

#define instr adc
#include "add_adc_sub_sbb_cmp-template-h.h"
#undef instr

#define instr sub
#include "add_adc_sub_sbb_cmp-template-h.h"
#undef instr

#define instr sbb
#include "add_adc_sub_sbb_cmp-template-h.h"
#undef instr

#define instr cmp
#include "add_adc_sub_sbb_cmp-template-h.h"
#undef instr

#endif
