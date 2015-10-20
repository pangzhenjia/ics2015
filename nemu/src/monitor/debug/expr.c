#include "nemu.h"   

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, EQ = 5000, NQ = 5001, AND = 5002, OR = 5003, NO=5004,  X = 1016, Num = 1111,  

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
    {"\\$[A-Za-z]+\\b", '$'},          // $register
	{"\\+", '+'},					// plus
    {"\\-", '-'},                   // substract
    {"\\*", '*'},                   // multiply
    {"\\/", '/'},                   // divide
    {"\\b0[xX][a-fA-F0-9]+\\b", X},       // 0x...
    {"\\b[0-9]+\\b", Num},          // number
	{"\\=\\=", EQ},					     // equal
    {"\\!\\=", NQ},                     // not equal
    {"\\&\\&", AND},                    // and
    {"\\|\\|", OR},                     // or
    {"\\!", NO}                         // no
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
				    case '$': tokens[nr_token].type ='$'; strncpy(tokens[nr_token].str, substr_start, 4); nr_token++; 
                            break;
                    case EQ : tokens[nr_token].type =EQ; nr_token++; break;
                    case NQ : tokens[nr_token].type =NQ; nr_token++; break;
                    case AND: tokens[nr_token].type =AND; nr_token++; break;
                    case OR : tokens[nr_token].type =OR;  nr_token++; break;
                    case NO : tokens[nr_token].type =NO;  nr_token++; break;
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
uint32_t eval(uint32_t p, uint32_t q);
uint32_t find_op(uint32_t p, uint32_t q);
static bool check_parenthesis(uint32_t p, uint32_t q);
uint32_t get_reg(uint32_t p);
uint32_t find_logic_op(uint32_t p, uint32_t q);
uint32_t get_logic_result(uint32_t p, uint32_t q, uint32_t logic_op);
void get_par_position(uint32_t p, uint32_t q);

//the main evaluation
uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
    else{
        *success = true;
        uint32_t val = eval(0, nr_token-1);
        return val;
    }
}

//to evaluate all the brackets in the tokens, we have to identify all the position of the both sides brackets.
uint32_t par_position[32], iterator;

