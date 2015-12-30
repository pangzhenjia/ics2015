#ifndef __STI_H__
#define __STI_H__

int sti(swaddr_t eip){
    cpu.If = 1;
    return 1;
}

#endif
