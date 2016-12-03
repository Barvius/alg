// lb9.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//#include <malloc.h>
#include <locale.h>

void main(){
	setlocale(0, "Rus");
	int N, M, i, j, temp, item;
	printf("¬ведите размер n x m");
	scanf_s("%d %d",&N,&M);
	int **a;
	a = (int**)malloc(sizeof(int*)*M);
	for (i = 0; i < M; i++){
		a[i] = (int*)malloc(sizeof(int)*N);
	}
	/*
	int** a = new int* [M];
	for (i = 0; i < N; i++){
		a[i] = new int [N];
	}
	*/
	for (i = 0; i<N; i++){
		for (j = 0; j<M; j++){
			a[i][j] = rand() % 100; 
			printf("%d\t", a[i][j]);
		}                       
		printf("\n");
	}
	for (j = 0; j<M; j++){
		for (i = 0; i<N; i++) {
			if(!(a[i][j])){
				for (i = 0; i < N; i++) {
					temp = a[i][j]; // инициализируем временную переменную текущим значением элемента массива
					item = i - 1; // запоминаем индекс предыдущего элемента массива
					while (item >= 0 && a[item][j] > temp) // пока индекс не равен 0 и предыдущий элемент массива больше текущего
					{
						a[item + 1][j] = a[item][j]; // перестановка элементов массива
						a[item][j] = temp;
						item--;
					}
				}
			}
		}
	}
	printf("\n");
	for (i = 0; i<N; i++) {
		for (j = 0; j<M; j++) {
			printf("%d\t", a[i][j]);
		}
		printf("\n");
	}
	_getch();
	/*
	for (i = 0; i < M; i++) {
		free(a[i]);
	}
	*/
	free(a);
}

