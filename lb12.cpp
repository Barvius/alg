// lb12.cpp: определяет точку входа для консольного приложения.
//
/* Пример базы
Пискунов И.И ИМ-13 1 1 1 1 1
Писарев В.В ВА-14 2 2 2 2 2
Сидоров И.А КМ-23 3 3 3 3 3
Самсанов Х.Ч ВА-12 4 4 4 4 4
Пирожков С.К АКМ-03 5 5 5 5 5
*/

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

typedef struct {
	char LastName[21] = { NULL };
	char FirstName[4] = { NULL };
	char Group[7] = { NULL };
	int score[5] = { NULL };
	float s_score = { NULL };
} Student;

void MainMenu();
void ReadDB(Student student[]);
void ShowRecords(Student student[], int rows_db);
void AddRecords();
void DelRecords(Student student[], int rows_db);
void PostMenuHandler();
void ShowFiltredList(Student *SortStudent, int rows_db);
void ShowGodStudents(Student student[], int rows_db);
int AllRows();

void PostMenuHandler() {
	printf("-------------------------------------\n");
	printf("Для возврата в главное меню нажмите m\n");
	printf("Для выхода нажмите q\n");
	while (true) {
		switch (_getch()) {
		case 'm':
			MainMenu();
			break;
		case 'q':
			exit(0);
			break;
		}
	}
}

void ReadDb(Student student[]) {
	FILE *f;
	int i = 0;
	if (!(f = fopen("db.txt", "r"))) {
		printf("Файл не найден....\n");
		system("pause");
		exit(0);
	} else {
		while (fscanf(f, "%s %s %s %d %d %d %d %d\n", student[i].LastName, student[i].FirstName, student[i].Group, &student[i].score[0], &student[i].score[1], &student[i].score[2], &student[i].score[3], &student[i].score[4]) != EOF) {
			student[i].s_score = (student[i].score[0] + student[i].score[1] + student[i].score[2] + student[i].score[3] + student[i].score[4]) / 5.0;
			i++;
		}
		fclose(f);
	}
}

void ShowRecords(Student student[],int rows_db) {
	system("cls");
	printf("Список студентов\n");
	printf("------------------------\n");
	int i = 0;
	printf("+----+----------------------+-----+--------+---+---+---+---+---+------+\n");
	printf("| ID | Фамилия              | И.О | Группа |                   |  СБ  |\n");
	while (i < rows_db) {
		printf("+----+----------------------+-----+--------+---+---+---+---+---+------+\n");
		printf("| %-2d | %-20s | %-3s | %-6s | %d | %d | %d | %d | %d | %.2f |\n", i, student[i].LastName, student[i].FirstName, student[i].Group, student[i].score[0], student[i].score[1], student[i].score[2], student[i].score[3], student[i].score[4], student[i].s_score);
		i++;
	}
	printf("+----+----------------------+-----+--------+---+---+---+---+---+------+\n");

}

void DelRecords(Student student[], int rows_db) {
	system("cls");
	printf("Удаление записи\n");
	printf("---------------\n");
	FILE *f;
	int i = 0, rm_row;
	ShowRecords(student, rows_db);
	printf("Введите ID удаляемой записи\n");
	scanf("%d", &rm_row);
	for (i = rm_row; i < rows_db - 1; i++) {
		student[i] = student[i + 1];
	}
	f = fopen("db.txt", "w");
	i = 0;
	while (i < rows_db - 1) {
		fprintf(f, "%s %s %s %d %d %d %d %d\n", student[i].LastName, student[i].FirstName, student[i].Group, student[i].score[0], student[i].score[1], student[i].score[2], student[i].score[3], student[i].score[4]);
		i++;
	}
	fclose(f);
	printf("Запись с ID %d устпешно удалена\n", rm_row);
}

