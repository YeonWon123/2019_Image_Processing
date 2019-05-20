#include "IppConvert.h"
#include "IppGeometry.h"

// 고민?
// 1. bmp 파일이 RGB인지 그레이스케일인지 판단할 수 있는지?
//    - 카메라로 입력받는 bmp 파일은 RGB 파일이니깐, GrayScale인지 판단은 무의미
//    - 따라서 입력받는 bmp 파일은 RGB 파일이라고 가정하고,
//    - RGB 파일 입력 -> GrayScale로 변환 -> 확대축소 알고리즘 적용 이 합리적으로 보임
//    - 만약 assert 오류가 날 경우, 그 bmp파일은 RGB파일이 아니라고 생각할 수 있다!

// 2. 확대, 축소의 비율을 변수화할 수 있는지?
//    - *2, /2, /4 셋이 필요하므로, Save를 3개 시도하면 됨
//    - 즉 원본에서 *2를 먼저 하고 그것을 한 객체에 담고 Save 하고
//    - 다음으로 /2를 하고 그것을 다른 객체에 담고 Save 하고
//    - 마지막으로 /4를 하고 그것을 다른 객체에 담고 Save 한다!

int main()
{
	// 영상의 확대 축소 함수 예시 (img2 : 원본, img_result1 : 저장할 곳) 
	// IppResizeCubic(img2, img_result1, img2.GetWidth()/2, img2.GetHeight()/2);
	// IppResizeCubic(img2, img_result2, img2.GetWidth()*2, img2.GetHeight()*2);
	// IppResizeCubic(img2, img_result3, img2.GetWidth()/4, img2.GetHeight()/4);
	

	// Question: 내가 만약 RGB 파일을 받아서 GrayScale로 바꾸려고 하면, 어떻게 해야 할까? (서현)
	IppDib dib8;
	dib8.Load("lena.bmp");
	IppRgbImage img3;
	IppDibToImage(dib8, img3);
	IppByteImage img3_2;
	img3_2.Convert(img3);

	// GrayScale 이미지 파일을 확대(*2)하고 축소(/2, /4) 해서 각각 result1.bmp, result2.bmp, result3.bmp로 저장하기!
	IppByteImage result1, result2, result3;
	IppResizeCubic(img3_2, result1, img3_2.GetWidth() * 2, img3_2.GetHeight() * 2);
	IppResizeCubic(img3_2, result2, img3_2.GetWidth() / 2, img3_2.GetHeight() / 2);
	IppResizeCubic(img3_2, result3, img3_2.GetWidth() / 4, img3_2.GetHeight() / 4);

	// Hint
	/*
	// 수정된 GrayScale파일을 BMP 파일로 변환
		IppDib dib2;
		IppImageToDib(img_result1, dib2);+

	// 최종 BMP 파일을 저장
		dib2.Save("output.bmp");
	*/

	IppDib dib111, dib222, dib333;
	IppImageToDib(result1, dib111);
	IppImageToDib(result2, dib222);
	IppImageToDib(result3, dib333);
	dib111.Save("result1.bmp");
	dib222.Save("result2.bmp");
	dib333.Save("result3.bmp");











	// 영상의 확대 축소 함수 예시 (img2 : 원본, img_result1 : 저장할 곳) 
	// IppResizeCubic(img2, img_result1, img2.GetWidth()/2, img2.GetHeight()/2);
	// IppResizeCubic(img2, img_result2, img2.GetWidth()*2, img2.GetHeight()*2);
	// IppResizeCubic(img2, img_result3, img2.GetWidth()/4, img2.GetHeight()/4);
	
	// Question: 내가 만약 RGB 파일을 받아서 GrayScale로 바꾸려고 하면, 어떻게 해야 할까? (윤지)
	IppDib dib2;
	dib2.Load("dog.bmp");
	IppRgbImage img2;
	IppDibToImage(dib2, img2);
	IppByteImage img_result1;
	img_result1.Convert(img2);

	// GrayScale 이미지 파일을 확대(*2)하고 축소(/2, /4) 해서 각각 result4.bmp, result5.bmp, result6.bmp로 저장하기!
	IppByteImage result4, result5, result6;
	IppResizeCubic(img_result1, result4, img_result1.GetWidth() * 2, img_result1.GetHeight() * 2);
	IppResizeCubic(img_result1, result5, img_result1.GetWidth() / 2, img_result1.GetHeight() / 2);
	IppResizeCubic(img_result1, result6, img_result1.GetWidth() / 4, img_result1.GetHeight() / 4);
	
	// Hint
	/*
		// 수정된 GrayScale파일을 BMP 파일로 변환
			IppDib dib2;
			IppImageToDib(img_result1, dib2);

		// 최종 BMP 파일을 저장
			dib2.Save("output.bmp");
	*/
	IppDib dib3, dib4, dib5;
	IppImageToDib(result4, dib3);
	IppImageToDib(result5, dib4);
	IppImageToDib(result6, dib5);
	dib3.Save("result4.bmp");
	dib4.Save("result5.bmp");
	dib5.Save("result6.bmp");


	// 1차원 배열 5개
	// 1. 원본을 담을 객체 5개
	IppDib original1, original2, original3, original4, original5; // (X)
	IppDib original[5]; // (O)

	// 2. * 2한 수정본을 담을 객체 5개
	IppDib mult2[5];

	// 3. / 2한 수정본을 담을 객체 5개
	IppDib div2[5];

	// 4. / 4한 수정본을 담을 객체 5개
	IppDib div4[5];



	// 2차원 배열 1개
	IppDib Pictures[5][4]; // (X) 나만 알 수 있는 코드는 잘 쓰지 않는다! 왜냐면 여기 3명이 없거든!


	return 0;
}