#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_list[NR_WP];
static WP *head, *free_;

void init_wp_list() {
	int i;
	for(i = 0; i < NR_WP - 1; i ++) {
		wp_list[i].NO = i;
		wp_list[i].next = &wp_list[i + 1];
	}
	wp_list[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_list;
}

WP* get_head(){
    return head;
}

WP* new_wp(){
    WP* re = free_;
    if ( re != NULL ){
        free_ = free_ -> next; // get wp from free;
        re -> next = head;
        head = re;       // make the using wp in head 
        return re;
    }
    else{
        printf("no available watchpoint, have to refree!\n");
        assert(0);
        return 0;
    }
}

void free_wp( WP* wp){
    wp -> next = free_;
    free_ = wp;
    // have to delete from head
    WP* p;
    for(p=head; p!=NULL; p =p -> next){
        if( wp == head) {
            head = head -> next;
        }
        if((p -> next) == wp){
            p -> next = wp -> next;
        }
    }
}


WP* set_wp(char *args){
    bool a;
    bool *success = &a;
    *success = false;
    WP* watch = new_wp();
    unsigned result = expr( args, success);
    if ( *success == true){
        watch -> expr = args;
        watch -> p_val = result;
        return watch;
    }
    else{
        printf(" the expr is illegal!\n");
        assert(0);
    }
}

int watch_wp(){
    bool a;
    bool *success = &a;
    *success = false;
    unsigned result;
    int i = 0;
    WP *p;

    for( p = head; ; p = p -> next){
        if (p == NULL){break;}
        printf("%d expr is %s\n", p->NO, p -> expr);
        result = expr(p -> expr, success);
        if(*success == false){
            printf(" expr bug! sorry for watchpoint\n");
            assert(0);
        }
        if ( p -> p_val != result) {
            i++;
            p -> n_val = result;
            printf("Hardware watchpoint %d: %s\n", p -> NO, p -> expr);
            printf("Old value: %d\n", p -> p_val);
            printf("New value: %d\n", p -> n_val);
            p -> p_val = p -> n_val;
        }
    }
    if ( i == 0){return 0;}
    return -1;
}
    


