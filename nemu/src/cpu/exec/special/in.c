#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "in-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "in-template.h"
#undef DATA_BYTE
    
#define DATA_BYTE 4
#include "in-template.h"
#undef DATA_BYTE

make_helper_v(in_imm2a)
make_helper_v(in_d2a)
