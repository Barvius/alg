#include "stdafx.h"
#include "stdio.h"
#include "math.h"
#include "conio.h"
#include "locale.h"

void main() {
	setlocale(0, "rus");
	int a, b, c, count = 0;
	float f=0, dx, xn, xk, x, e=0,k=1;
	printf("Введите A B C\n");
	scanf_s("%d %d %d", &a, &b, &c);

	do {
		printf("\nВведите Xn Xk Dx\n");
		scanf_s("%f %f %f", &xn, &xk, &dx);
		_getch();
	} while (!((xn<xk&&dx>0)||(xn>xk&&dx<0)));
	if (dx<0) {
		k = -1;
	}
	printf("\nA\t B\t C\t X\t\t F\n\n");
	x = xn;
	point:
		if (x < 10.0 && b != 0) {
			f = a*x + b;
		} else if (x > 10.0 && b == 0) {
			f = (1.0 + c) / x;
		} else {
			if (c == 0) {
				printf("%d\t %d\t %d\t %f\t Нет решений\n", a, b, c, x); goto to_end;
			} else {
				f = -(pow(x, 2)) / c;
			}
		}
			printf("%d\t %d\t %d\t %f\t %f\n", a, b, c, x, f);
		to_end:
			
		x += dx;
		//printf("%f\n", x);
		
		if (f > 0) {
			count++;
		}
		
			if (x*k <= xk*k) {
				goto point;
			}
		
	printf("Количество F>0 = %d\n", count);
	_getch();
}