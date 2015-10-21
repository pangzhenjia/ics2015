#include "FLOAT.h"
#include <stdio.h>

FLOAT F_mul_F(FLOAT a, FLOAT b) {
    FLOAT result = (a>>2) * (b>>2);
    result >>= 12;
	return result;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
    FLOAT val1 = a / b;
    val1 <<= 16;
    FLOAT val2 = (a<<16) / (b<<16);
    val2 = val2 & 0xffff;
	return val1 | val2;
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

