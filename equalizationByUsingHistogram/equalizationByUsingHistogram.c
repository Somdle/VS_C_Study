// 패턴인식 평활화

#include <stdio.h>
#include <math.h>  // round함수 사용을 위함

#define ORIGIN_IMAGE_Y 11    // 이미지의 Y크기
#define ORIGIN_IMAGE_X 11    // 이미지의 X크기
#define ORIGIN_IMAGE_RANGE 8 // 이미지의 범위

// 히스토그램을 설정하는 함수
void setHistogram(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X], long histogram[ORIGIN_IMAGE_RANGE]);

// 히스토그램을 보이는 함수
void showHistogram(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X]);
void showHistogramDual(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X], long outputImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X]);

// 매칭 함수
void setMatchingFunction(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X], long histogram[ORIGIN_IMAGE_RANGE], long outputImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X]);
void showMatchingFunction(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X], long histogram[ORIGIN_IMAGE_RANGE]);
void setH_hat(double h_hat[ORIGIN_IMAGE_RANGE], long histogram[ORIGIN_IMAGE_RANGE]);   // h-hat(i)      의 값을 구하기
void setC_in(double c_in[ORIGIN_IMAGE_RANGE], double h_hat[ORIGIN_IMAGE_RANGE]);     // c(in)       의 값을 구하기
void setC_in_L(double c_in_L[ORIGIN_IMAGE_RANGE], double c_in[ORIGIN_IMAGE_RANGE]); // c(in)*(L-1) 의 값을 구하기
void setL_out(double L_out[ORIGIN_IMAGE_RANGE], double c_in_L[ORIGIN_IMAGE_RANGE]);   // L(out)      의 값을 구하기

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

	// 출력이미지 데이터
	long outputImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X] = { 0, };

	// 히스토그램 데이터
	long histogram[ORIGIN_IMAGE_RANGE] = { 0 };

	// 히스토그램 설정
	setHistogram(originImage, histogram);

	// 히스토그램 정보 보이기
	showHistogram(originImage);

	// 매칭 함수 설정(출력 이미지 데이터 입력)
	setMatchingFunction(originImage, histogram, outputImage);

	// 매칭 함수 내부 과정 보이기
	showMatchingFunction(originImage, histogram);

	// 출력 이미지 히스토그램 보이기
	showHistogram(outputImage);

	// 히스토그램 두개 비교
	showHistogramDual(originImage, outputImage);

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
	long histogramRange    = 0; // 히스토그램 유효 범위

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
	printf("\n");
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