//recurssion to evaluate the expr
uint32_t eval(uint32_t p, uint32_t q) {
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
        else if( tokens[p].type == X ){
            uint32_t val =0;
            sscanf( tokens[p].str, "%x", &val);
            return val;
        }
        else if (tokens[p].type == '$'){
            printf("the reg is %s!\n", tokens[p].str);
            return get_reg(p);
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
        uint32_t op = 0, logic_op = 0;
        uint32_t val1, val2;
        get_par_position(p, q);
        logic_op = find_logic_op(p, q); // only four forms ==, !=, &&, ||
        if(logic_op != 0){
            return get_logic_result(p, q, logic_op);
        }

        // reconigize the negative number or the value of a pointer or the !num
        if (tokens[p].type == '-' || tokens[p].type == '*' || tokens[p].type == NO){
            if( (tokens[p+1].type == '('&& tokens[q].type == ')') || (p+1 == q) ){
                //only two type, -1, -(3+5) 
                if(tokens[p].type == '-'){
                    return -eval(p+1,q);
                }
                else if(tokens[p].type == '*'){
                    return swaddr_read(eval(p+1, q), 4);
                }
                else{
                    return !eval(p+1,q);
                }
            }
        }

        op = find_op(p, q);
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
    uint32_t i, num, op;
    char *operate = "+-/*";   
    for(i = 0; i < 4; i++){
        num = 0;  // this is definitely important!
        for(op = p+1; op < q; op++){ 
            // op=p+1 is very important, because it can rule out the case like that negative number -1 or poiter *12
             
            if( op==p+1 && par_position[0] == 0){
                op = par_position[1]+1;
                num += 2;
            }
            else if(op == par_position[num] ){ 
                if( par_position[num+1] == q){
                    break;  
                    //not only more quickly, but also avoid out of range
                }
                op = par_position[num+1] + 1;
                num += 2;
            }
            // get op not in the brackets, so if op bump in the par, op has to go to the next par
            if ( (char)(tokens[op].type) == operate[i]){
                if (tokens[op].type == '-' && (tokens[op-1].type == '-' || tokens[op-1].type == '*' || tokens[op-1].type == '/')){
                    return op-1;  // find "--", "*-", "/-"
                }
                else{
                    return op;
                }
            }
        }
    }
    printf("wrong operator!\n");
    assert(0);
    return 0;
}


static bool check_parenthesis(uint32_t p, uint32_t q){
    uint32_t i=1000, j=1000, par=0;
    if(p>=q){
        printf("wrong parenthesis!\n");
        assert(0);
    }
    for(i= p; i<q+1; i++){
        if(tokens[i].type == '(' ){       // find '('
            par++;
            for( j=i+2; j<q+1; j++){
                if(tokens[j].type == '('){
                    par++;
                }
                else if(tokens[j].type == ')' ){
                    par--;
                }                  
                if(par == 0){          //find the match ')'
                    if ( i == p && j == q){
                        check_parenthesis(i+1, j-1); //check error
                        return true;
                    }
                    else {
                        if(j<q-1){
                            check_parenthesis(j+1, q);
                        }
                        check_parenthesis(i+1, j-1); // check error
                        return false;
                    }
                }
            } 
            printf("wrong parenthesis!\n");  // have '(', but no ')'
            assert(0);
        }
    }
    // now there is no '('
    for(j=q; j>p; j--){
        if (tokens[j].type == ')' ){   // no '(', but have ')'
            printf("wrong parenthesis!\n");
            assert(0);
        }
    }
    //now no '(', no ')', good!
    return false;
}

uint32_t get_reg(uint32_t p){
    if(strcmp(tokens[p].str, "$eax") == 0){
        return cpu.eax;
    }
    else if(strcmp(tokens[p].str, "$ecx") == 0){
        return cpu.ecx;
    }
    else if(strcmp(tokens[p].str, "$edx") == 0){
        return cpu.edx;
    }
    else if(strcmp(tokens[p].str, "$ebx") == 0){
        return cpu.ebx;
    }
    else if(strcmp(tokens[p].str, "$esp") == 0){
        return cpu.esp;
    }
    else if(strcmp(tokens[p].str, "$ebp") == 0){
        return cpu.ebp;
    }
    else if(strcmp(tokens[p].str, "$esi") == 0){
        return cpu.esi;
    }
    else if(strcmp(tokens[p].str, "$edi") == 0){
        return cpu.edi;
    }
    else{
        printf("wrong register!\n");
        assert(0);
    }
}

uint32_t find_logic_op(uint32_t p, uint32_t q){
    /* extended power, maybe we do not need it now

    uint32_t logic_op, i, num;
    int logic[4] = { EQ, NQ, AND, OR};
    for(i=0; i<4; i++){
        num = 0;
        for(logic_op = p; logic_op < q+1; logic_op++){
            if(logic_op == par_position[num]){
                if(par_position[num+1] == q){
                    break;
                }
                else{
                    logic_op = par_position[num+1]+1;
                    num += 2;
                }
            }
            if(tokens[logic_op].type == logic[i]){
                return logic_op;
            }
        }
    } 
    */

    uint32_t logic_op, i;
    int logic[4] = { EQ, NQ, AND, OR};
    for(i=0; i<4; i++){
        for(logic_op = p+1; logic_op <q; logic_op++){
            if (tokens[logic_op].type == logic[i]){
                return logic_op;
            }
        }
    }

    return 0;
}

uint32_t get_logic_result(uint32_t p, uint32_t q, uint32_t logic_op){
    uint32_t val1 = eval(p, logic_op-1);
    uint32_t val2 = eval(logic_op+1, q);
    switch(tokens[logic_op].type){
        case EQ : return val1 == val2; 
        case NQ : return val1 != val2;
        case AND: return val1 && val2;
        case OR : return val1 || val2; 
    }
    return 0;
}


void get_par_position(uint32_t p, uint32_t q){
    uint32_t num, i = p, j, par=0;
    for(num=0; num<32; num++){
        par_position[num] = 1000;
    }   // initiate the par_position
    num = 0;
    while( i<q ){
        if (tokens[i].type == '(' ){
            par_position[num] = i;
            num++;
            par++;
            for(j=i+1; j<q+1; j++){
                if(tokens[j].type == '(' ){
                    par++;
                }
                else if(tokens[j].type == ')' ){
                    par--;
                }
                if(par == 0){
                    par_position[num] = j;
                    num++;
                    i = j+1;
                    break;
                }
            }
        }
        else{
            i++;
        }
    }
}
