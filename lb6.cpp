// lb6.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//

#include "stdafx.h"
#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "locale.h"

void main() {
	//int * c = new int[n];
	setlocale(0, "rus");
	const int m_len = 50;
	int  n,i,k,j=0;
	float a[m_len], b[m_len], sum = 0, sr_ar = 0;
	for (i = 0; i < m_len; i++) {
		a[i] = rand() % 20;
		printf("%.0f ", a[i]);
		sum += a[i];
	}
	sr_ar = sum / m_len;
	n = m_len;
	for (i = 0; i < n; i++) {
		if (a[i] < sr_ar) {
			b[j] = a[i];
			j++;
			n--;
			for (k = i; k <= n;k++) {
				a[k] = a[k + 1];
			}
			i--;
		}
	}
	printf_s("\nÑð àð: %.2f \n", sr_ar);
	printf("Ìàññèâ À \n");
	for (i = 0; i < n; i++) {
		printf("%.0f ", a[i]);
	}
	printf("\nÌàññèâ Â \n");
	for (i = 0; i < j; i++) {
		printf("%.0f ", b[i]);
	}
	_getch();
	//шестая лаба
}

