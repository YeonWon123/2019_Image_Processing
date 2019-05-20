#include "IppConvert.h"
#include "IppImage.h"
#include "IppFilter.h"

//    - ī�޶�� �Է¹޴� bmp ������ RGB �����̴ϱ�
//    - ���� �Է¹޴� bmp ������ RGB �����̶�� �����ϰ�,
//    - RGB ���� �Է� -> GrayScale�� ��ȯ -> Ȯ����� �˰��� ���� �� �ո������� ����
//    - ���� assert ������ �� ���, �ҷ������� ���� �̸��� �߸��Ǿ��ų�, bmp������ RGB������ �ƴ϶�� ������ �� �ִ�!

int main()
{
	// IppDib.h : BMP ���� �����!
	// IppImage.h : 2���� �迭�� �Ǿ� ����
	// �������� �ȼ� �� ����
	// IppRgbImage�� IppByteImage ��� IppImage.h �� ����

	/*
	IppDib dib;				// BMP ������ ������ϰ� �����ϱ� ���� IppDib ��ü ����, ������ ��� ����
	dib.Load("input.bmp");  // �� �ٿ��� ������ ��ü�� "input.bmp" ������ �ҷ��ͼ� ä��, IppDib ��ü(dib)�� ä����

	IppRgbImage img;		// RGB �̹��� ������ ���� IppRgbImage ��ü ����, ������ ��� ����
	IppDibToImage(dib, img); // �̹��� ������ ���ؼ��� IppDib Ŭ���� ��ü�� IppImage Ŭ���� ��ü�� ��ȯ�ؾ� ��

	IppByteImage img2;		// GrayScale �̹��� ������ ���� IppByteImage ��ü ����, ������ ��� ����
	img2.Convert(img);		// RGB ����(img)�� GrayScale ���Ϸ� ��ȯ(Convert)�Ͽ� IppByteImage ��ü(img2)�� ä��
	*/
	/*
		// ���� Question: ���� ���� RGB ������ �޾Ƽ� GrayScale�� �ٲٷ��� �ϸ�, ��� �ؾ� �ұ�? (����)
		IppDib dib3;
		dib3.Load("lena.bmp");
		IppRgbImage img3;
		IppDibToImage(dib3, img3);
		IppByteImage img3_2;
		img3_2.Convert(img3);
		*/
		// ���� Question: ���� ���� RGB ������ �޾Ƽ� GrayScale�� �ٲٷ��� �ϸ�, ��� �ؾ� �ұ�? (����)
		IppDib dib2; 
		dib2.Load("dog.bmp"); 
		IppRgbImage myimg;
		IppDibToImage(dib2, myimg);
		IppByteImage myimg2; 
		myimg2.Convert(myimg);


	// ������ GrayScale ������ ������ ��ü ����
	IppFloatImage img_result1;

	IppFilterGaussian(myimg2, img_result1, 2);
	//--------------------------------------------------------------//
	//																//
	//					IppImage Ŭ���� ��ü�� ����					//
	//					��, �̰��� BMP ������ ����...					//
	//																//
	//--------------------------------------------------------------//
		


	// ������ GrayScale������ BMP ���Ϸ� ��ȯ
	IppDib dib5;
	IppImageToDib(img_result1, dib5);

	// ���� BMP ������ ����
	dib5.Save("output.bmp");

	return 0;
}