#pragma once
#include "CMyImage.h"

template <typename T>
class CImageProDoc : public CMyImage <typename T>
{
public:
	unsigned char**inputImg;//입력 영상의 기억 장소에 대한 포인터 변수
	unsigned char**inputImg2;//입력 영상의 기억 장소에 대한 포인터 변수
	unsigned char**resultImg;//출력 영상의 기억 장소에 대한 포인터 변수
	int depth; //1=흑백영상, 3=컬러영상
	//결과 영상의 크기가 변화되는 기하학적 처리를 위해 새로이 추가되는 코드
	int gm_nWidth; //크기가 변한 결과 영상의 가로 크기
	int gm_nHeight; //크기가 변한 결과 영상의 세로 크기 
	unsigned char**gResultImg; //크기가 변한 결과 영상에 대한 포인터 변수 

	//기본생성자
	CImageProDoc(void)
		: CMyImage(), inputImg(NULL), inputImg2(NULL), resultImg(NULL), gResultImg(NULL)
	{ }

	//가로,세로,채널을 입력 받는 생성자
	CImageProDoc(int nWidth, int nHeight, int nChannels = 1)
		: CMyImage(nWidth, nHeight, nChannels), inputImg(NULL), inputImg2(NULL), resultImg(NULL), gResultImg(NULL)
	{ }

	//확대 함수 
	void GeometryZoominInterpolation()
	{
		float src_x, src_y;	//원시 화소 위치
		float alpha, beta;
		int scale_x, scale_y;	//x방향과 y방향으로의 확대 비율
		int E, F;	//x방향으로 보간된 결과값
		int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;	//보간에 사용될 4개 픽셀의 좌표

		scale_x = 2;
		scale_y = 2;

		//결과 영상의 크기 설정
		gm_nWidth = CMyImage<T>::m_nWidth * scale_x;
		gm_nHeight = CMyImage<T>::m_nHeight * scale_y;

		//결과 영상을 저장할 기억 장소 공간 할당
		gResultImg = new unsigned char*[gm_nHeight * sizeof(unsigned char*)];
		for (int i = 0; i < gm_nHeight * sizeof(unsigned char*); i++) {
			gResultImg[i] = new unsigned char[gm_nWidth*depth];
		}
		for (int y = 0; y < gm_nHeight; y++)
		{
			for (int x = 0; x < gm_nWidth; x++) {
				//원시 영상에서의 픽셀 좌표 계산
				src_x = x / (float)scale_x;
				src_y = y / (float)scale_y;
				alpha = src_x - x / scale_x;
				beta = src_y - y / scale_y;

				Ax = x / scale_x;
				Ay = y / scale_y;
				Bx = Ax + 1;
				By = Ay;
				Cx = Ax;
				Cy = Ay + 1;
				Dx = Ax + 1;
				Dy = Ay + 1;

				//픽셀 위치가 영상의 경계를 벗어나는지 검사
				if (Bx > CMyImage<T>::m_nWidth - 1) Bx = CMyImage<T>::m_nWidth - 1;
				if (Dx > CMyImage<T>::m_nWidth - 1) Bx = CMyImage<T>::m_nWidth - 1;
				if (Cy > CMyImage<T>::m_nHeight - 1) Cy = CMyImage<T>::m_nHeight - 1;
				if (Dy > CMyImage<T>::m_nHeight - 1) Dy = CMyImage<T>::m_nHeight - 1;

				//x방항으로 보간
				E = (int)(inputImg[Ay][Ax] * (1 - alpha) + inputImg[By][Bx] * alpha);
				F = (int)(inputImg[Cy][Cx] * (1 - alpha) + inputImg[Dy][Dx] * alpha);

				//y방향으로 보간
				gResultImg[y][x] = (unsigned char)(E*(1 - beta) + F * beta);
			}
		}
	} //!!!여기에 선언이 필요합니다 뜨거나 
	//delete없음
};  //!!!!여기에 ;가 필요합니다 뜸