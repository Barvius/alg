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
	FILE *f_in, *f_out;
	char a[100], b[100], znak[] = { '.', ',', ':' };
	char *ykaz ;
	int i, p, str_count, vs_vt_count, vs_vs_count, s_max, s_max_addr;
	i = p = str_count = vs_vt_count = vs_vs_count = s_max = s_max_addr = 0;

	if (!(f_in = fopen("text.txt", "r"))) {
		printf("Файл не найден....\nСоздаю...\t[ok]\n");
		f_in = fopen("text.txt", "w");
		fputs("Пример использования функции fopen ", f_in);
		fclose(f_in);
	} else {
		printf("Файл найден\t[ok]\n");
	}
	printf("-----------------------------------------------\n");
	while (fgets(a, 100, f_in)) {
		printf(a);
	}
	printf("\n-----------------------------------------------\n");
	fseek(f_in, 0L, SEEK_SET);
	while (fgets(a, 100, f_in)) {
		ykaz = &a[0];
		do {
			ykaz = strchr(ykaz + p, 'а');
			p++;
			if (ykaz){
				printf("Символ \"a\" в строке %d на позиции # %d\n", str_count +1, ykaz - a + 1);
				vs_vt_count++;
				vs_vs_count++;
			}
		} while (ykaz);
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
	fseek(f_in, 0L, SEEK_SET);
	i = -1;
	do {
		fgets(a, 100, f_in);
		i++;
	} while (i < s_max_addr);
	for ( i = 0; i < strlen(znak); i++){
		ykaz = &a[0];
		do {
			ykaz = strchr(ykaz + p, znak[i]);
			p++;
			if (ykaz) {
				*ykaz = '*';
			}
		} while (ykaz);
		p = 0;
	}
	printf(a);
	f_out = fopen("out.txt", "w+");
	str_count = 0;
	fseek(f_in, 0L, SEEK_SET);
	while (fgets(b, 100, f_in)) {
		if (str_count == s_max_addr) {
			fputs(a, f_out);
			str_count++;
			continue;
		}
		fputs(b, f_out);
		str_count++;
	}
	fclose(f_out);
	fclose(f_in);
	_getch();
}