// lb12.cpp: ���������� ����� ����� ��� ����������� ����������.
//

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
	int id = { NULL };
} Student;

void MainMenu();
void ReadDB(Student);
void ShowAllRecords(Student);
void AddRecords(Student);
void DelRecords(Student);
void PostMenuHandler();

void PostMenuHandler() {
	printf("��� �������� � ������� ���� ������� m\n");
	printf("��� ������ ������� q\n");
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
		printf("���� �� ������....\n");
	} else {
		while (fscanf(f, "%d %s %s %s %d %d %d %d %d\n", &student[i].id, student[i].LastName, student[i].FirstName, student[i].Group, &student[i].score[0], &student[i].score[1], &student[i].score[2], &student[i].score[3], &student[i].score[4]) != EOF) {
			i++;
		}
		fclose(f);
	}
}

 void ShowAllRecords(Student student[]) {
	 system("cls");
	 int i = 1;
	 printf("+---+-----------------+----------+--------+---+---+---+---+---+\n");
	 printf("|ID | �������         | �������� | ������ |                   |\n");
	 while (student[i].id){
		 printf("+---+-----------------+----------+--------+---+---+---+---+---+\n");
		 printf("|%-2d | %-15s | %-8s | %-6s | %d | %d | %d | %d | %d |\n", student[i].id, student[i].LastName, student[i].FirstName, student[i].Group, student[i].score[0], student[i].score[1], student[i].score[2], student[i].score[3], student[i].score[4]);
		 i++;
	 }
	 printf("+---+-----------------+----------+--------+---+---+---+---+---+\n");
	 
 }

 void DelRecords(Student student[]) {
	 system("cls");
	 printf("�������� ������\n");
	 printf("-----------------------\n");
	 FILE *f;
	 int i = 1, id, rm_row, row;
	 ShowAllRecords(student);
	 printf("������� ID ��������� ������\n");
	 scanf("%d", &id);
	 i = 1;
	 while (student[i].id) {
		 if (id == student[i].id) {
			 rm_row = i;
		 }
		 i++;
	 }
	 row = i;
	 // 10 ��������!!!!
	 for ( i = rm_row; i < row; i++){
		 student[i].id = student[i + 1].id;
		 for (int j = 0; j < 50;j++) {
			 student[i].LastName[j] = student[i + 1].LastName[j];
			 student[i].FirstName[j] = student[i + 1].FirstName[j];
			 student[i].Group[j] = student[i + 1].Group[j];
		 }
		
		 student[i].score[0] = student[i + 1].score[0];
		 student[i].score[1] = student[i + 1].score[1];
		 student[i].score[2] = student[i + 1].score[2];
		 student[i].score[3] = student[i + 1].score[3];
		 student[i].score[4] = student[i + 1].score[4];
	 }
	 ShowAllRecords(student);
	 f = fopen("db.txt", "w");
	 i = 1;
	 while (student[i].id) {
		 fprintf(f, "%d %s %s %s %d %d %d %d %d\n", student[i].id, student[i].LastName, student[i].FirstName, student[i].Group, student[i].score[0], student[i].score[1], student[i].score[2], student[i].score[3], student[i].score[4]);
		 i++;
	 }
	 fclose(f);
 }

 void AddRecords(Student student[]) {
	 system("cls");
	 printf("���������� ����� ������\n");
	 printf("-----------------------\n");
	 FILE *f;
	 int i = 1;
	 while (student[i].id) {
		 i++;
	 }
	 student[i].id = student[i-1].id + 1;
	 printf("�������:  ");
	 scanf("%s50", student[i].LastName);
	 printf("\n��������:  ");
	 scanf("%s50", &student[i].FirstName);
	 printf("\n������:  ");
	 scanf("%s10", &student[i].Group);
	 printf("\n������ ������:  ");
	 scanf("%d", &student[i].score[0]);
	 printf("\n������ ������:  ");
	 scanf("%d", &student[i].score[1]);
	 printf("\n������ ������:  ");
	 scanf("%d", &student[i].score[2]);
	 printf("\n��������� ������:  ");
	 scanf("%d", &student[i].score[3]);
	 printf("\n����� ������:  ");
	 scanf("%d", &student[i].score[4]);

	 i = 1;
	 f = fopen("db.txt", "w");
	 while (student[i].id) {
		 fprintf(f, "%d %s %s %s %d %d %d %d %d\n", student[i].id, student[i].LastName, student[i].FirstName, student[i].Group, student[i].score[0], student[i].score[1], student[i].score[2], student[i].score[3], student[i].score[4]);
		 i++;
	 }
	 fclose(f);
 }

 void MainMenu() {
	 system("cls");
	 Student student[10];
	 ReadDb(student);
	 printf("�������� ��������\nl - ���������� ��� ������\na - �������� ������\nd - ������� ������");
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
	 //setlocale(LC_ALL, "");
	 //setlocale(LC_ALL, "rus");
	 system("color 3");
	 /*
	 struct Student Student;
	 Student.score[0][0] = 1;
	 printf("%d", Student.score[0][0]);
	 system("pause");
	 //return 0;
	 */
	 //system("pause");
	 MainMenu();
	 //system("pause");
 }

