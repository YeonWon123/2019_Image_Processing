// MyImage.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include"pch.h"
#include <iostream>
#include "CImageProDoc.h"

using namespace std;

int main(int argc, char** argv)
{
	CImageProDoc<BYTE> image1(640,480);
	image1.SetConstValue(0);// 0으로 초기화  //!!!!!!!!!class CImageProDoc<BYTE>에 SetConstValue 없다고 뜸 밑에 함수들도 다 없다고뜸
	image1.LoadImage("lady.bmp");

	int nWidth = image1.GetWidth();   // 영상의 너비
	int nHeight = image1.GetHeight();  // 영상의 높이
	int nChannel = image1.GetChannel(); // 영상의 채널 수

	//double incX = 255.0 / nWidth;
	//double incY = 255.0 / nHeight;

	image1.GeometryZoominInterpolation();

	// 결과 영상 저장
	image1.SaveImage("BigImage.bmp");
	//image2.SaveImage("GradationX.bmp");
	//image3.SaveImage("GradationY.bmp");

	//return 0;
}

