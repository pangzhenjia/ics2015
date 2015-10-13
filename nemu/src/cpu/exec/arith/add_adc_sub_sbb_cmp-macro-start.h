#if instr_num == 2

#define CF cpu.cf
#define add_sub_op +
#define add_sub_flags add

#elif instr_num == 1

#define CF 0
#define add_sub_op +
#define add_sub_flags add

#elif instr_num == 3

#define CF 0
#define add_sub_op -
#define add_sub_flags sub

#elif instr_num == 4 

#define CF cpu.cf
#define add_sub_op -
#define add_sub_flags sub

#elif instr_num == 5

#define CF 0
#define add_sub_op -
#define add_sub_flags sub

#else
#error unknown instr

#endif
