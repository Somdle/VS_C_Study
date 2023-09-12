// 패턴인식 평활화

#include <stdio.h>

#define ORIGIN_IMAGE_Y 11    // 이미지의 Y크기
#define ORIGIN_IMAGE_X 11    // 이미지의 X크기
#define ORIGIN_IMAGE_RANGE 8 // 이미지의 범위

// 히스토그램을 보이는 함수
void showHistogram(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X]);

// 메인함수
int main() {
	long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X] = 
	{
		{2, 4, 4, 4, 3, 2, 2, 3, 3, 4, 5},
		{2, 3, 4, 5, 5, 6, 6, 6, 6, 2, 2},
		{2, 3, 4, 5, 5, 6, 6, 6, 3, 2, 3},
		{3, 2, 4, 5, 5, 6, 6, 6, 3, 2, 3},
		{3, 2, 4, 5, 6, 6, 4, 4, 3, 2, 3},
		{3, 2, 3, 4, 4, 4, 4, 4, 3, 2, 3},
		{3, 3, 3, 4, 5, 5, 5, 5, 4, 2, 3},
		{4, 3, 3, 6, 6, 5, 5, 5, 4, 3, 4},
		{4, 2, 2, 6, 6, 5, 5, 5, 4, 3, 6},
		{4, 2, 2, 4, 4, 4, 4, 5, 3, 3, 6},
		{4, 3, 3, 5, 5, 5, 5, 5, 4, 4, 6}
	};

	/*
		2: 19
		3: 29
		4: 30
		5: 24
		6: 19
	*/

	showHistogram(originImage);

	return 0;
}

void showHistogram(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X]) {
	long histogram[ORIGIN_IMAGE_RANGE] = { 0 };
	long MaxhistogramValue = 0;

	// 히스토그램 값 채우기
	for (int i = 0; i < ORIGIN_IMAGE_Y; i++) {
		for (int j = 0; j < ORIGIN_IMAGE_X; j++) {
			histogram[originImage[i][j]] += 1;
		}
	}

	// 히스토그램의 최고값 구하기
	for (int i = 0; i < ORIGIN_IMAGE_RANGE; i++) {
		if (histogram[i] > MaxhistogramValue) {
			MaxhistogramValue = histogram[i];
		}
	}

	// 히스토그램 출력하기
	for (int i = MaxhistogramValue; i >= 1; i--) {     // 높이만큼 반복
		printf("%2d", i);                               // Y축 수치 표현
		for (int j = 0; j < ORIGIN_IMAGE_RANGE; j++) { // 히스토그램 출력
			if (histogram[j] == i) {
				printf("*");
			}
			else if (histogram[j] >= i) {
				printf("|");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");

		if (i == 1) {
			printf("  ");
			for (int j = 0; j < ORIGIN_IMAGE_RANGE; j++) {
				printf("%d", j);
			}
		}
	}
}