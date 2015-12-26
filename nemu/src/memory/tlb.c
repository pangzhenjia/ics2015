#include "common.h"
#include "nemu.h"
#include "misc.h"
#include <stdlib.h>
#include "x86-inc/mmu.h"

/* Now we are going to make a TLB! */

#define OFFSET_WID 12    // offset: 4KB
#define DRAM_WID   27    // dram:   128MB
#define V_DRAM_WID  32    // virtual dram: 4GB

#define NR_TLB  64  

#define TAG_WID    (DRAM_WID - OFFSET_WID)
#define V_TAG_WID  (V_DRAM_WID - OFFSET_WID)


typedef struct{
    uint32_t p_tag: TAG_WID;
    uint32_t v_tag: V_TAG_WID;
    uint32_t valid: 1;
} TLB;

TLB tlb[NR_TLB];

void init_tlb(){
    int i;
    for(i=0; i< NR_TLB; i++){
        tlb[i].valid = 0;
    }
}

uint32_t tlb_find_num();
uint32_t tag_translate(lnaddr_t addr);

uint32_t tlb_translate(lnaddr_t addr){
    /* give me a lnaddr, you'll get a hwaddr;
       if not hit in TLB, TLB will automately load it from dram */

    uint32_t v_tag = addr >> 12;
    uint32_t offset = addr & 0xfff;

    /* TLB hit */
    int i;
    for(i=0; i< NR_TLB; i++){
       if(tlb[i].valid && tlb[i].v_tag == v_tag){
           uint32_t hwaddr = (tlb[i].p_tag << 12) + offset;
           return hwaddr;
       }
    }

    /* TLB not hit */
    uint32_t p_tag = tag_translate(addr);

    uint32_t num = tlb_find_num();
    tlb[num].v_tag = v_tag;
    tlb[num].p_tag = p_tag;
    tlb[num].valid = 1;
    uint32_t hwaddr = (p_tag << 12) + offset;
    return hwaddr;
}




uint32_t tlb_find_num(){

    /* have empty block to fill in */
    int i;
    for(i=0; i< NR_TLB; i++){
        if(tlb[i].valid == 0){ return i; }
    }

    /* no empty block, randomly fill in */
    uint32_t num = rand() % NR_TLB;
    return num;
}




union {
    uint32_t addr;
    struct {
        uint32_t offset: 12;
        uint32_t page  : 10;
        uint32_t dir   : 10;
    };
}page_addr;


uint32_t tag_translate(lnaddr_t addr){

    /* give me a lnaddr, you'll get the physical page frame tag */

    page_addr.addr = addr;
    uint32_t dir    = page_addr.dir;
    uint32_t page   = page_addr.page;
    //uint32_t offset = page_addr.offset;
   
    uint32_t cr3_addr = cpu.cr3 & (~0xfff);

    uint32_t pde_addr = cr3_addr | (dir << 2);
    uint32_t pde_val = hwaddr_read(pde_addr, 4);
    PDE pde;
    pde.val = pde_val;
    if(!pde.present){
        Assert(0, "eip: 0x%x\nPageDirectory fault", cpu.eip);
    }

    uint32_t pte_addr = (pde.page_frame << 12) | (page << 2);
    uint32_t pte_val = hwaddr_read(pte_addr, 4);
    PTE pte; 
    pte.val = pte_val;
    

        printf("eip: 0x%x\n", cpu.eip);
        printf("addr: 0x%x\n", addr);
        printf("cr3 : 0x%x\n", cpu.cr3);
        printf("pde_addr: 0x%x\n", pde_addr);
        printf("pte_addr: 0x%x\n", pte_addr);
        printf("pte_val: 0x%x\n", pte_val);
        printf("\n");


    if(pte.val == 0){ return 0x1000000; }

    if(!pte.present){
        Assert(0, "eip: 0x%x\nPageTable fault", cpu.eip);
    }

    return pte.page_frame;
}
