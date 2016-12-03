// lb7.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "locale.h"
#include <malloc.h>

void main(){
	setlocale(0,"rus");
	int i, j, b[99] = {0}, m,n;
	printf("Введите размерность m n\n");
	scanf_s("%d %d", &m, &n);
	int **a = (int **)malloc(n * sizeof(int*));
	for (i = 0; i < n; i++) {
		a[i] = (int*)malloc(m * sizeof(int));
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			a[i][j] = rand() % 20;
			printf_s("%d \t", a[i][j]);
			b[i] += a[i][j];
		}
		printf("\n");
	}
	printf("Сумма каждой строки:\n");
	for (i = 0; i < m; i++) {
		printf("%d\t", b[i]);
	}
	free(a);
	_getch();
}

