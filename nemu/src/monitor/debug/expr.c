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
    {"\\b0[xX][0-9]+\\b", X},       // 0x...
    {"\\b[0-9]+\\b", Num},          // number
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
                    case ')': tokens[nr_token].type =')';nr_token++;break;
                    case X  : tokens[nr_token].type =X;   strncpy(tokens[nr_token].str, substr_start, substr_len); nr_token++;  break;
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

//statement
int eval(uint32_t p, uint32_t q);
uint32_t find_op(uint32_t p, uint32_t q);
static bool check_parenthesis(uint32_t p, uint32_t q);

//the main evaluation
int expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
    else{
        *success = true;
        int val = eval(0, nr_token-1);
        return val;
    }
}

//recurssion to evaluate the expr
int eval(uint32_t p, uint32_t q) {
    printf("eval: p is %d, q is %d\n", p ,q);
    if ( p > q){
        printf("wrong operator!\n");
        assert(0);
    }
    
    else if ( p == q ){
        if ( tokens[p].type == Num ){
            uint32_t val = 0;
            sscanf( tokens[p].str,"%d", &val);
            return val;
        }
        else if( tokens[p].type == X ){
            uint32_t val =0;
            sscanf( tokens[p].str, "%x", &val);
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

        // reconigize the negative number
        if (tokens[p].type == '-'){
            return -eval(p+1, q);
        }

        op = find_op(p, q);
        if (op == 0){
            printf("wrong expresstion in finding op!\n");
            assert(0);
        }  
        val1 = eval(p, op-1);
        val2 = eval(op+1, q);

        switch(tokens[op].type){
            case '+': return val1 + val2;break;
            case '-': return val1 - val2;break;
            case '*': return val1 * val2;break;
            case '/': return val1 / val2;break;
        }
    }
    return 0;
}

//find the position of the dominant operator;
uint32_t find_op(uint32_t p, uint32_t q){
    int i, op;
    char *operate = "+-*/";     
    for(i = 0; i < 4; i++){
        for(op = p; op < q; op++){
            if ( (char)(tokens[op].type) == operate[i]){
                return op;
            }
        }
    }
    return 0;
}


static bool check_parenthesis(uint32_t p, uint32_t q){
    uint32_t i=p, j=q;
    printf("brackets: p is %d, q is %d\n", p, q);
    for(i= p; i<q+1; i++){
        if(tokens[i].type == '(' ){       // find '('
            printf("have '('!\n");
            while( j>p-1 ){
                if(tokens[j].type == ')' ){   // find ')'
                    printf("have ')'!\n" );
                    if ( i >= j){            // bad ') ('
                        printf("wrong parenthesis!\n");
                        assert(0);
                    }
                    if ( i == p && j == q){
                        check_parenthesis(i+1, j-1); //check error
                        return true;
                    }
                    else {
                        check_parenthesis(i+1, j-1); // check error
                        return false;
                    }
                }
                j--;
                printf("j is %d!\n", j);
            } 
            if(j == p){
                printf("wrong parenthesis!\n");  // have '(', but no ')'
                assert(0);
            }
        }
    }
    // now there is no '('
    printf("i is %d, j is %d!\n", i, j);
    if(i == q){
        for(j=q; j>p-1; j--){
            if (tokens[j].type == ')' ){   // no '(', but have ')'
                printf("wrong parenthesis!\n");
                assert(0);
            }
        }
    }
    //now no '(', no ')', good!
    if (j == p){
        printf(" whatever!, j is %d\n", j);
        return false;
    }
    else{
        printf("wrong parenthesis!\n"); 
        assert(0);
    }
}



