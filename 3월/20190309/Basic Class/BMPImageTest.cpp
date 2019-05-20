#include "IppConvert.h"
#include "IppImage.h"
#include "IppFilter.h"

//    - 카메라로 입력받는 bmp 파일은 RGB 파일이니깐
//    - 따라서 입력받는 bmp 파일은 RGB 파일이라고 가정하고,
//    - RGB 파일 입력 -> GrayScale로 변환 -> 확대축소 알고리즘 적용 이 합리적으로 보임
//    - 만약 assert 오류가 날 경우, 불러오려는 파일 이름이 잘못되었거나, bmp파일이 RGB파일이 아니라고 생각할 수 있다!

int main()
{
	// IppDib.h : BMP 파일 입출력!
	// IppImage.h : 2차원 배열로 되어 있음
	// 실질적인 픽셀 값 수정
	// IppRgbImage와 IppByteImage 모두 IppImage.h 에 있음

	/*
	IppDib dib;				// BMP 파일을 입출력하고 보관하기 위한 IppDib 객체 생성, 아직은 비어 있음
	dib.Load("input.bmp");  // 윗 줄에서 선언한 객체에 "input.bmp" 파일을 불러와서 채움, IppDib 객체(dib)가 채워짐

	IppRgbImage img;		// RGB 이미지 수정을 위한 IppRgbImage 객체 생성, 아직은 비어 있음
	IppDibToImage(dib, img); // 이미지 수정을 위해서는 IppDib 클래스 객체를 IppImage 클래스 객체로 변환해야 함

	IppByteImage img2;		// GrayScale 이미지 수정을 위한 IppByteImage 객체 생성, 아직은 비어 있음
	img2.Convert(img);		// RGB 파일(img)을 GrayScale 파일로 변환(Convert)하여 IppByteImage 객체(img2)에 채움
	*/
	/*
		// 예시 Question: 내가 만약 RGB 파일을 받아서 GrayScale로 바꾸려고 하면, 어떻게 해야 할까? (서현)
		IppDib dib3;
		dib3.Load("lena.bmp");
		IppRgbImage img3;
		IppDibToImage(dib3, img3);
		IppByteImage img3_2;
		img3_2.Convert(img3);
		*/
		// 예시 Question: 내가 만약 RGB 파일을 받아서 GrayScale로 바꾸려고 하면, 어떻게 해야 할까? (윤지)
		IppDib dib2; 
		dib2.Load("dog.bmp"); 
		IppRgbImage myimg;
		IppDibToImage(dib2, myimg);
		IppByteImage myimg2; 
		myimg2.Convert(myimg);


	// 수정할 GrayScale 파일을 저장할 객체 생성
	IppFloatImage img_result1;

	IppFilterGaussian(myimg2, img_result1, 2);
	//--------------------------------------------------------------//
	//																//
	//					IppImage 클래스 객체를 수정					//
	//					즉, 이곳에 BMP 영상을 수정...					//
	//																//
	//--------------------------------------------------------------//
		


	// 수정된 GrayScale파일을 BMP 파일로 변환
	IppDib dib5;
	IppImageToDib(img_result1, dib5);

	// 최종 BMP 파일을 저장
	dib5.Save("output.bmp");

	return 0;
}