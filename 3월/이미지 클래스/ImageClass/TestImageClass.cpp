#include <iostream>
#include <tchar.h>
#include "ImageClass.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	CByteImage image1(640, 480); // ������ ȣ��
	image1.SetConstValue(0);	 // 0���� �ʱ�ȭ

	CByteImage image2(image1); // ���� ������ ȣ��
	CByteImage image3;		   // �⺻ ������ ȣ��
	image3 = image1;		   // ���� ������ ȣ��

	int nWidth = image1.GetWidth();   // ������ �ʺ�
	int nHeight = image1.GetHeight();  // ������ ����
	int nChannel = image1.GetChannel(); // ������ ä�� ��

	double incX = 255.0 / nWidth;
	double incY = 255.0 / nHeight;
	int r, c;
	for (r = 0; r < nHeight; r++) // �� ���� �̵�
	{
		for (c = 0; c < nWidth; c++) // �� ���� �̵�
		{
			image2.GetAt(c, r) = (BYTE)(c*incX); // ���� �׶��̼�
			image3.GetAt(c, r) = (BYTE)(r*incY); // ���� �׶��̼�
		}
	}

	// ��� ���� ����
	image1.SaveImage("Black.bmp");
	image2.SaveImage("GradationX.bmp");
	image3.SaveImage("GradationY.bmp");

	return 0;
}