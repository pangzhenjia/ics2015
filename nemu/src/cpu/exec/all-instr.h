#include "prefix/prefix.h"

#include "data-mov/mov.h"
#include "data-mov/xchg.h"
#include "data-mov/push.h"
#include "data-mov/pusha.h"
#include "data-mov/popa.h"
#include "data-mov/pop.h"
#include "data-mov/leave.h"
#include "data-mov/movsx.h"
#include "data-mov/movzx.h"
#include "data-mov/cwd_cdq.h"
#include "data-mov/cmov.h"
#include "data-mov/lgdt.h"
#include "data-mov/igdt.h"
#include "data-mov/mov_cr0.h"
#include "data-mov/mov_sreg.h"

#include "arith/dec.h"
#include "arith/inc.h"
#include "arith/neg.h"
#include "arith/imul.h"
#include "arith/mul.h"
#include "arith/idiv.h"
#include "arith/div.h"
#include "arith/add_adc_sub_sbb_cmp.h"

#include "logic/and.h"
#include "logic/or.h"
#include "logic/not.h"
#include "logic/xor.h"
#include "logic/sar.h"
#include "logic/shl.h"
#include "logic/shr.h"
#include "logic/shrd.h"
#include "logic/setcc.h"
#include "logic/test.h"

#include "control/call.h"
#include "control/eflags.h"
#include "control/jcc.h"
#include "control/jmp.h"
#include "control/ret.h"
#include "control/ljmp.h"
#include "control/int.h"
#include "control/iret.h"
#include "control/cli.h"
#include "control/sti.h"

#include "string/rep.h"
#include "string/movs.h"
#include "string/stos.h"
#include "string/cmps.h"
#include "string/cld.h"
#include "string/std.h"

#include "misc/misc.h"

#include "special/special.h"
#include "special/float.h"
#include "special/in.h"
#include "special/out.h"
#include "special/hlt.h"
#include "special/bt.h"
