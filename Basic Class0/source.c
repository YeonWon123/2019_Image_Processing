#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

#define TRUE	1
#define FALSE	0


typedef struct {
	char	M, N;		// 매직넘버
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
		fprintf(stderr, "사용법 : %s <filename>\n", argv[0]);
		return -1;
	}


	if (fnReadPBM(argv[1], &img) != TRUE) {
		return -1;
	}


	// <-- 결과 확인을 위해서 읽은값을 콘솔에 출력함
	for (int i = 0; i < img.height; i++) {
		for (int j = 0; j < img.width; j++) {
			if (img.pixels[i][j] == 1) {
				printf("■");
			}
			else {
				printf("□");
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
		fprintf(stderr, "fnReadPBM 호출 에러\n");
		return FALSE;
	}

	fp = fopen(fileNm, "r");
	if (fp == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다 : %s\n", fileNm);
		return FALSE;
	}

	fscanf(fp, "%c %c", &img->M, &img->N);	// 매직넘버 읽기

	if (img->M != 'P' || img->N != '1') {
		fprintf(stderr, "PBM 이미지 포멧이 아닙니다 : %c%c\n", img->M, img->N);
		return FALSE;
	}

	fscanf(fp, "%d %d", &img->width, &img->height);	// 가로, 세로 읽기


	// <-- 메모리 할당
	img->pixels = (unsigned char**)calloc(img->height, sizeof(unsigned char*));

	for (int i = 0; i < img->height; i++) {
		img->pixels[i] = (unsigned char*)calloc(img->width, sizeof(unsigned char));
	}
	// -->


	// <-- pbm 파일로부터 픽셀값을 읽어서 할당한 메모리에 load
	int tmp;

	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			fscanf(fp, "%d", &tmp);

			img->pixels[i][j] = (unsigned char)tmp;
		}
	}
	// -->


	fclose(fp);	// 더 이상 사용하지 않는 파일을 닫아 줌

	return TRUE;
}

void fnClosePBM(PBMImage* img)
{
	for (int i = 0; i < img->height; i++) {
		free(img->pixels[i]);
	}

	free(img->pixels);
}