#include "CMyImage.h"
#include <math.h>

unsigned char m_OutImg[512][512];
unsigned char m_InImg[512][512];

void m_ZoomOut(int height, int width, float zoomoutfactor)
{
	BYTE *pZoomImg;
	BYTE newValue;
	int new_height = (int)(height*zoomoutfactor);//���ο� �̹����� ���� ��� 
	int new_width = (int)(width*zoomoutfactor);//���ο� �̹����� �� ��� 
	int heightm1 = height - 1;
	int widthm1 = width - 1;
	int where, org_where;
	int r, c;//Ÿ�� �̹��� ��ǥ 
	float r_orgr, r_orgc;//�� �̹��� ���� �ش� ��ǥ (�Ǽ���)
	int i_orgr, i_orgc;//�� �̹��� ���� �ش� ��ǥ (������)
	float sr, sc;// �� 1.24-1=0.24
	float I1, I2, I3, I4;


	//Zoom Image�� ���� ���� �޸� �Ҵ�
	pZoomImg = new BYTE[new_height*new_width];

	for (r = 0; r < new_height; r++)
		for (c = 0; c < new_width; c++)
		{
			r_orgr = r / zoomoutfactor;
			r_orgc = c / zoomoutfactor;
			i_orgr = floor(r_orgr);//��: floor(2.8)=2.0
			i_orgc = floor(r_orgc);
			sr = r_orgr - i_orgr;
			sc = r_orgc - i_orgc;
			//���� ���� 
			//���̹����� ������ ����� ��� 0�� �Ҵ� 
			if (i_orgr<0 || i_orgr>heightm1 || i_orgc<0 || i_orgc>widthm1)
			{
				where = r * new_width + c;
				pZoomImg[where] = 0;
			}
			//�� �̹����� ���� ���� ���� ���� ���� ���� ���� 
			else
			{
				I1 = (float)m_InImg[i_orgr][i_orgc];//(org_r,org_c)
				I2 = (float)m_InImg[i_orgr][i_orgc + 1];//(org_r,org_c+1)
				I3 = (float)m_InImg[i_orgr + 1][i_orgc + 1];//(org_r+1,org_c+1)
				I4 = (float)m_InImg[i_orgr + 1][i_orgc];//(org_r+1,org_c)

				//���� ���� ������ ���� ���ο� ��Ⱚ ���
				newValue = (BYTE)(I1*(1 - sc)*(1 - sr) + I2 * sc*(1 - sr) + I3 * sc*sr + I4 * (1 - sc)*sr);
				where = r * new_width + c;
				pZoomImg[where] = newValue;
			}
		}
	//�ϴ� ������ �Ϻθ� �����ϴ� ������ ��.
	for (r = 0; r < new_height; r++)
		for (c = 0; c < new_width; c++)
		{
			m_OutImg[r][c] = pZoomImg[r*new_width + c];
		}
	//���� �Ҵ� �޸� ���� 
	delete[] pZoomImg;
}

int main()
{
	CMyImage<BYTE> image1; // ������ ȣ��
	image1.LoadImage("dog.bmp");
	
	int nWidth = image1.GetWidth();   // ������ �ʺ�
	int nHeight = image1.GetHeight();  // ������ ����
	int nChannel = image1.GetChannel(); // ������ ä�� ��
	
	CMyImage<BYTE> image2(nWidth, nHeight);
	image2.SetConstValue(0);

	for (int i = 0; i < nWidth; i++)
	{
		for (int j = 0; j < nHeight; j++)
		{
			m_InImg[i][j] = image1.m_pImageData[i * image1.m_nWStep + j];
		}
	}

	m_ZoomOut(nWidth, nHeight, 1);
	
	for (int i = 0; i < nWidth; i++)
	{
		for (int j = 0; j < nHeight; j++)
		{
			image2.m_pImageData[i * image1.m_nWStep + j] = m_OutImg[i][j];
		}
	}

	image2.SaveImage("small2.bmp");

	return 0;
}