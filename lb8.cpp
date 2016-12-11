// lb8.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "locale.h"

void main() {
	setlocale(0, "rus");
	int i, j,k,l, a[12][6], m = 12, n = 6,max_1,max_2;
	max_1 = max_2 = 0.00000001; 
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			a[i][j] = rand() % 20;
			printf("%d \t", a[i][j]);
			if (a[i][j] > max_1) {
				max_2 = max_1;
				max_1 = a[i][j];
			}
		}
		printf("\n");
	}
	printf("\nМаксимальные элементы: %d, %d\n\n", max_1, max_2);
	for (i = m; i > 0; i--) {
		for (j = 0; j < n; j++) {
			if (a[i][j] == max_2) {
				for (k = i; i < m ; i++) {
					for (l = 0; l < n; l++) {
						a[i][l] = a[i + 1][l];
					}
				}
				m--;
			}
		}
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			printf("%d \t", a[i][j]);
		}
		printf("\n");
	}
	printf("\n" );
	for (i = m; i > 0; i--) {
		for (j = 0; j < n; j++) {
			if (a[i][j] == max_1) {
				for (k = i; i < m; i++) {
					for (l = 0; l < n; l++) {
						a[i][l] = a[i + 1][l];
					}
				}
				m--;
			}
		}
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			printf("%d \t", a[i][j]);
		}
		printf("\n");
	}
	_getch();
}