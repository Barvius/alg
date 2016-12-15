// lb10.cpp: определяет точку входа для консольного приложения.
//
//#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "locale.h"
#include < string.h >
#include <ctype.h>
void main(){
	setlocale(0,"rus");
	FILE *uk;
	char a[100];
	char *ach ;
	int i = 0,p=0, str_count=0, vs_vt_count=0, vs_vs_count=0, s_max=0, s_max_addr=0;

	if (!(uk = fopen("text.txt", "r"))) {
		printf("Файл не найден....\nСоздаю...\t[ok]\n");
		uk = fopen("text.txt", "w");
		fputs("Пример использования функции fopen ", uk); // записать строку в файл
		fclose(uk);
	}	
	else
		printf("Файл найден\t[ok]\n");
	printf("-----------------------------------------------\n");
	while (fgets(a, 100, uk)) {
		printf(a);
	}
	printf("\n-----------------------------------------------\n");
	fseek(uk, 0L, SEEK_SET);
	while (fgets(a, 100, uk)) {
		//printf(a);
		ach = &a[0];
		do {
			ach = strchr(ach + p, 'а');
			//ach = strchr(ach + p, 'а');
			p++;
			if (ach == NULL) {
				//printf("Символ в строке не найден\n");
			} else {
				printf("Символ \"a\" в строке %d на позиции # %d\n", str_count +1, ach - a + 1);
				vs_vt_count++;
				vs_vs_count++;
			}
		} while (ach);
		p = 0;
		if (vs_vs_count > s_max) {
			s_max = vs_vs_count;
			s_max_addr = str_count;
		}
		vs_vs_count = 0;
		str_count++;
	}
	printf("Всего символов \"a\" в тексте %d\n", vs_vt_count);
	printf("макс в строке %d\n", s_max_addr+1);
	_getch();
}