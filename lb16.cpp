#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

void dyn(float **&arr, int *n, int *m) {
	printf("Размерность n x m\n");
	scanf_s("%d %d", n, m);
	arr = new float * [*n];
	for (int i = 0; i < *n; i++){
		arr[i] = new float[*m];
	}
}

void print(float **&arr, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%f\t", arr[i][j]);
		}
		printf("\n");
	}
}

float TZ(float **&arr, int n, int m) {
	float max = 0, sum=0;
	int max_addr;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j]>max) {
				max = arr[i][j];
				max_addr = i;
			}
		}
	}
	for (int j = 0; j < m; j++) {
		sum += arr[max_addr][j];
	}
	return sum;
}	

void rand(float **&arr, int n, int m, char type) {
	switch (type){
	case 'x':
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				arr[i][j] = 5.7*j*sinf((float)i / 2) + 9.3*i*cosf((float)j / 2);
			}
		}
		break;
	case 'y':
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				arr[i][j] = 12.1*j*sinf((float)i / 2) - 3.8 *i*cosf((float)j / 2);
			}
		}
		break;
	case 'z':
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				arr[i][j] = 10.5*j*sinf((float)i / 2) + 23.4*i*cosf((float)j / 2);
			}
		}
		break;
	}
}

int main(){
	setlocale(0,"rus");
	float max[3] = {NULL};
	int x_n, x_m, y_n, y_m, z_n, z_m;
	float **x, **y, **z;
	dyn(x,&x_n,&x_m);
	rand(x, x_n, x_m, 'x');
	max[0] = TZ(x, x_n, x_m);
	print(x, x_n, x_m);
	printf("сумма элементов строки с наибольшим элементом %f\n", max[0]);
	dyn(y, &y_n, &y_m);
	rand(y, y_n, y_m, 'y');
	max[1] = TZ(y, y_n, y_m);
	print(y, y_n, y_m);
	printf("сумма элементов строки с наибольшим элементом %f\n", max[1]);
	dyn(z, &z_n, &z_m);
	rand(z, z_n, z_m, 'z');
	max[2] = TZ(z, z_n, z_m);
	print(z, z_n, z_m);
	printf("сумма элементов строки с наибольшим элементом %f\n", max[2]);
	system("pause");
    return 0;
}

