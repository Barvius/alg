#include "stdafx.h"
#include "stdio.h"
#include "math.h"
#include "conio.h"

void main() {
	float a, b, c;
	a = pow(6, 2.45) - pow(4 * pow(9, 1./5), -3./4)*tan(2);
	b = sin(6*asin(2./3)+atan(5./8));
	if (fabs(a)>=5*fabs(b)){
		c = log(fabs(2 * exp(3) - 4 * b));
		
	} if (fabs(a) < 5 * fabs(b)) {
		c = log(fabs(7 * a - 6 * b));
	}
	printf("A\t B\t C\t\n");
	printf("%4.2f\t %4.2f\t %4.2f\t\n", a,b,c);
	_getch();
}