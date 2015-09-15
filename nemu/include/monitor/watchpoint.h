#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
    char *expr;
    unsigned p_val;
    unsigned n_val;
	int NO;
	struct watchpoint *next;

	/* TODO: Add more members if necessary */


} WP;

extern void init_wp_list();
extern WP* set_wp(char *args);
extern int watch_wp();
extern WP* get_head();

#endif
