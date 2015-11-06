#include "cpu/exec/template-start.h"


int concat(ja_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.cf == 0 && cpu.zf == 0){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}

int concat(jae_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.cf == 0){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jb_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.cf == 1){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jbe_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 1 || cpu.cf == 1){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jc_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.cf == 1){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(je_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 1){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jz_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 1){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jg_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 0 && cpu.sf == cpu.of){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jge_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.sf == cpu.of){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jl_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.sf != cpu.of){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jle_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 1 || cpu.sf != cpu.of){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jna_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 1 || cpu.cf == 1){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jnae_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.cf == 1){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jnb_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.cf == 0){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jnbe_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 0 && cpu.cf == 0){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jnc_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.cf == 0){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jne_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 0){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jng_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 1 || cpu.sf != cpu.of){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jnge_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.sf != cpu.of){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jnl_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.sf == cpu.of){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jnle_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 0 && cpu.sf == cpu.of){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jno_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.of == 0){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jnp_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.pf == 0){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jns_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.sf == 0){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jnz_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 0){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jo_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.of == 1){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jp_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.pf == 1){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jpe_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.pf == 1){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jpo_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.pf == 0){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(js_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.sf == 1){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}

#if DATA_BYTE == 1
int concat(jcxz_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (reg_w(R_ECX) == 0){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
int concat(jecxz_si_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    len += 1;
    if (reg_l(R_ECX) == 0){
        DATA_TYPE_S val0 = op_src -> val;
        int val = val0;
        cpu.eip+=val;
    }
    return len;
}
#endif

#include "cpu/exec/template-end.h"
