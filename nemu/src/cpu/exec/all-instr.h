#include "prefix/prefix.h"

#include "data-mov/mov.h"
#include "data-mov/xchg.h"
#include "data-mov/push.h"
#include "data-mov/pop.h"
#include "data-mov/leave.h"
#include "data-mov/movsx.h"
#include "data-mov/movzx.h"
#include "data-mov/cwd_cdq.h"

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

#include "control/call.h"
#include "control/test.h"
#include "control/eflags.h"
#include "control/je.h"

#include "string/rep.h"

#include "misc/misc.h"

#include "special/special.h"
