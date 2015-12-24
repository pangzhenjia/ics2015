#ifndef __CLD_H__
#define __CLD_H__

int cld(swaddr_t eip){
    cpu.df = 0;
    return 1;
}

#endif
