#include "cpu/exec/template-start.h"


int concat(cmova_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.cf == 0 && cpu.zf == 0){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}

int concat(cmovae_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.cf == 0){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovb_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.cf == 1){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovbe_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 1 || cpu.cf == 1){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovc_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.cf == 1){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmove_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 1){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}

int concat(cmovg_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 0 && cpu.sf == cpu.of){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovge_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.sf == cpu.of){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovl_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.sf != cpu.of){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovle_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 1 || cpu.sf != cpu.of){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovna_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 1 || cpu.cf == 1){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovnae_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.cf == 1){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovnb_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.cf == 0){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovnbe_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 0 && cpu.cf == 0){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovnc_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.cf == 0){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovne_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 0){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovng_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 1 || cpu.sf != cpu.of){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovnge_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.sf != cpu.of){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovnl_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.sf == cpu.of){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovnle_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 0 && cpu.sf == cpu.of){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovno_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.of == 0){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovnp_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.pf == 0){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovns_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.sf == 0){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovnz_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 0){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovo_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.of == 1){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovp_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.pf == 1){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovpe_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.pf == 1){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovpo_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.pf == 0){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}
int concat(cmovs_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.sf == 1){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}

int concat(cmovz_rm2r_, SUFFIX)(swaddr_t eip){
    int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
    len += 1;
    if (cpu.zf == 1){
        OPERAND_W(op_dest, op_src->val);
    }
    return len;
}

#include "cpu/exec/template-end.h"
