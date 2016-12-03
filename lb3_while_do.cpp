#include "stdafx.h"
#include "stdio.h"
#include "math.h"
#include "conio.h"
#include "locale.h"

void main() {
	setlocale(0, "rus");
	int a, b, c, count=0;
	float f, dx, xn, xk, x;
	printf("Введите A B C\n");
	scanf_s("%d %d %d", &a, &b, &c);
	printf("\nВведите Xn Xk Dx\n");
	scanf_s("%f %f %f", &xn, &xk, &dx);
	printf("\nA\t B\t C\t X\t\t F\n\n");
	x = xn;
	while (x <= xk) {
		if (x < 10.0 && b != 0) {
			f = a*x + b;
		} else if (x > 10.0 && b == 0) {
			f = (1.0 + c) / x;
		} else {
			if (c == 0) {
				printf("%d\t %d\t %d\t %f\t Нет решений\n", a, b, c, x); 
				x += dx; 
				continue;
			} else {
				f = -(pow(x, 2)) / c;
			}
		}
		printf("%d\t %d\t %d\t %f\t %f\n", a, b, c, x, f);
		x += dx;
		if (f>0) {
			count++;
		}
	}
	printf("Количество F>0 = %d\n", count);
	_getch();
}