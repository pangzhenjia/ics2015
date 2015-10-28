#include "FLOAT.h"
#include <stdio.h>

FLOAT F_mul_F(FLOAT a, FLOAT b) {
    int a_abs, b_abs;
    if( a < 0) { a_abs = -a; }
    else{ a_abs = a;}
    if( b < 0) { b_abs = -b; }
    else{ b_abs = b; }
    int a_n = a_abs >> 16;
    int b_n = b_abs >> 16;
    int b_p = b & 0xffff;
    int val1 = a_abs * b_n;
    int val2 = a_n * b_p;
    unsigned val3 = (a * b) >> 16;
    int val = val1 + val2 + val3;
    if ( (a >> 16) * (b >> 16) < 0){ val = -val;}
    return val;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
    int i;
    int val = 0;
    int res = a;
    int div_val = 0;
    for(i = 0; i < 16; i++){
        div_val = res/b;
        val += (div_val << ( 16 - i));
        res = res - b * div_val;
        res <<= 1;
        if ( res == 0) { break; }
    }
	return val;
}

FLOAT f2F(float a) {
    void *uff = &a;
    unsigned *uffff = (unsigned *)uff;
    unsigned uf = *uffff;
    unsigned exponent = uf << 1 >> 24;
    unsigned fraction = uf << 9 >> 9;
    fraction >>= 7;
    int sign = uf >> 31;
    sign = (sign << 31) >> 31;
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
        unsigned sign_1 = sign << (17 + new_exponent);
        if(new_exponent < 0){
            if ( new_exponent < -16){
                return 0;
            }
            else if( new_exponent == -16){
                return 1;
            }
            else{
                unsigned fraction_1 = fraction >> (-new_exponent);
                return (sign_1 | one_1 |fraction_1);
            }
        }
        else if(new_exponent < 33){
            unsigned fraction_2 = fraction << new_exponent;
            return (sign_1 | one_1 | fraction_2);
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