void AddRecords() {
	system("cls");
	Student NewStudent;
	FILE *f;
	printf("Добавление новой записи\n");
	printf("-----------------------\n");
	printf("Фамилия:  ");
	scanf("%s20", NewStudent.LastName);
	printf("\nИнициалы:  ");
	scanf("%s3", NewStudent.FirstName);
	printf("\nГруппа:  ");
	scanf("%s6", NewStudent.Group);
	printf("\nПервая оценка:  ");
	scanf("%d", &NewStudent.score[0]);
	printf("\nВторая оценка:  ");
	scanf("%d", &NewStudent.score[1]);
	printf("\nТретья оценка:  ");
	scanf("%d", &NewStudent.score[2]);
	printf("\nЧетвертая оценка:  ");
	scanf("%d", &NewStudent.score[3]);
	printf("\nПятая оценка:  ");
	scanf("%d", &NewStudent.score[4]);
	f = fopen("db.txt", "at");
	fprintf(f, "%s %s %s %d %d %d %d %d\n", NewStudent.LastName, NewStudent.FirstName, NewStudent.Group, NewStudent.score[0], NewStudent.score[1], NewStudent.score[2], NewStudent.score[3], NewStudent.score[4]);
	fclose(f);
	printf("\nЗапись успешно добавлена\n");
}

void ShowFiltredList(Student *SortStudent,int rows_db) {
	bool fl = 1;
	Student TmpStudent;
	while (fl) {
		fl = 0;
		for (int i = 0; i < rows_db - 1 ; i++) {
			if (strcmp(SortStudent[i].Group, SortStudent[i + 1].Group) > 0) {
				fl = 1;
				TmpStudent = SortStudent[i];
				SortStudent[i] = SortStudent[i + 1];
				SortStudent[i + 1] = TmpStudent;	
			}
		}
	}
	ShowRecords(SortStudent, rows_db);
}

void ShowGodStudents(Student student[],int rows_db) {
	system("cls");
	printf("Студенты с средним баллом > 4\n");
	printf("-----------------------------\n");
	int i = 0, j = 0;
	while (i < rows_db) {
		if (student[i].s_score >= 4.0) {
			j++;
		}
		i++;
	}
	if (j) {
		i = 0;
		printf("+----------------------+--------+\n");
		printf("| Фамилия              | Группа |\n");
		while (i < rows_db) {
			if (student[i].s_score >= 4.0) {
				printf("+----------------------+--------+\n");
				printf("| %-20s | %-6s |\n", student[i].LastName, student[i].Group);
			}
			i++;
		}
		printf("+----------------------+--------+\n");
	} else {
		printf("Увы и ах...\nСтуденты данного учебного заведения,\nпредпочитают проводить пары в столовой.\n");
	}

}

int AllRows() {
	FILE *f;
	char tmp[100];
	int i = 0;
	if (!(f = fopen("db.txt", "r"))) {
		printf("Файл не найден....\n");
		system("pause");
		exit(0);
	} else {
		while(fgets(tmp, 100, f)){
			i++;
		}
		fclose(f);
		return i;
	}
}

void MainMenu() {
	system("cls");
	int rows_db = AllRows();
	Student *student = new Student[rows_db];
	ReadDb(student);
	printf("Выберите действие:\n");
	printf("------------------\n");
	printf("l - Отобразить все записи\n");
	printf("a - Добавить запись\n");
	printf("d - Удалить запись\n");
	printf("s - Показать товарищей с средним баллом > 4\n");
	printf("f - Сортировка по названию группы\n");
	printf("q - Выход\n");
	printf("\n");
	while (true) {
		switch (_getch()) {
		case 'l':
			ShowRecords(student,rows_db);
			PostMenuHandler();
			break;
		case 'a':
			AddRecords();
			PostMenuHandler();
			break;
		case 'd':
			DelRecords(student, rows_db);
			PostMenuHandler();
			break;
		case 's':
			ShowGodStudents(student, rows_db);
			PostMenuHandler();
			break;
		case 'f':
			ShowFiltredList(student, rows_db);
			PostMenuHandler();
			break;
		case 'q':
			exit(0);
			break;
		}
	}

}

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color F0");
	MainMenu();
}

