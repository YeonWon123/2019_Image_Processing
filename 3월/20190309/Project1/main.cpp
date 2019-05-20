#include "IppConvert.h"
#include "IppGeometry.h"

// ���?
// 1. bmp ������ RGB���� �׷��̽��������� �Ǵ��� �� �ִ���?
//    - ī�޶�� �Է¹޴� bmp ������ RGB �����̴ϱ�, GrayScale���� �Ǵ��� ���ǹ�
//    - ���� �Է¹޴� bmp ������ RGB �����̶�� �����ϰ�,
//    - RGB ���� �Է� -> GrayScale�� ��ȯ -> Ȯ����� �˰��� ���� �� �ո������� ����
//    - ���� assert ������ �� ���, �� bmp������ RGB������ �ƴ϶�� ������ �� �ִ�!

// 2. Ȯ��, ����� ������ ����ȭ�� �� �ִ���?
//    - *2, /2, /4 ���� �ʿ��ϹǷ�, Save�� 3�� �õ��ϸ� ��
//    - �� �������� *2�� ���� �ϰ� �װ��� �� ��ü�� ��� Save �ϰ�
//    - �������� /2�� �ϰ� �װ��� �ٸ� ��ü�� ��� Save �ϰ�
//    - ���������� /4�� �ϰ� �װ��� �ٸ� ��ü�� ��� Save �Ѵ�!

int main()
{
	// ������ Ȯ�� ��� �Լ� ���� (img2 : ����, img_result1 : ������ ��) 
	// IppResizeCubic(img2, img_result1, img2.GetWidth()/2, img2.GetHeight()/2);
	// IppResizeCubic(img2, img_result2, img2.GetWidth()*2, img2.GetHeight()*2);
	// IppResizeCubic(img2, img_result3, img2.GetWidth()/4, img2.GetHeight()/4);
	

	// Question: ���� ���� RGB ������ �޾Ƽ� GrayScale�� �ٲٷ��� �ϸ�, ��� �ؾ� �ұ�? (����)
	IppDib dib8;
	dib8.Load("lena.bmp");
	IppRgbImage img3;
	IppDibToImage(dib8, img3);
	IppByteImage img3_2;
	img3_2.Convert(img3);

	// GrayScale �̹��� ������ Ȯ��(*2)�ϰ� ���(/2, /4) �ؼ� ���� result1.bmp, result2.bmp, result3.bmp�� �����ϱ�!
	IppByteImage result1, result2, result3;
	IppResizeCubic(img3_2, result1, img3_2.GetWidth() * 2, img3_2.GetHeight() * 2);
	IppResizeCubic(img3_2, result2, img3_2.GetWidth() / 2, img3_2.GetHeight() / 2);
	IppResizeCubic(img3_2, result3, img3_2.GetWidth() / 4, img3_2.GetHeight() / 4);

	// Hint
	/*
	// ������ GrayScale������ BMP ���Ϸ� ��ȯ
		IppDib dib2;
		IppImageToDib(img_result1, dib2);+

	// ���� BMP ������ ����
		dib2.Save("output.bmp");
	*/

	IppDib dib111, dib222, dib333;
	IppImageToDib(result1, dib111);
	IppImageToDib(result2, dib222);
	IppImageToDib(result3, dib333);
	dib111.Save("result1.bmp");
	dib222.Save("result2.bmp");
	dib333.Save("result3.bmp");











	// ������ Ȯ�� ��� �Լ� ���� (img2 : ����, img_result1 : ������ ��) 
	// IppResizeCubic(img2, img_result1, img2.GetWidth()/2, img2.GetHeight()/2);
	// IppResizeCubic(img2, img_result2, img2.GetWidth()*2, img2.GetHeight()*2);
	// IppResizeCubic(img2, img_result3, img2.GetWidth()/4, img2.GetHeight()/4);
	
	// Question: ���� ���� RGB ������ �޾Ƽ� GrayScale�� �ٲٷ��� �ϸ�, ��� �ؾ� �ұ�? (����)
	IppDib dib2;
	dib2.Load("dog.bmp");
	IppRgbImage img2;
	IppDibToImage(dib2, img2);
	IppByteImage img_result1;
	img_result1.Convert(img2);

	// GrayScale �̹��� ������ Ȯ��(*2)�ϰ� ���(/2, /4) �ؼ� ���� result4.bmp, result5.bmp, result6.bmp�� �����ϱ�!
	IppByteImage result4, result5, result6;
	IppResizeCubic(img_result1, result4, img_result1.GetWidth() * 2, img_result1.GetHeight() * 2);
	IppResizeCubic(img_result1, result5, img_result1.GetWidth() / 2, img_result1.GetHeight() / 2);
	IppResizeCubic(img_result1, result6, img_result1.GetWidth() / 4, img_result1.GetHeight() / 4);
	
	// Hint
	/*
		// ������ GrayScale������ BMP ���Ϸ� ��ȯ
			IppDib dib2;
			IppImageToDib(img_result1, dib2);

		// ���� BMP ������ ����
			dib2.Save("output.bmp");
	*/
	IppDib dib3, dib4, dib5;
	IppImageToDib(result4, dib3);
	IppImageToDib(result5, dib4);
	IppImageToDib(result6, dib5);
	dib3.Save("result4.bmp");
	dib4.Save("result5.bmp");
	dib5.Save("result6.bmp");


	// 1���� �迭 5��
	// 1. ������ ���� ��ü 5��
	IppDib original1, original2, original3, original4, original5; // (X)
	IppDib original[5]; // (O)

	// 2. * 2�� �������� ���� ��ü 5��
	IppDib mult2[5];

	// 3. / 2�� �������� ���� ��ü 5��
	IppDib div2[5];

	// 4. / 4�� �������� ���� ��ü 5��
	IppDib div4[5];



	// 2���� �迭 1��
	IppDib Pictures[5][4]; // (X) ���� �� �� �ִ� �ڵ�� �� ���� �ʴ´�! �ֳĸ� ���� 3���� ���ŵ�!


	return 0;
}