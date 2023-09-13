// 패턴인식 평활화

#include <stdio.h>

#define ORIGIN_IMAGE_Y 11    // 이미지의 Y크기
#define ORIGIN_IMAGE_X 11    // 이미지의 X크기
#define ORIGIN_IMAGE_RANGE 8 // 이미지의 범위

// 히스토그램을 설정하는 함수
void setHistogram(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X], long histogram[ORIGIN_IMAGE_RANGE]);

// 히스토그램을 보이는 함수
void showHistogram(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X]);

// 매칭 함수
void matchingFunction(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X]);
void setH_hat(double h_hat[ORIGIN_IMAGE_RANGE]);   // h헷(i)      의 값을 구하기
void setC_in(double c_in[ORIGIN_IMAGE_RANGE]);     // c(in)       의 값을 구하기
void setC_in_L(double c_in_L[ORIGIN_IMAGE_RANGE]); // c(in)*(L-1) 의 값을 구하기
void setL_out(double L_out[ORIGIN_IMAGE_RANGE]);   // L(out)      의 값을 구하기

// 메인함수
int main() {
	// 원본 이미지 데이터
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
		/*
			2: 19
			3: 29
			4: 30
			5: 24
			6: 19
		*/
	};

	// 히스토그램 데이터
	long histogram[ORIGIN_IMAGE_RANGE] = { 0 };

	setHistogram(originImage, histogram);

	showHistogram(originImage);

	return 0;
}

void setHistogram(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X], long histogram[ORIGIN_IMAGE_RANGE]) {
	// 히스토그램 값 채우기
	for (int i = 0; i < ORIGIN_IMAGE_Y; i++) {
		for (int j = 0; j < ORIGIN_IMAGE_X; j++) {
			histogram[originImage[i][j]] += 1;
		}
	}
}

void showHistogram(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X]) {
	long histogram[ORIGIN_IMAGE_RANGE] = { 0 };
	long MaxhistogramValue = 0; // 히스토그램에서 가장 큰값
	long histogramRange = 0; // 히스토그램 유효 범위

	long temp_minHistogramPos = 0; // 히스토그램의 유효한 가장 작은 위치
	long temp_maxHistogramPos = 0; // 히스토그램의 유효한 가장 큰   위치

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

	// 히스토그램의 범위 구하기
	for (int i = 0; i < ORIGIN_IMAGE_RANGE; i++) {
		if (histogram[i] != 0 && temp_minHistogramPos == 0) {
			temp_minHistogramPos = i;
		}
		if (histogram[i] != 0) {
			temp_maxHistogramPos = i;
		}
	}
	histogramRange = temp_maxHistogramPos - temp_minHistogramPos + 1;

	// 히스토그램 출력하기
	printf("show histogram graph: \n");
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
			printf("\n");
		}
	}
	printf("histogram Range: %d \n", histogramRange);
}

void matchingFunction(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X]) {
	double h_hat[ORIGIN_IMAGE_RANGE]  = { 0 };
	double c_in[ORIGIN_IMAGE_RANGE]   = { 0 };
	double c_in_L[ORIGIN_IMAGE_RANGE] = { 0 };
	double L_out[ORIGIN_IMAGE_RANGE]  = { 0 };

	setH_hat(h_hat);
	setC_in(c_in);
	setC_in_L(c_in_L);
	setL_out(L_out);

}

void setH_hat(double h_hat[ORIGIN_IMAGE_RANGE]) {

}
void setC_in(double c_in[ORIGIN_IMAGE_RANGE]) {

}
void setC_in_L(double c_in_L[ORIGIN_IMAGE_RANGE]) {

}
void setL_out(double L_out[ORIGIN_IMAGE_RANGE]) {

}