#include "FLOAT.h"

FLOAT F_mul_F(FLOAT a, FLOAT b) {
    FLOAT result = (a>>8) * (b>>8);
	return result;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
    //long long A = a;
    //A = A << 16;
    //long long result = A/b;
    FLOAT result = (a << 8) / (b >> 8);
	return result;
}

FLOAT f2F(float a) {
    unsigned uf = (int)a & (~0);
    unsigned exponent = uf << 1 >> 24;
    unsigned fraction = uf << 9 >> 9;
    unsigned sign = uf >> 31;
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
        if(new_exponent < 0){ // unsigned exp can not < 0
            return 0;
        }
        else if(exponent < 24){
            shift = 23 - exponent;
            fraction = fraction >> shift;
            val = ( 1 << exponent) | fraction;
            if ( sign ){ val = -val; }
            return val;
        }
        else if(exponent < 31){
            shift = exponent -23;
            fraction = fraction << shift;
            val = ( 1 << exponent) | fraction;
            if ( sign ){ val = -val; }
            return val;
        }
        else{  // overflow
            return 0x80000000;
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

