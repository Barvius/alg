#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "locale.h"

void main() {
	setlocale(0, "rus");
	int x[3] = { 0 }, y[3] = { 0 },i;
	float a, b,a1,b1,d;
	for ( i = 0; i <= 3; i++){
		printf("Ввести координаты %d точки Х У\n",i+1);
		scanf_s("%d %d", &x[i], &y[i]);
	}
	a = y[1] - y[0];
	a1 = y[3] - y[2];
	b = x[1] - x[0];
	b1 = x[3] - x[2];
	d = a*b1 - b*a1;
	if (d==0){
		printf("Прямые параллельны %f",d);
	} else {
		printf("Не параллельны %f", d);
	}
	
	_getch();
}