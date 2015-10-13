#if instr == adc

#define CF cpu.cf
#define add_sub_op +
#define add_sub_flags add

#elif instr == add

#define CF 0
#define add_sub_op +
#define add_sub_flags add

#elif instr == sub

#define CF 0
#define add_sub_op -
#define add_sub_flags sub

#elif instr == sbb 

#define CF cpu.cf
#define add_sub_op -
#define add_sub_flags sub

#elif instr == cmp

#define CF 0
#define add_sub_op -
#define add_sub_flags sub

#else
#error unknown instr

#endif
