#include "FLOAT.h"

FLOAT F_mul_F(FLOAT a, FLOAT b) {
    FLOAT result = (a>>8) * (b>>8);
	return result;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
    long long A = a;
    A = A << 16;
    long long result = A/b;
	return (FLOAT)result;
}

FLOAT f2F(float a) {
    a = a * (1<<16);
	return (FLOAT)a;
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

