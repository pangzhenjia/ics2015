#include "cpu/exec/helper.h"
#include "device/i8259.h"

void raise_intr(uint8_t no);

int hlt(swaddr_t eip){

   // return 1;
   // /*
    cpu.If = 1;
    
    cpu.eip += 1;
    while(1){
        if(cpu.INTR & cpu.If) {
            uint32_t intr_no = i8259_query_intr();
            i8259_ack_intr();
            raise_intr(intr_no);
            return 0;
        }
    }
  // */ 
}
