#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint32_t);

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

static int cmd_help(char *args);
static int cmd_si(char *args);
static int cmd_info(char *args);
int cmd_p(char *args);
static int cmd_x(char *args);

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
         printf("\teax:0x%8x\n\tebx:0x%8x\n\tecx:0x%8x\n\tedx:0x%8x\n\tebp:0x%8x\n\tesp:0x%8x\n\tedi:0x%8x\n\tesi:0x%8x\n\t", cpu.eax, cpu.ebx, cpu.ecx, cpu.edx, cpu.ebp, cpu.esp, cpu.edi, cpu.esi );
     }
     return 0;
 }

int cmd_p(char *args){
    uint32_t result =strtol(args,NULL,16);
    return result;
}

static int cmd_x(char *args){
    char *numchar = strtok(NULL, " ");
    int num = atoi(numchar);
    char *expr = strtok(NULL, " ");
    uint32_t value = cmd_p(expr), result = 0;
    int i = 0;
    for( ; i<num; i++){
        result = swaddr_read(value,4);
        printf("0x%8x\n", result);
        value += 4;
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
