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
HPEN hPen, hOldPen, greenPen,redPen;
HBRUSH hBrush, hOldBrush;
HFONT hFont, hOldFont;
LOGFONT Lf = { 0 };



typedef struct CIRCLE {
	float x;
	float y;
	float r;
} circle;

circle vpis(float x1, float y1, float x2, float y2, float x3, float y3) {
	circle crcl;
	float a, b, c, p, S;
	a = sqrt(powf((x2 - x1), 2) + (powf((y2 - y1), 2)));
	b = sqrt(powf((x3 - x2), 2) + (powf((y3 - y2), 2)));
	c = sqrt(powf((x3 - x1), 2) + (powf((y3 - y1), 2)));
	p = fabs((a + b + c)) / 2;
	crcl.x = (a*x1 + b*x2 + c*x3) / (p * 2);
	crcl.y = (a*y1 + b*y2 + c*y3) / (p * 2);
	S = sqrt(p*(p - a)*(p - b)*(p - c));
	crcl.r = S / p;
	return crcl;
}

void clearscreen(int r, int g, int b) {
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

void mashtab(float *mx, float *my, float *miny, float *maxy) {
	*maxy = 10;
	*miny = -10;
	float xn = -10;
	float xk = 10;
	*my = (Rect.bottom - 2 * DY) / (*maxy - *miny);
	*mx = (Rect.right - 2 * DX) / (xk - xn);
}

void osi(float minx, float maxx, float miny, float maxy, float mx, float my, int *osx, int *osy) {
	if (minx*maxx < 0) *osy = fabs(minx)*mx + DX;
	else if (minx >= 0) *osy = DX;
	else *osy = Rect.right - DX;
	if (miny*maxy < 0) *osx = Rect.bottom - fabs(miny)*my - DY;
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

void setka(int osx, int osy, float minx, float maxx, float miny, float maxy, float mx, float my) {
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
	dx = (maxx - minx) / 20;
	for (x = minx; x <= maxx; x += dx) {
		xt = DX + mx*(x - minx);
		MoveToEx(hDC, xt, Rect.top + DY, NULL);
		LineTo(hDC, xt, Rect.bottom - DY);
		sprintf(S, "%.1f", x);
		TextOut(hDC, xt, osx + 8, (LPCSTR)S, strlen(S));
	}
	float dy = (maxy - miny) / 20;
	for (y = miny; y < maxy + dy; y += dy) {
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

void tz(float minx, float maxx, float miny, float mx, float my) {
	float x, y, dx;
	COLORREF col = RGB(255, 0, 0);
	COLORREF blue = RGB(0, 0, 255);
	float N, M[2][200], MM[2][3];
	//float N = 3, M[2][200] = { {-3,2,2},{0,3,-3} }, MM[2][3];
	circle max,c;
	LOGFONT *font;
	max.r = 0;
	scanf("%f", &N);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < N; j++) {
			M[i][j] = -10 + rand() % 20;
			//printf("%f\t", M[i][j]);
		}
		//printf("\n");
	}
	for (int i = 0; i < N - 2; i++) {
		for (int j = i + 1; j < N - 1; j++) {
			for (int k = j + 1; k < N; k++) {
				c = vpis(M[0][i], M[1][i], M[0][j], M[1][j], M[0][k], M[1][k]);
				//printf("x1 = %1.f y1 =  %1.f x2 = %1.f y2 = %1.f x3 = %1.f y3 = %1.f\n", M[0][i], M[1][i], M[0][j], M[1][j], M[0][k], M[1][k]);
				int count = 0;
				for (int l = 0; l < N; l++) {
					if (sqrt(powf(M[0][l] - c.x, 2) + powf(M[1][l] - c.y, 2)) < c.r) {
						count++;
					}
				}
				if (count) {
					//printf("tochek v okr = %d\n", count);
				}
				else {
					//printf("Center: (%f, %f)\t", c.x, c.y);
					//printf("Radius: %f\n", c.r);
					if (max.r < c.r) {
						max.r = c.r;
						max.x = c.x;
						max.y = c.y;
						MM[0][0] = M[0][i];
						MM[1][0] = M[1][i];
						MM[0][1] = M[0][j];
						MM[1][1] = M[1][j];
						MM[0][2] = M[0][k];
						MM[1][2] = M[1][k];
					}

				}
			}
		}
	}
	redPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	greenPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	SelectObject(hDC, redPen);
	float xt = Rect.left + (max.x - minx)*mx + DX;
	float yt = Rect.bottom - (max.y - miny)*my - DY;
	float rt = max.r*mx;
	printf("x1 = %1.f y1 =  %1.f x2 = %1.f y2 = %1.f x3 = %1.f y3 = %1.f\t\n", MM[0][0], MM[1][0], MM[0][1], MM[1][1], MM[0][2], MM[1][2]);
	printf("Center: (%f, %f)\n", max.x, max.y);
	printf("Radius: %f\n", max.r);
	Ellipse(hDC, xt - rt, yt - rt, xt + rt, yt + rt);
	SetPixel(hDC, xt, yt, col);
	SelectObject(hDC, greenPen);
	MoveToEx(hDC, (Rect.left + (MM[0][0] - minx)*mx + DX), (Rect.bottom - (MM[1][0] - miny)*my - DY), NULL);
	LineTo(hDC, (Rect.left + (MM[0][0] - minx)*mx + DX), (Rect.bottom - (MM[1][0] - miny)*my - DY));
	LineTo(hDC, (Rect.left + (MM[0][1] - minx)*mx + DX), (Rect.bottom - (MM[1][1] - miny)*my - DY));
	LineTo(hDC, (Rect.left + (MM[0][2] - minx)*mx + DX), (Rect.bottom - (MM[1][2] - miny)*my - DY));
	LineTo(hDC, (Rect.left + (MM[0][0] - minx)*mx + DX), (Rect.bottom - (MM[1][0] - miny)*my - DY));
	SelectObject(hDC, redPen);
	SetTextColor(hDC, blue);

	Lf.lfItalic = true;
	hFont = CreateFontIndirect(&Lf);
	(HFONT)SelectObject(hDC, hFont);

	for (int j = 0; j < N; j++) {
		xt = Rect.left + (M[0][j] - minx)*mx + DX;
		yt = Rect.bottom - (M[1][j] - miny)*my - DY;
		Ellipse(hDC, xt - 2, yt - 2, xt + 2, yt + 2);
		char *text = new char[100];
		sprintf(text, "(%1.f:%1.f)", M[0][j], M[1][j]);
		int z = strlen(text);
		TextOut(hDC, xt - 40, yt, (LPSTR)text, z);
	}
	DeleteObject(redPen);
	DeleteObject(greenPen);
}

int WindowInit() {
	hWnd = GetConsoleWindow();
	if (!hWnd) {
		printf("Can't get hWnd of console!\n");
		_getch();
		return -1;
	}
	MoveWindow(hWnd, 0, 0, 700, 700, TRUE);
	SetWindowText(hWnd, (LPCSTR)"График функции");
	hDC = GetDC(hWnd);
	if (!hDC) {
		printf("Can't get device context!\n");
		_getch();
		return -2;
	}
	GetClientRect(hWnd, &Rect);
}

int main(int argc, _TCHAR* argv[]) {
	float maxy, miny, mx, my;
	int osx, osy;
	int xn, xk, a = 0;
	setlocale(LC_ALL, "Russian");
	WindowInit();
	clearscreen(255, 255, 255);
	mashtab(&mx, &my, &miny, &maxy);
	osi(-10, 10, miny, maxy, mx, my, &osx, &osy);
	setka(osx, osy, -10, 10, miny, maxy, mx, my);
	tz(-10, 10, miny, mx, my);
	ReleaseDC(hWnd, hDC);
	_getch();
	return 0;
}
