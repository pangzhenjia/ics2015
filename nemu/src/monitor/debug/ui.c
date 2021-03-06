#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint32_t);

void stack_bt(swaddr_t eip, uint32_t ebp);

/* We use the ``readline'' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_si(char *args){
    char *numchar = strtok(NULL, " "); //get the exec number
    int num = 1;
    if (numchar != NULL){
        num = atoi(numchar);
    }
    int i = 0;
    for( ; i<num; i++){ 
        cpu_exec(1);
    }
    return 0;
}

 static int cmd_info(char *args){
     char *subcmd = strtok(NULL, " ");
     if (strcmp(subcmd, "r") == 0){
         printf("eax\t:0x%08x\nebx\t:0x%08x\necx\t:0x%08x\nedx\t:0x%08x\nebp\t:0x%08x\nesp\t:0x%08x\nedi\t:0x%08x\nesi\t:0x%08x\n", cpu.eax, cpu.ebx, cpu.ecx, cpu.edx, cpu.ebp, cpu.esp, cpu.edi, cpu.esi );

/*
         printf("es\t:0x%08x\ncs\t:0x%08x\nss\t:0x%08x\nds\t:0x%08x\n", cpu.Sreg[0].val, cpu.Sreg[1].val, cpu.Sreg[2].val, cpu.Sreg[3].val);
*/

     }
     else if(strcmp(subcmd, "w") == 0){
         info_wp();
     }
     else if(strcmp(subcmd, "p") == 0){
         printf("cr3\t:0x%x\n", cpu.cr3);
     }
     return 0;
 }


int cmd_p(char *args){   
    bool a;
    bool *success = &a;
    *success = false;
    union{
        int int1;
        float float1;
    }val;
    val.int1 = expr(args, success);
    if ( *success == true){
        printf("%s -int is %d, -float is %f, -Ox is 0x%x!\n", args, val.int1, val.float1, val.int1);
        return 0;
    }
    assert(0);
}

static int cmd_x(char *args){
    int num;
    uint32_t addr;
    uint32_t result;
    sscanf(args, "%d %x", &num, &addr);
    int i = 0;
    for( ; i<num; i++){
        result = hwaddr_read(addr, 4);
        printf("addr: \t0x%08x \tval: \t0x%08x\n", addr, result);
        addr += 4;
    }
    return 0;
}

static int cmd_w(char *args){
    WP* watch = set_wp(args);
    printf("Hardware watchpoint %d: %s\n", watch -> NO, args);
    return 0;
}

int cmd_d(char *args){
    del_wp(args);
    return 0;
}

int cmd_bt(char *args){
    stack_bt(cpu.eip, cpu.ebp);
    return 0;
}

extern void print_cache(hwaddr_t addr);
int cmd_cache(char *args){
    hwaddr_t addr; 
    sscanf(args, "%x", &addr);
    printf("0x%08x\n", addr);
    print_cache(addr);
    return 0;
}

extern uint32_t page_translate(lnaddr_t addr, size_t len);
int cmd_page(char *args){
    lnaddr_t addr;
    sscanf(args, "%x", &addr);
    uint32_t hwaddr = page_translate(addr, 4);
    printf("hwaddr:\t 0x%x \n", hwaddr);
    return 0;
}

static int cmd_help(char *args);    

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
    { "si", "exec cmd one by one", cmd_si},
    { "info", "print out the info of register or watchpoints", cmd_info},    
    { "p", "get the value of EXPR", cmd_p},
    { "x", "print out the near memory", cmd_x},
    { "w", "set watch point", cmd_w},
    { "d", "delete the related wp", cmd_d},
    {"bt", "print out the info of stack_frame", cmd_bt},
    {"cache", "print out the info of the specific block in the cache", cmd_cache},
    { "page", "print out the hwaddr by page_translate", cmd_page}

	/* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}


void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
