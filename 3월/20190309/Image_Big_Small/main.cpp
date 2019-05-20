#include <iostream>
#include "ImageClass.h"
using namespace std;

#define _USE_MATH_DEFINES
#include <math.h>

CByteImage	m_imageIn;
CByteImage	m_imageOut;
int			m_nWidth;
int			m_nHeight;
int			m_nWStep;
BYTE*		m_pOut;

int		m_nSelIntp = 1;
double	m_dTransX = 0;
double	m_dTransY = 0;
double	m_dRotation = 0;
double	m_dScale = 2.0;
double	m_dH1 = 1.0;
double	m_dH2 = 0;
double	m_dH3 = 0;
double	m_dH4 = 0;
double	m_dH5 = 0;
double	m_dH6 = 0;
double	m_dH7 = 0;
double	m_dH8 = 0;
double	m_dH9 = 1.0;

int main(int argc, char** argv)
{
	m_imageIn.LoadImage("lena.bmp");
	if (m_imageIn.IsEmpty())
	{
		cout << "파일이 없음!" << endl;
		return 0;
	}
	
	m_nWidth = m_imageIn.GetWidth();
	m_nHeight = m_imageIn.GetHeight();
	m_nWStep = m_imageIn.GetWStep();
	m_imageOut = CByteImage(m_nWidth, m_nHeight);
	m_pOut = m_imageOut.GetPtr();
	
	m_imageOut.SetConstValue(0);

	double cR = cos(m_dRotation*M_PI / 180.0);
	double sR = sin(m_dRotation*M_PI / 180.0);
	double z = 1.0 / m_dScale;
	double cx = m_nWidth / 2.0;  // 영상 가로 중심
	double cy = m_nHeight / 2.0; // 영상 세로 중심

	m_dH1 = z * cR;
	m_dH2 = z * sR;
	m_dH3 = z * (cR*(-cx) + sR * (-cy)) + cx - m_dTransX;
	m_dH4 = -z * sR;
	m_dH5 = z * cR;
	m_dH6 = z * (-sR * (-cx) + cR * (-cy)) + cy - m_dTransY;
	m_dH7 = 0;
	m_dH8 = 0;
	m_dH9 = 1;

	int r, c;
	for (r = 0; r < m_nHeight; r++)
	{
		for (c = 0; c < m_nWidth; c++)
		{
			double srcX = z * (cR*(c - cx) + sR * (r - cy)) + cx - m_dTransX;
			double srcY = z * (-sR * (c - cx) + cR * (r - cy)) + cy - m_dTransY;
			if (srcX >= 0 && srcX < m_nWidth && srcY >= 0 && srcY < m_nHeight)
			{
				switch (m_nSelIntp)
				{
				case 0:
					m_pOut[r*m_nWStep + c] = m_imageIn.NearestNeighbor(srcX, srcY);
					break;
				case 1:
					m_pOut[r*m_nWStep + c] = m_imageIn.BiLinearIntp(srcX, srcY);
					break;
				case 2:
					m_pOut[r*m_nWStep + c] = m_imageIn.CubicConvIntp(srcX, srcY);
					break;
				case 3:
					m_pOut[r*m_nWStep + c] = m_imageIn.BiCubicIntp(srcX, srcY);
					break;
				default:
					break;
				}
			}
		}
	}

	m_imageOut.SaveImage("Warped.bmp");
	return 0;
}