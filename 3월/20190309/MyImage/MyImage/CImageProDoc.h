#pragma once
#include <stdio.h>
#include "CMyImage.h"

template <typename T>
class CImageProDoc : public CMyImage <typename T>
{
public:
	unsigned char**inputImg;//�Է� ������ ��� ��ҿ� ���� ������ ����
	unsigned char**inputImg2;//�Է� ������ ��� ��ҿ� ���� ������ ����
	unsigned char**resultImg;//�x�� ������ ��� ��ҿ� ���� ������ ����
	int imageWidth; //������ ����ũ��
	int imageHeight; //������ ���� ũ��
	int depth; //1=��鿵��, 3=�÷�����

	//��� ������ ũ�Ⱑ ��ȭ�Ǵ� �������� ó���� ���� ������ �߰��Ǵ� �ڵ�
	int gImageWidth; //ũ�Ⱑ ���� ��� ������ ���� ũ��
	int gImageHeight; //ũ�Ⱑ ���� ��� ������ ���� ũ�� 
	unsigned char**gResultImg; //ũ�Ⱑ ���� ��� ���� ���� ������ ���� 

	CImageProDoc(void)
		: inputImg(NULL), inputImg2(NULL), resultImg(NULL), gResultImg(NULL)
	{ }

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
		gImageWidth = imageWidth * scale_x;
		gImageHeight = imageHeight * scale_y;

		//��� ������ ������ ��� ��� ���� �Ҵ�
		gResultImg = new unsigned char*[gImageHeight];
		for (int i = 0; i < gImageHeight; i++) {
			gResultImg[i] = new unsigned char[gImageWidth*depth];
		}
		for (int y = 0; y < gImageHeight; y++)
		{
			for (int x = 0; x < gImageWidth; x++) {
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
				if (Bx > imageWidth - 1) Bx = imageWidth - 1;
				if (Dx > imageWidth - 1) Bx = imageWidth - 1;
				if (Cy > imageHeight - 1) Cy = imageHeight - 1;
				if (Dy > imageHeight - 1) Dy = imageHeight - 1;

				//x�������� ����
				E = (CMyImage<typename int>::m_pImageData[Ay] * (1 - alpha) + CMyImage<typename int>::m_pImageData[By] * alpha);
				F = (CMyImage<typename int>::m_pImageData[Cy] * (1 - alpha) + CMyImage<typename int>::m_pImageData[Dy] * alpha);

				//y�������� ����
				gResultImg[y][x] = (unsigned char)(E*(1 - beta) + F * beta);
			}
		}
	}
	//delete����
};