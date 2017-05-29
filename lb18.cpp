#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include "conio.h"
#include "math.h"
#include "dos.h"
#include "string.h"
#include "locale.h"
#define DX 20
#define DY 20

HDC hDC;
HWND hWnd;
RECT Rect;
HPEN hPen, hOldPen;
HBRUSH hBrush, hOldBrush;
HFONT hFont, hOldFont;
LOGFONT Lf = { 0 };

float f_lg(float x, int a){
	if (x) {
		return log(fabs(x));
	} else {
		return 0;
	}
	
}

float f_ax(float x, int a) {
	return(2 * cos(x + 3.14 / 6) + a*(powf(x,2)-3*x+2));
}

void clearscreen(int r, int g, int b){
	hPen = CreatePen(PS_SOLID, 4, RGB(r, g, b));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hBrush = CreateSolidBrush(RGB(r, g, b));
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, Rect.left, Rect.top, Rect.right, Rect.bottom);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
}

void mashtab(float xn, float xk, float *mx, float *my, float *miny, float *maxy, float(*func)(float, int), int a){
	float x, y, dx;
	x = xn; 
	dx = (xk - xn) / 100;
	*maxy = -1000; 
	*miny = 1000;
	while (x <= xk){
		y = func(x,a);
		if (y>*maxy) *maxy = y;
		if (y<*miny) *miny = y;
		x = x + dx;
	}
	*my = (Rect.bottom - 2 * DY) / (*maxy - *miny);
	*mx = (Rect.right - 2 * DX) / (xk - xn);
}

void osi(float minx, float maxx, float miny, float maxy, float mx, float my, int *osx, int *osy){
	if (minx*maxx<0) *osy = fabs(minx)*mx + DX;
	else if (minx >= 0) *osy = DX;
	else *osy = Rect.right - DX;
	if (miny*maxy<0) *osx = Rect.bottom - fabs(miny)*my - DY;
	else if (miny >= 0) *osx = Rect.bottom - DY;
	else *osx = DY;
	hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	MoveToEx(hDC, DX, *osx, NULL);
	LineTo(hDC, Rect.right - DX, *osx);
	MoveToEx(hDC, *osy, DY, NULL);
	LineTo(hDC, *osy, Rect.bottom - DY);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

void setka(int osx, int osy, float minx, float maxx, float miny, float maxy, float mx, float my){
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	Lf.lfHeight = 12;
	Lf.lfWeight = 900;
	Lf.lfWidth = 8;
	CHAR S[20];
	strcpy((char*)Lf.lfFaceName, "Times New Roman");
	hFont = CreateFontIndirect(&Lf);
	hOldFont = (HFONT)SelectObject(hDC, hFont);
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkColor(hDC, RGB(255, 255, 255));
	TextOut(hDC, osy - 20, Rect.top + DY - 8, (LPCSTR)"Y", 1);
	TextOut(hDC, Rect.right - DX + 2, osx - 20, (LPCSTR)"X", 1);
	//построение сетки
	float dx, x, y;
	int xt, yt;
	RECT d;
	dx = (maxx - minx) / 20;
	for (x = minx; x <= maxx; x += dx){
		xt = DX + mx*(x - minx);
		MoveToEx(hDC, xt, Rect.top + DY, NULL);
		LineTo(hDC, xt, Rect.bottom - DY);
		sprintf(S, "%.1f", x);
		TextOut(hDC, xt, osx + 8, (LPCSTR)S, strlen(S));
	}
	float dy = (maxy - miny) / 20;
	for (y = miny; y<maxy + dy; y += dy){
		yt = Rect.bottom - my*(y - miny) - DY;
		MoveToEx(hDC, Rect.left + DX, yt, NULL);
		LineTo(hDC, Rect.right + DX, yt);
		sprintf(S, "%.1f", y);
		TextOut(hDC, osy + 5, yt, (LPCSTR)S, strlen(S));
	}
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(hDC, hOldFont);
	DeleteObject(hFont);
}

void grafik(float minx, float maxx, float miny, float mx, float my, float(*func)(float, int), int a){
	float x, y, dx;
	int xt, yt;
	dx = (maxx - minx) / 200;
	//установка цвета и стиля линий для построения функции (красный)
	hPen = CreatePen(PS_SOLID, 4, RGB(0, 128, 128));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	//расчет координат начальной точки функции	
	x = minx;
	y = func(x, a);
	xt = Rect.left + (x - minx)*mx + DX;
	yt = Rect.bottom - (y - miny)*my - DY;
	MoveToEx(hDC, xt, yt, NULL);
	//построение графика
	do {
		x = x + dx;
		y = func(x, a);
		 
		xt = Rect.left + (x - minx)*mx + DX;
		yt = Rect.bottom - (y - miny)*my - DY;
		LineTo(hDC, xt, yt);
	} while (x<maxx - dx);
	//printf("%d %d\n", xt,yt);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

int WindowInit() {
	hWnd = GetConsoleWindow();
	if (!hWnd) {
		printf("Can't get hWnd of console!\n");
		_getch();
		return -1;
	}
	MoveWindow(hWnd, 0, 0, 800, 600, TRUE);
	SetWindowText(hWnd, (LPCSTR)"График функции");

	hDC = GetDC(hWnd);
	if (!hDC) {
		printf("Can't get device context!\n");
		_getch();
		return -2;
	}
	GetClientRect(hWnd, &Rect);
}

int main(int argc, _TCHAR* argv[]){
	float(*charts_function)(float, int);
	float b, maxy, miny, mx, my;
	int osx, osy;
	int xn, xk, a = 0;
	setlocale(LC_ALL, "Russian");

	WindowInit();
	clearscreen(255, 255, 255);

	do {
		
		//_getch();
		//ReleaseDC(hWnd, hDC);
		system("cls");
		clearscreen(0, 0, 0);
		printf("x => ln|x|\n");
		printf("a => 2cos(x+pi/6)+a(x^2-3x+2)\n");

		switch (_getch()) {
			system("cls");
			//clearscreen(0, 0, 0);
		case 'x':
			printf("ln|x|\n\n");
			printf("DX\n");
			charts_function = f_lg;
			scanf_s("%d %d", &xn, &xk);
			break;
		case 'a':
			printf("2cos(x+pi/6)+a(x^2-3x+2)\n");
			printf("DX\n");
			charts_function = f_ax;
			scanf_s("%d %d", &xn, &xk);
			printf("A\n");
			scanf_s("%d", &a);
			break;
		default:
			exit(0);
			break;
		}
		char ch;
		int scale = 1;
		do
		{	
			clearscreen(255, 255, 255);
			mashtab(xn, xk, &mx, &my, &miny, &maxy, charts_function, a);
			osi(xn, xk, miny, maxy, mx, my, &osx, &osy);
			setka(osx, osy, xn, xk, miny, maxy, mx, my);
			grafik(xn, xk, miny, mx, my, charts_function, a);
			ch = _getch();
			switch (ch) {
			case 61: //+
				if ((xk - xn) > 2.0) {
					xn += scale;
					xk -= scale;
				}
				break;
			case 45: //-
				xn -= scale;
				xk += scale;
				break;
			case 75: // l
				xn -= scale;
				xk -= scale;
				break;
			case 77: //r
				xn += scale;
				xk += scale;
				break;

			}
			
		} while (ch != 27);

		ReleaseDC(hWnd, hDC);
	}while(true);
	
	_getch();
	return 0;
}
