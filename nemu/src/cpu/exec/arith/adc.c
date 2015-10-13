#include "cpu/exec/helper.h"

#define instr adc

#define DATA_BYTE 1
#include "add_adc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "add_adc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "add_adc-template.h"
#undef DATA_BYTE

#undef instr

make_helper_v(adc_i2a)
make_helper_v(adc_i2rm)
make_helper_v(adc_si2rm)
make_helper_v(adc_r2rm)
make_helper_v(adc_rm2r)
