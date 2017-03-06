#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "locale.h"

void FillRand(int *arr, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			*(arr+i*n+j) = rand() % 20;
		}
	}
}

void PrintArr(int *arr, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf(" %-2d ", *(arr + i*n+j));
		}
		printf("\n");
	}
	printf("\n");
}

float SrAr(int *arr, int n, int m){
	float S = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			S += *(arr + i*n + j);
		}
	}
	return S / (m*n);
}

void SrArP(int *arr, int n, int m, float *S) {
	*S = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			*S += *(arr + i*n + j);
		}
	}
	*S /= (m*n);
}

float Percent(int *arr, int n, int m, float S) {
	float count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (*(arr + i*n + j) > S){
				count++;
			}
		}
	}
	return count * 100 / (m*n);
}

void PercentP(int *arr, int n, int m, float S, float *P) {
	float count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (*(arr + i*n + j) > S) {
				count++;
			}
		}
	}
	*P = count * 100 / (m*n);
}

void main() {
	setlocale(0, "RUS");
	int arr_1[10][10], n_1 = 10, m_1 = 10;
	FillRand(&arr_1[0][0], n_1, m_1);
	PrintArr(&arr_1[0][0], n_1, m_1);
	printf("Ср ар. - %.1f\n", SrAr(&arr_1[0][0], n_1, m_1));
	printf("Больше чем ср.ар - %.1f%%\n", Percent(&arr_1[0][0], n_1, m_1, SrAr(&arr_1[0][0], n_1, m_1)));
	float S,P;
	SrArP(&arr_1[0][0], n_1, m_1, &S);
	PercentP(&arr_1[0][0], n_1, m_1, S, &P);
	printf("Ср ар. - %.1f\n", S);
	printf("Больше чем ср.ар - %.1f%%\n", P);
	_getch();
}

