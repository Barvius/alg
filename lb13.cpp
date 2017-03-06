#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "locale.h"

void FillRand(int *arr, int n) {
	for (int i = 0; i < n; i++){
		arr[i] = rand() % 20;
	}
}

void PosMove(int *arr, int n) {
	int i = 0, j = n - 1, l;
	while (i < j) {
		while (arr[i] % 2)i++;
		while (arr[j] % 2)j--;
		if (!(arr[i] % 2) && !(arr[j] % 2)) {
			l = arr[i];
			arr[i] = arr[j];
			arr[j] = l;
			i++, j--;
		}
	}
}

void PrintArr(int *arr, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void main(){
	setlocale(0, "RUS");
	int arr_1[10], n_1 = 10;
	printf("Первый массив\n");
	FillRand(arr_1,n_1);
	PrintArr(arr_1, n_1);
	PosMove(arr_1, n_1);
	PrintArr(arr_1, n_1);
	int arr_2[20], n_2 = 20;
	printf("Второй массив\n");
	FillRand(arr_2, n_2);
	PrintArr(arr_2, n_2);
	PosMove(arr_2, n_2);
	PrintArr(arr_2, n_2);
	int arr_3[5], n_3 = 5;
	printf("Третий массив\n");
	FillRand(arr_3, n_3);
	PrintArr(arr_3, n_3);
	PosMove(arr_3, n_3);
	PrintArr(arr_3, n_3);
	_getch();
}

