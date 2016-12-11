#include "stdafx.h"
#include "stdio.h"
#include "math.h"
#include "conio.h"
#include "locale.h"

void main() {
	setlocale(0, "rus");
	int a, b, c, x;
	float f;
	scanf_s("%d %d %d %d",&a,&b,&c,&x);
	if (x<10&&b!=0) {
		f = a*x + b;
	} else if (x>10&&b==0) {
		f = (1.0 + c) / x;
	} else {
		if (c==0) {
			printf("Нет решений\n"); goto toend;
		} else {
			f = -(pow(x, 2)) / c;
		}
	}
	
		printf("A\t B\t C\t X\t F\n\n");
		printf("%d\t %d\t %d\t %d\t %f\n", a, b, c, x, f);
	toend:
		printf("A\t B\t C\t X\n");
		printf("%d\t %d\t %d\t %d\n", a, b, c, x);
	
	_getch();
}