void showHistogramDual(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X], long outputImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X]) {
	long orgImgHistogram[ORIGIN_IMAGE_RANGE] = { 0 }; // 입력 이미지 히스토그램
	long outImgHistogram[ORIGIN_IMAGE_RANGE] = { 0 }; // 출력 이미지 히스토그램
	long MaxhistogramValue = 0; // 히스토그램에서 가장 큰값

	long orgImgHistogramRange = 0; // 입력 이미지 히스토그램 범위
	long outImgHistogramRange = 0; // 출력 이미지 히스토그램 범위

	long temp_minHistogramPos = 0; // 히스토그램의 유효한 가장 작은 위치
	long temp_maxHistogramPos = 0; // 히스토그램의 유효한 가장 큰   위치

	// 히스토그램 값 얻기
	setHistogram(originImage, orgImgHistogram);
	setHistogram(outputImage, outImgHistogram);

	// 입력 히스토그램의 범위 구하기
	temp_minHistogramPos = 0;
	temp_maxHistogramPos = 0;
	for (int i = 0; i < ORIGIN_IMAGE_RANGE; i++) {
		if (orgImgHistogram[i] != 0 && temp_minHistogramPos == 0) {
			temp_minHistogramPos = i;
		}
		if (orgImgHistogram[i] != 0) {
			temp_maxHistogramPos = i;
		}
	}
	orgImgHistogramRange = temp_maxHistogramPos - temp_minHistogramPos + 1;

	// 출력 히스토그램의 범위 구하기
	temp_minHistogramPos = 0;
	temp_maxHistogramPos = 0;
	for (int i = 0; i < ORIGIN_IMAGE_RANGE; i++) {
		if (outImgHistogram[i] != 0 && temp_minHistogramPos == 0) {
			temp_minHistogramPos = i;
		}
		if (outImgHistogram[i] != 0) {
			temp_maxHistogramPos = i;
		}
	}
	outImgHistogramRange = temp_maxHistogramPos - temp_minHistogramPos + 1;

	// 원본 이미지에서 최고값 확인
	for (int i = 0; i < ORIGIN_IMAGE_RANGE; i++) {
		if (orgImgHistogram[i] > MaxhistogramValue) {
			MaxhistogramValue = orgImgHistogram[i];
		}
	}
	// 출력 이미지에서 최고값 확인
	for (int i = 0; i < ORIGIN_IMAGE_RANGE; i++) {
		if (outImgHistogram[i] > MaxhistogramValue) {
			MaxhistogramValue = outImgHistogram[i];
		}
	}

	// 히스토그램 2개 출력
	printf("\n");
	printf("show histogram graph dual: \n");
	for (int i = MaxhistogramValue; i >= 1; i--) {
		printf("%2d", i);
		for (int j = 0; j < ORIGIN_IMAGE_RANGE; j++) {
			if (orgImgHistogram[j] == i) {
				printf("*");
			}
			else if (orgImgHistogram[j] >= i) {
				printf("|");
			}
			else {
				printf(" ");
			}
		}

		printf("  ");
		for (int j = 0; j < ORIGIN_IMAGE_RANGE; j++) {
			if (outImgHistogram[j] == i) {
				printf("*");
			}
			else if (outImgHistogram[j] >= i) {
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
			printf("  ");
			for (int j = 0; j < ORIGIN_IMAGE_RANGE; j++) {
				printf("%d", j);
			}
			printf("\n");
		}
	}
	printf("Range: %2d, Range: %2d \n", orgImgHistogramRange, outImgHistogramRange);
}

void setMatchingFunction(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X], long histogram[ORIGIN_IMAGE_RANGE], long outputImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X]) {
	double h_hat[ORIGIN_IMAGE_RANGE]  = { 0 };
	double c_in[ORIGIN_IMAGE_RANGE]   = { 0 };
	double c_in_L[ORIGIN_IMAGE_RANGE] = { 0 };
	double L_out[ORIGIN_IMAGE_RANGE]  = { 0 };

	setH_hat(h_hat, histogram);
	setC_in(c_in, h_hat);
	setC_in_L(c_in_L, c_in);
	setL_out(L_out, c_in_L);

	for (int i = 0; i < ORIGIN_IMAGE_Y; i++) {
		for (int j = 0; j < ORIGIN_IMAGE_X; j++) {
			for (int k = 0; k < ORIGIN_IMAGE_RANGE; k++) {
				if (originImage[i][j] == k) {
					outputImage[i][j] = L_out[k];
				}
			}
		}
	}
}

void showMatchingFunction(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X], long histogram[ORIGIN_IMAGE_RANGE]) {
	double h_hat[ORIGIN_IMAGE_RANGE]  = { 0 };
	double c_in[ORIGIN_IMAGE_RANGE]   = { 0 };
	double c_in_L[ORIGIN_IMAGE_RANGE] = { 0 };
	double L_out[ORIGIN_IMAGE_RANGE]  = { 0 };

	setH_hat(h_hat, histogram);
	setC_in(c_in, h_hat);
	setC_in_L(c_in_L, c_in);
	setL_out(L_out, c_in_L);

	printf("\n");
	printf("matching function table \n");
	printf("in | h_hat | c_in | c_in_L | L_out \n");
	for (int i = 0; i < ORIGIN_IMAGE_RANGE; i++) {
		printf("%2d | %2.2lf | %2.2lf | %2.2lf | %2.2lf \n", i, h_hat[i], c_in[i], c_in_L[i], L_out[i]);
	}
}

void setH_hat(double h_hat[ORIGIN_IMAGE_RANGE], long histogram[ORIGIN_IMAGE_RANGE]) {
	for (int i = 0; i < ORIGIN_IMAGE_RANGE; i++) {
		h_hat[i] = (double)histogram[i] / (double)(ORIGIN_IMAGE_Y * ORIGIN_IMAGE_X);
	}
}
void setC_in(double c_in[ORIGIN_IMAGE_RANGE], double h_hat[ORIGIN_IMAGE_RANGE]) {
	c_in[0] = h_hat[0];
	for (int i = 1; i < ORIGIN_IMAGE_RANGE; i++) {
		c_in[i] = c_in[i - 1] + h_hat[i];
	}
}
void setC_in_L(double c_in_L[ORIGIN_IMAGE_RANGE], double c_in[ORIGIN_IMAGE_RANGE]) {
	for (int i = 0; i < ORIGIN_IMAGE_RANGE; i++) {
		c_in_L[i] = c_in[i] * (ORIGIN_IMAGE_RANGE - 1);
	}
}
void setL_out(double L_out[ORIGIN_IMAGE_RANGE], double c_in_L[ORIGIN_IMAGE_RANGE]) {
	for (int i = 0; i < ORIGIN_IMAGE_RANGE; i++) {
		L_out[i] = round(c_in_L[i]);
	}
}