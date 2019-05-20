// MyImage.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include"pch.h"
#include <iostream>
#include "CImageProDoc.h"

using namespace std;

int main(int argc, char** argv)
{
	CImageProDoc<BYTE> resultimage;
	CMyImage<BYTE> image1(640, 480); // 생성자 호출
	image1.LoadImage("lady.bmp");
	resultimage.LoadImage("lady.bmp");
	//image1.SetConstValue(0);	 // 0으로 초기화

	//CMyImage<BYTE> image2(image1); // 복사 생성자 호출
	//CMyImage<BYTE> image3;		   // 기본 생성자 호출
	//image3 = image1;		   // 대입 연산자 호출

	int nWidth = image1.GetWidth();   // 영상의 너비
	int nHeight = image1.GetHeight();  // 영상의 높이
	int nChannel = image1.GetChannel(); // 영상의 채널 수

	double incX = 255.0 / nWidth;
	double incY = 255.0 / nHeight;

	resultimage.imageWidth = image1.GetWidth();
	resultimage.imageHeight = image1.GetHeight();
	resultimage.GeometryZoominInterpolation();

	
	//int r, c;
	//for (r = 0; r < nHeight; r++) // 행 단위 이동
	//{
	//	for (c = 0; c < nWidth; c++) // 열 단위 이동
	//	{
	//		image2.GetAt(c, r) = (BYTE)(c*incX); // 가로 그라데이션
	//		image3.GetAt(c, r) = (BYTE)(r*incY); // 세로 그라데이션
	//	}
	//}

	// 결과 영상 저장
	resultimage.SaveImage("BigImage.bmp");
	//image2.SaveImage("GradationX.bmp");
	//image3.SaveImage("GradationY.bmp");

	//return 0;
}

