// lb10.cpp: определяет точку входа для консольного приложения.
//
//#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "locale.h"
#include "string.h"

void main(){
	setlocale(0,"rus");
	const int rows = 10, col = 100;
	FILE *f;
	char a[rows][col] = { NULL }, b[100], znak[] = { '.', ',', ':' };
	char *ykaz ;
	int j, i, p, vs_vt_count, vs_vs_count, s_max, s_max_addr;
	j = i = p = vs_vt_count = vs_vs_count = s_max = s_max_addr = 0;
	if (!(f = fopen("text.txt", "r"))) {
		printf("Файл не найден....\n");
	}
	printf("-----------------------------------------------\n");
	while (fgets(a[i], 100, f)) {
		printf(a[i]);
		i++;
	}
	fclose(f);
	printf("\n-----------------------------------------------\n");
	for (i = 0; i < rows-1; i++, p = vs_vs_count = 0) {
			if (a[i][0]) {
				ykaz = &a[i][0];
				do {
					ykaz = strchr(ykaz + p, 'а');
					p++;
					if (ykaz) {
						vs_vt_count++;
						vs_vs_count++;
					}
				} while (ykaz);
				if (vs_vs_count > s_max) {
					s_max = vs_vs_count;
					s_max_addr = i;
				}
				printf("Символов \"a\" в строке %d - %d\n", i + 1, vs_vs_count);
			}
	}
	printf("Всего символов \"a\" в тексте %d\n", vs_vt_count);
	printf("макс в строке %d\n", s_max_addr + 1);
	for (i = 0; i < strlen(znak); i++, p = 0) {
		ykaz = &a[s_max_addr][0];
		do {
			ykaz = strchr(ykaz + p, znak[i]);
			p++;
			if (ykaz) {
				*ykaz = '*';
			}
		} while (ykaz);
	}
	printf("-----------------------------------------------\n");
	f = fopen("out.txt", "w+");
	for (i = 0; i < rows - 1; i++) {
		if (a[i][0]) {
			printf(a[i]);
			fputs(a[i], f);
		}
	}
	fclose(f);
	printf("\n-----------------------------------------------\n");
	_getch();
}