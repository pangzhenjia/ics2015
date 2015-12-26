#ifndef __STD_H__
#define __STD_H__

int std(swaddr_t eip){
    cpu.df = 1;
    return 1;
}

#endif
