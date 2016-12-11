#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "conio.h"
#include "locale.h"

void main() {
	setlocale(0, "rus");
	//const int m_len = 45;
	int len=0, d;
	do {
		printf_s("Ввести размер массива\n");
		scanf_s("%d", &len);
	} while (len < 1 || len>46);
	const int m_len = len;
	int i, num_start, num_end, count=0, last_count=0 ;
	int * x = new int[len];
	for ( i = 0; i < m_len; i++) {
		x[i] = rand() % 2;
		printf("%d ", x[i]);
	}
	for (i = 0; i < m_len; i++){
		if (x[i] == 0) {
			count++;
		} else {
			if (count > last_count) {
				last_count = count;
				num_end = i;
				num_start = i + 1 - count;
			}
			count = 0;
		}
	}
	if (count > last_count) {
		last_count = count;
		num_end = i;
		num_start = i + 1 - count;
	}
	printf("\nНулей максимально подряд: %d\nНачиная с: %d\nЗаканчивая: %d",last_count,num_start,num_end);
	_getch();
}