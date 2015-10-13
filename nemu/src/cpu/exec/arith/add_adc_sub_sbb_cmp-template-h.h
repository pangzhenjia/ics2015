#include "add_adc_sub_sbb_cmp-macro-start.h"

make_helper(concat(instr, _i2a_b));
make_helper(concat(instr, _i2a_v));
make_helper(concat(instr, _i2rm_b));
make_helper(concat(instr, _i2rm_v));
make_helper(concat(instr, _si2rm_v));
make_helper(concat(instr, _r2rm_b));
make_helper(concat(instr, _r2rm_v));
make_helper(concat(instr, _rm2r_b));
make_helper(concat(instr, _rm2r_v));

#include "add_adc_sub_sbb_cmp-macro-end.h"
