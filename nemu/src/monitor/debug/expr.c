#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, EQ = 1000, X = 1016, Num = 1111 

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// spaces
    {"\\(", '('},                   // left_parenthesis
    {"\\)", ')'},                   // right_parenthesis
	{"\\+", '+'},					// plus
    {"\\-", '-'},                   // substract
    {"\\*", '*'},                   // multiply
    {"\\/", '/'},                   // divide
    {"\\w+", Num},                    // number
	{"==", EQ}					    // equal
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret != 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}


typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
	
                char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array ``tokens''. For certain 
				 * types of tokens, some extra actions should be performed.*/
				 

				switch(rules[i].token_type) {
                    case NOTYPE: break;
                    case '+': tokens[nr_token].type ='+';nr_token++;break;
                    case '-': tokens[nr_token].type ='-';nr_token++;break;
                    case '*': tokens[nr_token].type ='*';nr_token++;break;
                    case '/': tokens[nr_token].type ='/';nr_token++;break;
                    case Num: tokens[nr_token].type =Num; strncpy(tokens[nr_token].str, substr_start, substr_len); nr_token++; break;
                    case '(': tokens[nr_token].type ='(';nr_token++; break;
				}

				break;
			}
		}
		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}

int eval(uint32_t p, uint32_t q);
uint32_t find_op(uint32_t p, uint32_t q, char *operate, uint32_t num);
static bool check_parenthesis(uint32_t p, uint32_t q);

int expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
    else{
        int val = eval(0, nr_token);
        *success = true;
        return val;
    }
}


int eval(uint32_t p, uint32_t q) {
    printf("p is %d, q is %d!\n", p, q);
    printf("Num token str is %s!\n", tokens[0].str);
    if ( p > q){
        printf("bad eval!\n");
        assert(0);
    }
    else if ( p == q ){
        if ( tokens[p].type == Num ){
            uint32_t val = 0;
            sscanf( tokens[p].str,"%d", &val);
            return val;
        }
        else {
            printf ("wrong expression!\n");
            assert(0);
        }
    }
    else if ( check_parenthesis(p, q) ){
        return eval(p+1, q-1);
    }
    else {
        uint32_t op = 0;
        int val1, val2;
        op = find_op(p, q, "+-", 2);
        if (op == 0){
            op = find_op(p, q, "*/", 2);
        }
        if (op == 0){
            printf("wrong expresstion in finding op!\n");
            assert(0);
        }  
        val1 = eval(p, op-1);
        val2 = eval(op+1, q);

        switch(tokens[op].type){
            case '+': return val1 + val2;
            case '-': return val1 - val2;
            case '*': return val1 * val2;
            case '/': return val1 / val2;
            default: assert(0);
        }
    }
}

//find the position of the dominant operator;
uint32_t find_op(uint32_t p, uint32_t q, char *operate, uint32_t num){
    int i, op;
    for(i = 0; i < num; i++){
        for(op = p; op < q; op++){
            if ( (char)(tokens[op].type) == operate[i]){
                return op;
            }
        }
    }
    return 0;
}


static bool check_parenthesis(uint32_t p, uint32_t q){
    return false;
}



