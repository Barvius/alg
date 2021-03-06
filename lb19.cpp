﻿#include "stdafx.h"
#include "windows.h"
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define up 72
#define down 80
#define enter 13
#define esc 27

HDC hDC;
HWND hWnd;
RECT Rect;
HPEN hPen, hOldPen;
HBRUSH hBrush, hOldBrush;
HFONT hFont, hOldFont;
LOGFONT Lf = { 0 };

typedef struct{
	int x[4];
	COLORREF col;
	COLORREF BorderCol;
	char *text;
}Knopka;

typedef struct{
	Knopka *P;
	int n, m;
}Menu;

void clearscreen(){
	hPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hBrush = CreateSolidBrush(RGB(0, 0, 255));
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, Rect.left, Rect.top, Rect.right, Rect.bottom);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
}

void knopka(Knopka *P){
	hPen = CreatePen(PS_SOLID, 4, RGB(255, 255, 255));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hBrush = CreateSolidBrush(RGB(240, 240, 240));
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hFont = CreateFontIndirect(&Lf);
	hOldFont = (HFONT)SelectObject(hDC, hFont);
	Rectangle(hDC, P->x[0] - 4, P->x[1] - 4, P->x[0] + P->x[2] + 4,
		P->x[1] + P->x[3] + 4);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

	hPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, P->x[0], P->x[1], P->x[0] + P->x[2] + 4,
		P->x[1] + P->x[3] + 4);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

	hPen = CreatePen(PS_SOLID, 4, P->col);//заливка фигуры
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hBrush = CreateSolidBrush(P->col);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, P->x[0], P->x[1], P->x[0] + P->x[2],
		P->x[1] + P->x[3]);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

	hPen = CreatePen(PS_DASH, 1, P->BorderCol);//бордер
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	SelectObject(hDC, hPen);
	SelectObject(hDC, GetStockObject(NULL_BRUSH));
	Rectangle(hDC, P->x[0], P->x[1], P->x[0] + P->x[2],
		P->x[1] + P->x[3]);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);

	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, P->col);
	TextOut(hDC, P->x[0] + 2, P->x[1] + 2, (LPCSTR)P->text,
		strlen(P->text));
	SelectObject(hDC, hOldFont);
	DeleteObject(hFont);
}

Menu menu_init(char* punkt[], int l, int top, int width, int height, int n){
	int i;
	Menu M;  M.n = n;  M.m = 0;
	M.P = new Knopka[n];
	for (i = 0; i<n; i++)
	{
		M.P[i].x[0] = l;
		if (i == 0)M.P[i].x[1] = top;
		else M.P[i].x[1] = M.P[i - 1].x[1] + M.P[i - 1].x[3] + 20;
		M.P[i].x[2] = width;
		M.P[i].x[3] = height;
		M.P[i].text = new char[strlen(punkt[i]) + 1];
		strcpy(M.P[i].text, punkt[i]);
	}
	return M;
}

void menu_del(Menu *M){
	int i;
	for (i = 0; i<M->n; i++)
		delete[]M->P[i].text;
	delete[]M->P;
}

int menu_vert(Menu *M){
	int i;
	char ch;
	
	do{
		for (i = 0; i<M->n; i++){
			M->P[i].col = RGB(128, 128, 128);
			if (M->m == i) M->P[i].BorderCol = RGB(255,0,0); //активная
			else M->P[i].BorderCol = RGB(128, 128, 128);
			knopka(&(M->P[i]));
		}
		ch = _getch();
		switch (ch){
		case up: if (M->m == 0) M->m = M->n - 1;
				 else (M->m)--;
				 break;
		case down: if (M->m == M->n - 1) M->m = 0;
				   else (M->m)++;
		}
	} while (ch != enter && ch != esc);
	if (ch == esc) M->m = M->n - 1;
	return M->m;
}

void panel(int panel_x,int panel_y, COLORREF color, char *text) {
	hPen = CreatePen(PS_SOLID, 4, RGB(255, 255, 255));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, (Rect.right / 2) - (panel_x / 2) - 5, (Rect.bottom / 2) - (panel_y / 2) - 5, (Rect.right / 2) + (panel_x / 2) + 5, (Rect.bottom / 2) + (panel_y / 2) + 5);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

	hPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, (Rect.right / 2) - (panel_x / 2), (Rect.bottom / 2) - (panel_y / 2), (Rect.right / 2) + (panel_x / 2) + 5, (Rect.bottom / 2) + (panel_y / 2) + 5);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

	hPen = CreatePen(PS_SOLID, 4, color);
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hBrush = CreateSolidBrush(color);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, (Rect.right / 2) - (panel_x / 2), (Rect.bottom / 2) - (panel_y / 2), (Rect.right / 2) + (panel_x / 2), (Rect.bottom / 2) + (panel_y / 2));
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

	if (*text) {
		hFont = CreateFontIndirect(&Lf);
		hOldFont = (HFONT)SelectObject(hDC, hFont);
		SetTextColor(hDC, RGB(255, 0, 0));
		SetBkColor(hDC, color);
		RECT pos;
		pos.left = (Rect.right / 2) - (panel_x / 2);
		pos.right = (Rect.right / 2) + (panel_x / 2);
		pos.top = (Rect.bottom / 2) - (panel_y / 2);
		pos.bottom = (Rect.bottom / 2) + (panel_y / 2);
		DrawText(hDC, (LPCSTR)text, strlen(text), &pos, DT_CENTER);
		SelectObject(hDC, hOldFont);
		DeleteObject(hFont);
	}
}

int main(){
	int size_x, size_y, panel_x, panel_y;
	size_x = 100;
	size_y = 100;
	panel_x = 400;
	panel_y = 500;
	hWnd = GetConsoleWindow();
	if (!hWnd){
		printf("Can't get hWnd of console!\n");
		_getch();
		return -1;
	}
	MoveWindow(hWnd, 0, 0, 800, 600, TRUE);
	hDC = GetDC(hWnd);
	if (!hDC){
		printf("Can't get device context!\n");
		_getch();
		return -2;
	}
	GetClientRect(hWnd, &Rect);
	char *S[] = { "Об авторе ","Увеличить ","Уменьшить ","Выход " };
	int m = 0;
	do
	{
		clearscreen();
		panel(panel_x, panel_y, RGB(0,128,128),"");
		Menu M = menu_init(S, (Rect.right / 2) - (size_x / 2), (Rect.bottom / 2) - (size_y * 4 / 2)-10*4, size_x, size_y, 4);// текст,лево,право,размер размер, колво пунктов
		m = menu_vert(&M);
		switch (m)
		{
		case 0:
			panel(200, 200, RGB(0, 255, 128), "Выполнил Студент группы\n ИС-16 Барабанщиков Олег");
			_getch();
			break;
		case 1:
			size_x += 5;
			size_y += 5;
			panel_x += 20;
			panel_y += 20;
			break;
		case 2:
			size_x -= 5;
			size_y -= 5;
			panel_x -= 20;
			panel_y -= 20;
		}
	} while (m != 3);
	ReleaseDC(hWnd, hDC);
	return 0;
}
