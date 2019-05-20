#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

#define TRUE	1
#define FALSE	0


typedef struct {
	char	M, N;		// �����ѹ�
	int		width;
	int		height;
	unsigned char **pixels;
} PBMImage;


int fnReadPBM(char* fileNm, PBMImage* img);
void fnClosePBM(PBMImage* img);


int main(int argc, char** argv)
{
	PBMImage	img;

	if (argc != 2) {
		fprintf(stderr, "���� : %s <filename>\n", argv[0]);
		return -1;
	}


	if (fnReadPBM(argv[1], &img) != TRUE) {
		return -1;
	}


	// <-- ��� Ȯ���� ���ؼ� �������� �ֿܼ� �����
	for (int i = 0; i < img.height; i++) {
		for (int j = 0; j < img.width; j++) {
			if (img.pixels[i][j] == 1) {
				printf("��");
			}
			else {
				printf("��");
			}
		}

		printf("\n");
	}
	// -->

	fnClosePBM(&img);

	return 0;
}

int fnReadPBM(char* fileNm, PBMImage* img)
{
	FILE* fp;

	if (fileNm == NULL) {
		fprintf(stderr, "fnReadPBM ȣ�� ����\n");
		return FALSE;
	}

	fp = fopen(fileNm, "r");
	if (fp == NULL) {
		fprintf(stderr, "������ �� �� �����ϴ� : %s\n", fileNm);
		return FALSE;
	}

	fscanf(fp, "%c %c", &img->M, &img->N);	// �����ѹ� �б�

	if (img->M != 'P' || img->N != '1') {
		fprintf(stderr, "PBM �̹��� ������ �ƴմϴ� : %c%c\n", img->M, img->N);
		return FALSE;
	}

	fscanf(fp, "%d %d", &img->width, &img->height);	// ����, ���� �б�


	// <-- �޸� �Ҵ�
	img->pixels = (unsigned char**)calloc(img->height, sizeof(unsigned char*));

	for (int i = 0; i < img->height; i++) {
		img->pixels[i] = (unsigned char*)calloc(img->width, sizeof(unsigned char));
	}
	// -->


	// <-- pbm ���Ϸκ��� �ȼ����� �о �Ҵ��� �޸𸮿� load
	int tmp;

	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			fscanf(fp, "%d", &tmp);

			img->pixels[i][j] = (unsigned char)tmp;
		}
	}
	// -->


	fclose(fp);	// �� �̻� ������� �ʴ� ������ �ݾ� ��

	return TRUE;
}

void fnClosePBM(PBMImage* img)
{
	for (int i = 0; i < img->height; i++) {
		free(img->pixels[i]);
	}

	free(img->pixels);
}