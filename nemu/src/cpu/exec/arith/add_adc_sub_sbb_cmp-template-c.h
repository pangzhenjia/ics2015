#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "add_adc_sub_sbb_cmp-template-f.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "add_adc_sub_sbb_cmp-template-f.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "add_adc_sub_sbb_cmp-template-f.h"
#undef DATA_BYTE


make_helper_v(concat(instr, _i2a))
make_helper_v(concat(instr, _i2rm))
make_helper_v(concat(instr, _si2rm))
make_helper_v(concat(instr, _r2rm))
make_helper_v(concat(instr, _rm2r))
