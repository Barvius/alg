#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

typedef struct CIRCLE {
	double x;
	double y;
	double r;
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

int main(){
	setlocale(0,"rus");
	int N;
	float MM[2][3], M[2][20];
	circle max,c;
	max.r = 0;
	printf("введите количество точек\n");
	scanf("%d",&N);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < N; j++) {
			M[i][j] = -10 + rand() % 20;
			printf("%1.f\t", M[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < N - 2; i++) {
		for (int j = i + 1; j < N - 1; j++) {
			for (int k = j + 1; k < N; k++) {
				c = vpis(M[0][i], M[1][i], M[0][j], M[1][j], M[0][k], M[1][k]);
				printf("x1 = %1.f y1 =  %1.f x2 = %1.f y2 = %1.f x3 = %1.f y3 = %1.f\n", M[0][i], M[1][i], M[0][j], M[1][j], M[0][k], M[1][k]);
				int count = 0;
				for (int l = 0; l < N; l++) {
					if (sqrt(powf(M[0][l] - c.x, 2) + powf(M[1][l] - c.y, 2)) < c.r) {
						count++;
					}
				}
				if (count) {
					printf("tochek v okr = %d\n", count);
				}
				else {
					printf("Center: (%f, %f)\t", c.x, c.y);
					printf("Radius: %f\n", c.r);
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
	printf("Результаты\n");
	printf("x1 = %1.f y1 =  %1.f x2 = %1.f y2 = %1.f x3 = %1.f y3 = %1.f\t\n", MM[0][0], MM[1][0], MM[0][1], MM[1][1], MM[0][2], MM[1][2]);
	printf("Center: (%f, %f)\n", max.x, max.y);
	printf("Radius: %f\n", max.r);
	system("pause");
	return 0;
}