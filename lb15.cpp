#include "stdafx.h" 
#include "stdio.h" 
#include "locale.h" 
#include "stdlib.h" 
#include "conio.h" 
#include "string.h" 
#include "time.h" 
#define byte 4 

void del(FILE *f, int position, int *elements) {
	int temp;
	int tell = ftell(f);
	if (ftell(f) == *elements * byte){
		fseek(f, (*elements - 1) * byte, SEEK_SET);
		fprintf(f, "%4s", "    ");
	} else {
		while (!feof(f)) {
			fscanf(f, "%4d", &temp);
			fseek(f, -2 * byte, SEEK_CUR);
			fprintf(f, "%4d", temp);
			fseek(f, byte, SEEK_CUR);
			if (ftell(f) == *elements * 4){
				fseek(f, byte**elements - byte, SEEK_SET);
				fprintf(f, "%4s","    ");
				break;
			}
		}
	}
	*elements -= 1;
}

void printfile(int elements, char *namefile) {
	FILE *f = fopen(namefile, "r");
	int mass;
	for (int i = 0; i < elements; i++) {
		fscanf(f, "%4d", &mass);
		printf("%4d", mass);
	}
	printf("\n");
	fclose(f);
}

void create(int elements, char *namefile) {
	FILE *f;
	int n;
	f = fopen(namefile, "w");
	for (int i = 0; i < elements; i++) {
		n = -10 + rand() % 20;
		fprintf(f, "%4d", n);
	}
	fclose(f);
}

int processing(int elements_1, int elements_2, char *file_first, char *file_second, char *file_result) {
	FILE *one;
	FILE *two;
	FILE *three;
	int a,b,c, i = 0, j = 0, kol = 0;
	int m=0, last_position, last_position_f1, last_position_f2;
	bool in_three;
	one = fopen(file_first, "r+");
	two = fopen(file_second, "r+");
	three = fopen(file_result, "w+");
	do {
		fscanf(one, "%4d", &a);
		fseek(two, 0, SEEK_SET);
		do {
			fscanf(two, "%4d", &b);
			if (a == b) {
				last_position = ftell(three);
				fseek(three, 0, SEEK_SET);
				do {
					in_three = false;
					fscanf(three, "%4d", &c);
					if (c == a) {
						in_three = true;
					}
				} while (!feof(three));
				if (!in_three) {
					kol++;
					fseek(three, last_position, SEEK_SET);
					fprintf(three, "%4d", a);
					last_position_f1 = ftell(one) - byte;
					del(one, last_position_f1 + byte, &elements_1);
					fseek(one, last_position_f1, SEEK_SET);
					last_position_f2 = ftell(two) - byte;
					del(two, last_position_f2 + byte, &elements_2);
					fseek(two, last_position_f2, SEEK_SET);
				}	
			}	
		} while (!feof(two));
	} while (!feof(one));
	fclose(one);
	fclose(two);
	fclose(three);
	return kol;
}

int main(int argc, char* argv[], char* argp[]) {
	int z, n;
	char *namefile;
	char *namefile_s;
	setlocale(0, "rus");
	namefile = argv[1];
	z = atoi(argv[2]);
	namefile_s = argv[3];
	n = atoi(argv[4]);
	create(z, namefile);
	create(n, namefile_s);
	printf("—одержание первого файла:\n");
	printfile(z, namefile);
	printf("—одержание второго файла:\n");
	printfile(n, namefile_s);
	z = processing(z, n, namefile, namefile_s, "rez.txt");
	printf("Ёлементы, которые записываютс€ в третий файл:\n");
	printfile(z, "rez.txt");
	_getch();
	return 0;
}