// lb10.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"

int main(){
	FILE *f;
	f = fopen("text","r");
	if(!f){
		printf("Файл не найден!");
	} else {
	
	}
	_getch();
}

