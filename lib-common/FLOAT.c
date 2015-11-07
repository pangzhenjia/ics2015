#include "FLOAT.h"
#include <stdio.h>

FLOAT F_mul_F(FLOAT a, FLOAT b) {
    /* get positive a, b */
    unsigned a_abs, b_abs;
    if( a < 0) { a_abs = -a; }
    else{ a_abs = a;}
    if( b < 0) { b_abs = -b; }
    else{ b_abs = b; }

    /* split a = a_n + a_p; b = b_n + b_p */
    unsigned a_n = a_abs >> 16;
    unsigned b_n = b_abs >> 16;
    unsigned b_p = b & 0xffff;


    unsigned val1 = a_abs * b_n;
    unsigned val2 = a_n * b_p;
    unsigned val3 = (a * b) >> 16;
    unsigned val = val1 + val2 + val3;
    if ( (a >> 16) * (b >> 16) < 0){ val = -val;}
    return val;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
    int a_abs, b_abs;
    if(a<0) { a_abs = -a; }
    else{ a_abs = a; }
    if(b<0) { b_abs = -b; }
    else{ b_abs = b; }
    int i, j;
    int val = 0;
    int res = a_abs;
    int div_val = 0;
    for(i = 0; i < 16; i++){
        j = i;
        div_val = res/b_abs;
        val += (div_val << (16 - i));
        res = res - b_abs * div_val;
        res = res << 1;
        if ( res == 0) { break; }
    }
    if((a>>16) * (b>>16) < 0){ val = -val; }
	return val;
}

FLOAT f2F(float a) {
    void *uff = &a;
    unsigned *uffff = (unsigned *)uff;
    unsigned uf = *uffff;
    unsigned exponent = uf << 1 >> 24;
    unsigned fraction = uf << 9 >> 9;
    int sign = uf >> 31;
    sign = sign << 31 >> 31;
    int new_exponent, val, shift;
    if ( exponent == 0xff ){
        return 0x80000000u;
    }
    else if(exponent == 0){ 
        return 0;
    }
    else{
        exponent = exponent - 127;
        new_exponent = exponent;
        unsigned one_1 = 1 << (16 + new_exponent);
        if(new_exponent < 0){
            if ( new_exponent < -16){
                return 0;
            }
            else if( new_exponent == -16){
                return 1;
            }
            else{
                unsigned fraction_1 = fraction >> 7;
                fraction_1 = fraction_1 >> (-new_exponent);
                return ((sign ^ (one_1 |fraction_1)) + (sign&1));
            }
        }
        else if(new_exponent < 7){
            unsigned fraction_2 = fraction >> ( 7 -new_exponent);
            return ((sign ^ (one_1 | fraction_2)) + (sign&1));
        }
        else if(new_exponent > 6){
            unsigned fraction_3 = fraction << (new_exponent -7);
            return (sign ^ (one_1 | fraction_3) + (sign&1));
        }
        else{
            return 0;
        }
    }
}

FLOAT Fabs(FLOAT a) {
    if(a<0) { a = -a; }
	return a;
}

FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);

	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

