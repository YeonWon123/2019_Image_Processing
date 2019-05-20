#include "CMyImage.h"
#include <math.h>

unsigned char m_OutImg[512][512];
unsigned char m_InImg[512][512];

void m_ZoomOut(int height, int width, float zoomoutfactor)
{
	BYTE *pZoomImg;
	BYTE newValue;
	int new_height = (int)(height*zoomoutfactor);//새로운 이미지의 높이 계산 
	int new_width = (int)(width*zoomoutfactor);//새로운 이미지의 폭 계산 
	int heightm1 = height - 1;
	int widthm1 = width - 1;
	int where, org_where;
	int r, c;//타겟 이미지 좌표 
	float r_orgr, r_orgc;//원 이미지 상의 해당 좌표 (실수값)
	int i_orgr, i_orgc;//원 이미지 상의 해당 좌표 (정수값)
	float sr, sc;// 예 1.24-1=0.24
	float I1, I2, I3, I4;


	//Zoom Image를 위한 동적 메모리 할당
	pZoomImg = new BYTE[new_height*new_width];

	for (r = 0; r < new_height; r++)
		for (c = 0; c < new_width; c++)
		{
			r_orgr = r / zoomoutfactor;
			r_orgc = c / zoomoutfactor;
			i_orgr = floor(r_orgr);//예: floor(2.8)=2.0
			i_orgc = floor(r_orgc);
			sr = r_orgr - i_orgr;
			sc = r_orgc - i_orgc;
			//범위 조사 
			//원이미지의 범위를 벗어나는 경우 0값 할당 
			if (i_orgr<0 || i_orgr>heightm1 || i_orgc<0 || i_orgc>widthm1)
			{
				where = r * new_width + c;
				pZoomImg[where] = 0;
			}
			//원 이미지의 범위 내에 존재 이중 선형 보간 수행 
			else
			{
				I1 = (float)m_InImg[i_orgr][i_orgc];//(org_r,org_c)
				I2 = (float)m_InImg[i_orgr][i_orgc + 1];//(org_r,org_c+1)
				I3 = (float)m_InImg[i_orgr + 1][i_orgc + 1];//(org_r+1,org_c+1)
				I4 = (float)m_InImg[i_orgr + 1][i_orgc];//(org_r+1,org_c)

				//이중 선형 보간을 통한 새로운 밝기값 계산
				newValue = (BYTE)(I1*(1 - sc)*(1 - sr) + I2 * sc*(1 - sr) + I3 * sc*sr + I4 * (1 - sc)*sr);
				where = r * new_width + c;
				pZoomImg[where] = newValue;
			}
		}
	//일단 영상의 일부만 복사하는 것으로 함.
	for (r = 0; r < new_height; r++)
		for (c = 0; c < new_width; c++)
		{
			m_OutImg[r][c] = pZoomImg[r*new_width + c];
		}
	//동적 할당 메모리 해제 
	delete[] pZoomImg;
}

int main()
{
	CMyImage<BYTE> image1; // 생성자 호출
	image1.LoadImage("dog.bmp");
	
	int nWidth = image1.GetWidth();   // 영상의 너비
	int nHeight = image1.GetHeight();  // 영상의 높이
	int nChannel = image1.GetChannel(); // 영상의 채널 수
	
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