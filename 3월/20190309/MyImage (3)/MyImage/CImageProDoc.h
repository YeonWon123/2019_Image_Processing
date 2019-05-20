#pragma once
#include "CMyImage.h"

template <typename T>
class CImageProDoc : public CMyImage <typename T>
{
public:
	unsigned char**inputImg;//�Է� ������ ��� ��ҿ� ���� ������ ����
	unsigned char**inputImg2;//�Է� ������ ��� ��ҿ� ���� ������ ����
	unsigned char**resultImg;//��� ������ ��� ��ҿ� ���� ������ ����
	int depth; //1=��鿵��, 3=�÷�����
	//��� ������ ũ�Ⱑ ��ȭ�Ǵ� �������� ó���� ���� ������ �߰��Ǵ� �ڵ�
	int gm_nWidth; //ũ�Ⱑ ���� ��� ������ ���� ũ��
	int gm_nHeight; //ũ�Ⱑ ���� ��� ������ ���� ũ�� 
	unsigned char**gResultImg; //ũ�Ⱑ ���� ��� ���� ���� ������ ���� 

	//�⺻������
	CImageProDoc(void)
		: CMyImage(), inputImg(NULL), inputImg2(NULL), resultImg(NULL), gResultImg(NULL)
	{ }

	//����,����,ä���� �Է� �޴� ������
	CImageProDoc(int nWidth, int nHeight, int nChannels = 1)
		: CMyImage(nWidth, nHeight, nChannels), inputImg(NULL), inputImg2(NULL), resultImg(NULL), gResultImg(NULL)
	{ }

	//Ȯ�� �Լ� 
	void GeometryZoominInterpolation()
	{
		float src_x, src_y;	//���� ȭ�� ��ġ
		float alpha, beta;
		int scale_x, scale_y;	//x����� y���������� Ȯ�� ����
		int E, F;	//x�������� ������ �����
		int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;	//������ ���� 4�� �ȼ��� ��ǥ

		scale_x = 2;
		scale_y = 2;

		//��� ������ ũ�� ����
		gm_nWidth = CMyImage<T>::m_nWidth * scale_x;
		gm_nHeight = CMyImage<T>::m_nHeight * scale_y;

		//��� ������ ������ ��� ��� ���� �Ҵ�
		gResultImg = new unsigned char*[gm_nHeight * sizeof(unsigned char*)];
		for (int i = 0; i < gm_nHeight * sizeof(unsigned char*); i++) {
			gResultImg[i] = new unsigned char[gm_nWidth*depth];
		}
		for (int y = 0; y < gm_nHeight; y++)
		{
			for (int x = 0; x < gm_nWidth; x++) {
				//���� ���󿡼��� �ȼ� ��ǥ ���
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

				//�ȼ� ��ġ�� ������ ��踦 ������� �˻�
				if (Bx > CMyImage<T>::m_nWidth - 1) Bx = CMyImage<T>::m_nWidth - 1;
				if (Dx > CMyImage<T>::m_nWidth - 1) Bx = CMyImage<T>::m_nWidth - 1;
				if (Cy > CMyImage<T>::m_nHeight - 1) Cy = CMyImage<T>::m_nHeight - 1;
				if (Dy > CMyImage<T>::m_nHeight - 1) Dy = CMyImage<T>::m_nHeight - 1;

				//x�������� ����
				E = (int)(inputImg[Ay][Ax] * (1 - alpha) + inputImg[By][Bx] * alpha);
				F = (int)(inputImg[Cy][Cx] * (1 - alpha) + inputImg[Dy][Dx] * alpha);

				//y�������� ����
				gResultImg[y][x] = (unsigned char)(E*(1 - beta) + F * beta);
			}
		}
	} //!!!���⿡ ������ �ʿ��մϴ� �߰ų� 
	//delete����
};  //!!!!���⿡ ;�� �ʿ��մϴ� ��