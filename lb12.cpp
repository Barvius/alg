// lb12.cpp: определяет точку входа для консольного приложения.
//
/* Пример базы
1 Пискунов И.И ИМ-13 1 1 1 1 1
2 Писарев В.В ВА-14 2 2 2 2 2
3 Сидоров И.А КМ-23 3 3 3 3 3
4 Самсанов Х.Ч ВА-12 4 4 4 4 4
5 Пирожков С.К АКМ-03 5 5 5 5 5
*/

#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "conio.h"
#include "string.h"
#include "locale.h"
#include <windows.h>

typedef struct {
	char LastName[50] = { NULL };
	char FirstName[50] = { NULL };
	char Group[10] = { NULL };
	int score[5] = { NULL };
	float s_score = { NULL };
	int id = { NULL };
} Student;

void MainMenu();
void ReadDB(Student);
void ShowAllRecords(Student);
void AddRecords(Student);
void DelRecords(Student);
void PostMenuHandler();
void ShowFiltredList(Student);
void ShowGodStudents(Student);
void PostMenuHandler();

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
		default:
			break;
		}
	}
}

 void ReadDb(Student student[]) {
	FILE *f;
	int i=1;
	if (!(f = fopen("db.txt", "r"))) {
		printf("Файл не найден....\n");
		system("pause");
		exit(0);
	} else {
		while (fscanf(f, "%d %s %s %s %d %d %d %d %d\n", &student[i].id, student[i].LastName, student[i].FirstName, student[i].Group, &student[i].score[0], &student[i].score[1], &student[i].score[2], &student[i].score[3], &student[i].score[4]) != EOF) {
			student[i].s_score = (student[i].score[0] + student[i].score[1] + student[i].score[2] + student[i].score[3] + student[i].score[4] ) / 5.0;
			i++;
		}
		fclose(f);
	}
}

 void ShowAllRecords(Student student[]) {
	 system("cls");
	 printf("Список студентов и баллы\n");
	 printf("------------------------\n");
	 int i = 1;
	 printf("+----+-----------------+----------+--------+---+---+---+---+---+------+\n");
	 printf("| ID | Фамилия         | Инициалы | Группа |                   |  СБ  |\n");
	 while (student[i].id){
		 printf("+----+-----------------+----------+--------+---+---+---+---+---+------+\n");
		 printf("| %-2d | %-15s | %-8s | %-6s | %d | %d | %d | %d | %d | %.2f |\n", student[i].id, student[i].LastName, student[i].FirstName, student[i].Group, student[i].score[0], student[i].score[1], student[i].score[2], student[i].score[3], student[i].score[4], student[i].s_score);
		 i++;
	 }
	 printf("+----+-----------------+----------+--------+---+---+---+---+---+------+\n");
	 
 }

 void DelRecords(Student student[]) {
	 system("cls");
	 printf("Удаление записи\n");
	 printf("---------------\n");
	 FILE *f;
	 int i = 1, id, rm_row, row;
	 ShowAllRecords(student);
	 printf("Введите ID удаляемой записи\n");
	 scanf("%d", &id);
	 i = 1;
	 while (student[i].id) {
		 if (id == student[i].id) {
			 rm_row = i;
		 }
		 i++;
	 }
	 row = i;
	 for ( i = rm_row; i < row; i++){
		 student[i].id = student[i + 1].id;
		 strcpy(student[i].Group, student[i + 1].Group);
		 strcpy(student[i].FirstName, student[i + 1].FirstName);
		 strcpy(student[i].LastName, student[i + 1].LastName);
		 student[i].s_score = student[i + 1].s_score;
		 for (int k = 0; k < 5; k++) {
			 student[i].score[k] = student[i + 1].score[k];
		 }
	 }
	 f = fopen("db.txt", "w");
	 i = 1;
	 while (student[i].id) {
		 fprintf(f, "%d %s %s %s %d %d %d %d %d\n", student[i].id, student[i].LastName, student[i].FirstName, student[i].Group, student[i].score[0], student[i].score[1], student[i].score[2], student[i].score[3], student[i].score[4]);
		 i++;
	 }
	 fclose(f);
	 printf("Запись с ID %d устпешно удалена\n", id);

 }

 void AddRecords(Student student[]) {
	 system("cls");
	 printf("Добавление новой записи\n");
	 printf("-----------------------\n");
	 FILE *f;
	 int i = 1;
	 while (student[i].id) {
		 i++;
	 }
	 student[i].id = student[i-1].id + 1;
	 printf("Фамилия:  ");
	 scanf("%s50", student[i].LastName);
	 printf("\nИнициалы:  ");
	 scanf("%s50", &student[i].FirstName);
	 printf("\nГруппа:  ");
	 scanf("%s10", &student[i].Group);
	 printf("\nПервая оценка:  ");
	 scanf("%d", &student[i].score[0]);
	 printf("\nВторая оценка:  ");
	 scanf("%d", &student[i].score[1]);
	 printf("\nТретья оценка:  ");
	 scanf("%d", &student[i].score[2]);
	 printf("\nЧетвертая оценка:  ");
	 scanf("%d", &student[i].score[3]);
	 printf("\nПятая оценка:  ");
	 scanf("%d", &student[i].score[4]);
	 i = 1;
	 f = fopen("db.txt", "w");
	 while (student[i].id) {
		 fprintf(f, "%d %s %s %s %d %d %d %d %d\n", student[i].id, student[i].LastName, student[i].FirstName, student[i].Group, student[i].score[0], student[i].score[1], student[i].score[2], student[i].score[3], student[i].score[4]);
		 i++;
	 }
	 fclose(f);
	 printf("\nЗапись успешно добавлена\n");
 }

 void ShowFiltredList(Student *SortStudent) {
	 int i=1,row;
	 bool fl = 1;
	 while (SortStudent[i].id) {
		 i++;
	 }
	 row = i;
	 while (fl){
		 fl = 0;
		 for (int i = 1; i < row -1; i++){
			 if (strcmp(SortStudent[i].Group , SortStudent[i + 1].Group) > 0){
				 fl = 1;
				 char Group[sizeof(SortStudent[i].Group)];
				 strcpy(Group, SortStudent[i].Group);
				 strcpy(SortStudent[i].Group, SortStudent[i+1].Group);
				 strcpy(SortStudent[i + 1].Group, Group);
				 char FirstName[sizeof(SortStudent[i].FirstName)];
				 strcpy(FirstName, SortStudent[i].FirstName);
				 strcpy(SortStudent[i].FirstName, SortStudent[i + 1].FirstName);
				 strcpy(SortStudent[i + 1].FirstName, FirstName);
				 char LastName[sizeof(SortStudent[i].LastName)];
				 strcpy(LastName, SortStudent[i].LastName);
				 strcpy(SortStudent[i].LastName, SortStudent[i + 1].LastName);
				 strcpy(SortStudent[i + 1].LastName, LastName);
				 float s_score = SortStudent[i].s_score;
				 SortStudent[i].s_score = SortStudent[i + 1].s_score;
				 SortStudent[i + 1].s_score = s_score;
				 int id = SortStudent[i].id;
				 SortStudent[i].id = SortStudent[i + 1].id;
				 SortStudent[i + 1].id = id;
				 for (int k = 0; k < 5; k++){
					 int tmp = SortStudent[i].score[k];
					 SortStudent[i].score[k] = SortStudent[i + 1].score[k];
					 SortStudent[i + 1].score[k] = tmp;
				 }
			 }
		 }
	 }
	 ShowAllRecords(SortStudent);
 }

 void ShowGodStudents(Student student[]) {
	 system("cls");
	 printf("Студенты с средним баллом > 4\n");
	 printf("-----------------------------\n");
	 int i = 1, j = 0;
	 while (student[i].id) {
		 if (student[i].s_score >= 4.0) {
			 j++;
		 }
		 i++;
	 }
	 if (j){
		 i = 1;
		 printf("+-----------------+--------+\n");
		 printf("| Фамилия         | Группа |\n");
		 while (student[i].id) {
			 if (student[i].s_score >= 4.0) {
				 printf("+-----------------+--------+\n");
				 printf("| %-15s | %-6s |\n", student[i].LastName, student[i].Group);
			 }
			 i++;
		 }
		 printf("+-----------------+--------+\n");
	 } else {
		 printf("Увы и ах...\nСтуденты данного учебного заведения,\nпредпочитают проводить пары в столовой.\n");
	 }
	 
 }

 void MainMenu() {
	 system("cls");
	 Student student[10];
	 ReadDb(student);
	 printf("Выберите действие\n");
	 printf("l - Отобразить все записи\n");
	 printf("a - Добавить запись\n");
	 printf("d - Удалить запись\n");
	 printf("s - Показать товарищей с среднем баллом > 4\n");
	 printf("f - Сортировка по названию группы\n");
	 printf("\n");
	 while (true){
		 switch (_getch()) {
		 case 'l':
			 ShowAllRecords(student);
			 PostMenuHandler();
			 break;
		 case 'a':
			 AddRecords(student);
			 PostMenuHandler();
			 break;
		 case 'd':
			 DelRecords(student);
			 PostMenuHandler();
			 break;
		 case 's':
			 ShowGodStudents(student);
			 PostMenuHandler();
			 break;
		 case 'f':
			 ShowFiltredList(student);
			 PostMenuHandler();
			 break;
		 case 'q':
			 exit(0);
			 break;
		 default:
			 break;
		 }
	 }
	 
 }

 void main() {
	 SetConsoleCP(1251);
	 SetConsoleOutputCP(1251);
	 system("color 3");
	 MainMenu();
 }

