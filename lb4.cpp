#include "stdafx.h"
#include "stdio.h"
#include "math.h"
#include "conio.h"
#include "locale.h"

void main() {
	setlocale(0, "rus");
	int c, count = 0;
	float f, dx, xn, xk, x, da ,an ,ak ,a ,db ,bn ,bk ,b;
	printf("ВведитеC\n");
	scanf_s("%d",&c);
	printf("\nВведите An Ak Da\n");
	scanf_s("%f %f %f", &an, &ak, &da);
	printf("\nВведите Bn Bk Db\n");
	scanf_s("%f %f %f", &bn, &bk, &db);
	printf("\nВведите Xn Xk Dx\n");
	scanf_s("%f %f %f", &xn, &xk, &dx);
	printf("\nA\t\t B\t\t C\t\t X\t\t F\n\n");
	for (b = bn; b <= bk; b += db) {
			a = an;
			do {
				x = xn;
				while (x <= xk) {
					if (x < 10 && b != 0) {
						f = a*x + b;
					} else if (x > 10 && b == 0) {
						f = (1.0 + c) / x;
					} else {
						if (c == 0) {
							printf("%f\t %f\t %d\t %f\t Нет решений\n", a, b, c, x);
							x += dx;
							continue;
						} else {
							f = -(pow(x, 2)) / c;
						}
					}
					printf("%f\t %f\t %d\t %f\t %f\n", a, b, c, x, f);
					if (f > 0) {
						count++;
					}
				x += dx;
				}
			a += da;
			} while (a <= ak);
	}
	printf("Количество F>0 = %d\n", count);
	_getch();
}