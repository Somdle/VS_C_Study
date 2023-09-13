// �����ν� ��Ȱȭ

#include <stdio.h>

#define ORIGIN_IMAGE_Y 11    // �̹����� Yũ��
#define ORIGIN_IMAGE_X 11    // �̹����� Xũ��
#define ORIGIN_IMAGE_RANGE 8 // �̹����� ����

// ������׷��� �����ϴ� �Լ�
void setHistogram(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X], long histogram[ORIGIN_IMAGE_RANGE]);

// ������׷��� ���̴� �Լ�
void showHistogram(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X]);

// ��Ī �Լ�
void matchingFunction(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X]);
void setH_hat(double h_hat[ORIGIN_IMAGE_RANGE]);   // h��(i)      �� ���� ���ϱ�
void setC_in(double c_in[ORIGIN_IMAGE_RANGE]);     // c(in)       �� ���� ���ϱ�
void setC_in_L(double c_in_L[ORIGIN_IMAGE_RANGE]); // c(in)*(L-1) �� ���� ���ϱ�
void setL_out(double L_out[ORIGIN_IMAGE_RANGE]);   // L(out)      �� ���� ���ϱ�

// �����Լ�
int main() {
	// ���� �̹��� ������
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

	// ������׷� ������
	long histogram[ORIGIN_IMAGE_RANGE] = { 0 };

	setHistogram(originImage, histogram);

	showHistogram(originImage);

	return 0;
}

void setHistogram(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X], long histogram[ORIGIN_IMAGE_RANGE]) {
	// ������׷� �� ä���
	for (int i = 0; i < ORIGIN_IMAGE_Y; i++) {
		for (int j = 0; j < ORIGIN_IMAGE_X; j++) {
			histogram[originImage[i][j]] += 1;
		}
	}
}

void showHistogram(long originImage[ORIGIN_IMAGE_Y][ORIGIN_IMAGE_X]) {
	long histogram[ORIGIN_IMAGE_RANGE] = { 0 };
	long MaxhistogramValue = 0; // ������׷����� ���� ū��
	long histogramRange = 0; // ������׷� ��ȿ ����

	long temp_minHistogramPos = 0; // ������׷��� ��ȿ�� ���� ���� ��ġ
	long temp_maxHistogramPos = 0; // ������׷��� ��ȿ�� ���� ū   ��ġ

	// ������׷� �� ä���
	for (int i = 0; i < ORIGIN_IMAGE_Y; i++) {
		for (int j = 0; j < ORIGIN_IMAGE_X; j++) {
			histogram[originImage[i][j]] += 1;
		}
	}

	// ������׷��� �ְ� ���ϱ�
	for (int i = 0; i < ORIGIN_IMAGE_RANGE; i++) {
		if (histogram[i] > MaxhistogramValue) {
			MaxhistogramValue = histogram[i];
		}
	}

	// ������׷��� ���� ���ϱ�
	for (int i = 0; i < ORIGIN_IMAGE_RANGE; i++) {
		if (histogram[i] != 0 && temp_minHistogramPos == 0) {
			temp_minHistogramPos = i;
		}
		if (histogram[i] != 0) {
			temp_maxHistogramPos = i;
		}
	}
	histogramRange = temp_maxHistogramPos - temp_minHistogramPos + 1;

	// ������׷� ����ϱ�
	printf("show histogram graph: \n");
	for (int i = MaxhistogramValue; i >= 1; i--) {     // ���̸�ŭ �ݺ�
		printf("%2d", i);                               // Y�� ��ġ ǥ��
		for (int j = 0; j < ORIGIN_IMAGE_RANGE; j++) { // ������׷� ���
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