#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "locale.h"

void main() {
	setlocale(0, "rus");
	int x[4] = { 0 }, y[4] = { 0 }, i,n=0,j=1;
	float a[6] = { 0 }, b[6] = { 0 }, d[3] = { 1 };
	int input[3][4] = { {1,2,3,4},{ 1,3,2,4 },{ 1,4,2,3 } };
	for (i = 0; i <= 3; i++) {
		printf("Ввести координаты %d точки Х У\n", i + 1);
		scanf_s("%d %d", &x[i], &y[i]);
	}
	a[0] = y[1] - y[0];
	a[1] = y[3] - y[2];
	b[0] = x[1] - x[0];
	b[1] = x[3] - x[2];
	a[2] = y[0] - y[2];
	a[3] = y[1] - y[3];
	b[2] = x[0] - x[2];
	b[3] = x[1] - x[3];
	a[4] = y[3] - y[0];
	a[5] = y[2] - y[1];
	b[4] = x[0] - x[3];
	b[5] = x[1] - x[2];
	for (i = 0; i < 3; i++){
		d[i] = a[n]*b[j] - b[n]*a[j];
		n += 2;
		j += 2;
		if (d[i] == 0) {
			printf("Прямые проходящие через точки (%d,%d) (%d,%d) параллельны \n", input[i][0], input[i][1], input[i][2], input[i][3]);
		}
	}
	_getch();
}