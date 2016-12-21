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
	FILE *f;
	char b[100] = { NULL }, znak[] = { '.', ',', ':' };
	char *ykaz;
	char **a;
	int j, i, vs_vt_count, vs_vs_count, s_max, s_max_addr,col_i;
	j = i = vs_vt_count = vs_vs_count = s_max = s_max_addr=col_i = 0;
	if (!(f = fopen("text.txt", "r"))) { //открываем файл, если его нет то пишем "Файл не найден...." и закрываем консоль.
		printf("Файл не найден....\n");
	} else {
		// если файл найден, тогда работаем
		while (fgets(b, 100, f)) { //считаем кол-во строк  в файле
			col_i++;
		}
		char **a = new char*[col_i];// динамически выделяем память под строки
		fseek(f, 0L, SEEK_SET);// перемещаем указатель на начало файла, дабы считать его еще раз
		while (fgets(b, 100, f)) { // опять читаем файл для выделения столбцов и заполнения основного массива
			a[j] = new char[strlen(b)+1];// выделяем память под столбцы
			strcpy(a[j], b);// копируем содержимое из временной переменнной Б в переменную А
			j++;
		}
		
	printf("-----------------------------------------------\n");
	//выводим содержимое массива в который считали файл
	for (i = 0; i < col_i;i++) {
		puts(a[i]);
	}
	fclose(f);// файл закрыли
	printf("\n-----------------------------------------------\n");
	// далее в зависимости от тз, тут идет поиск в какой строке больше всего символов "а", и сколько всего по тексту в целом
	for (i = 0; i < col_i; i++, vs_vs_count = 0) {
				ykaz = a[i];
				do {
					ykaz = strchr(ykaz , 'а');
					if (ykaz) { 
						vs_vt_count++;
						vs_vs_count++;
						ykaz++;
					}
				} while (ykaz);
				if (vs_vs_count > s_max) {
					s_max = vs_vs_count;
					s_max_addr = i;
				}
				printf("Символов \"a\" в строке %d - %d\n", i + 1, vs_vs_count);
	}
	printf("Всего символов \"a\" в тексте %d\n", vs_vt_count);
	printf("макс в строке %d\n", s_max_addr + 1);
	// далее замена всех знаков препинания на символ "*" в строке, где максимально букв "а", знаки препинания содержатся в массиве znak
	for (i = 0; i < strlen(znak); i++) {
		ykaz = a[s_max_addr];
		do {
			ykaz = strchr(ykaz, znak[i]);
			if (ykaz) {
				*ykaz = '*';
				ykaz++;
			}
		} while (ykaz);
	}
	printf("-----------------------------------------------\n");
	// вывод измененного текста и запись его в файл
	f = fopen("out.txt", "w+");// открываем файл в котором будут результаты работы программы
	for (i = 0; i < col_i; i++) {
		if (a[i][0]) {// поидеи можно и без него, пробуй
			printf(a[i]); 
			fputs(a[i], f);// построчно загоняем массив в файл
		}
	}
	fclose(f);// закрываем 
	printf("\n-----------------------------------------------\n");
	free(a);// освобождаем переменнную с текстом
	_getch();
	}
}