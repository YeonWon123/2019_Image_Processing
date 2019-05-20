#include <windows.h> // BYTE 데이터형 사용 가능 (typedef unsigned char BYTE)
#include <assert.h>
#include <stdio.h>

// 원본 데이터형이 int나 double형이고 변환 결과 영상이 BYTE형일 때, 0~255를 넘어서서 변환되므로
// 0 미만일 경우 0, 255 이상일 경우 255, 둘 다 아닐 경우 그 값을 변환하게 하는 매크로이다.
#define CLIP(x) (x < 0) ? 0 : x > 255 ? 255 : x

// CMyImage 클래스를 템플릿으로 정의한다.
// 이는 영상이 회색조나 컬러 영상과 같은 통상적인 형태(int형)가 아닐 수 있기 때문입니다.
// 가우시안 필터를 이용하여 영상을 보정할 때에는, 영상의 각 픽셀에 실수 값이 곱해지기 때문에
// 영상도 각 픽셀이 실수 값을 가지게 됩니다.
template <typename T>
class CMyImage
{
public:
	// 기본 생성자 (이 클래스는 템플릿을 이용하여 정의되므로, 선언과 정의를 같이 쓴다.)
	CMyImage(void)
		: m_nChannels(0), m_nHeight(0), m_nWidth(0), m_nWStep(0), m_pImageData(NULL)
	{   }

	// 영상의 크기와 채널 수를 매개 변수로 받아
	// 픽셀 데이터의 메모리까지 할당하는 생성자의 정의
	// 한 행당 데이터 원소 수(m_nWStep)는
	// 영상의 가로 픽셀 수와 채널 수, 픽셀 데이터형의 크기 
	// 세 값의 조합으로 정해진다.
	CMyImage(int nWidth, int nHeight, int nChannels = 1)
		: m_nChannels(nChannels)
		, m_nHeight(nHeight)
		, m_nWidth(nWidth)
		, m_nWStep(((nWidth*nChannels * sizeof(T) + 3)&~3) / sizeof(T))
	{
		m_pImageData = new T[m_nHeight*m_nWStep];
	}

	// CMyImage 클래스는 동적으로 할당되는 메모리의 포인터를 멤버 변수로 가지므로,
	// 클래스를 복사한 객체를 생성할 때에는, 픽셀 데이터를 포함한 클래스 전체를 복사한다.
	// 즉 깊은 복사(deep copy)를 해야 하므로, 복사 생성자를 재정의한다.
	CMyImage(const CMyImage& myImage)
	{
		// 영상 정보에 대한 멤버 변수는 등호(=)연산자를 이용하여 그대로 대입
		m_nChannels = myImage.m_nChannels;
		m_nHeight = myImage.m_nHeight;
		m_nWidth = myImage.m_nWidth;
		m_nWStep = myImage.m_nWStep;
		// 픽셀 데이터 포인터인 m_pImageData 멤버 변수는 
		// 새로운 메모리를 할당하고 나서 memcpy() 함수를 이용하여
		// 한 번에 픽셀 데이터의 덩어리를 복사하는 방법 사용
		m_pImageData = new T[m_nHeight*m_nWStep];
		// memcpy(복사되는 곳의 위치, 복사할 데이터의 위치, 바이트 수);
		memcpy(m_pImageData, myImage.m_pImageData, m_nHeight*m_nWStep * sizeof(T));
	}

	// 변환 생성자 구현
	// 등호(=) 연산자를 이용하여 대입 연산을 할 때
	// 대입 연산이 수행되기 전에 우변을 좌변의 데이터 형식에 맞게 미리 형변환
	template <typename From>
	CMyImage(const CMyImage<From>& myImage)
	{
		// ----- 복사 생성자와 동일한 부분  ----- //
		m_nChannels = myImage.GetChannel();
		m_nHeight = myImage.GetHeight();
		m_nWidth = myImage.GetWidth();
		m_nWStep = ((m_nWidth*m_nChannels * sizeof(T) + 3)&~3) / sizeof(T);
		m_pImageData = new T[m_nHeight*m_nWStep];
		// ------------------------------------ //

		// -------- 픽셀 단위로 변환함 --------- //
		int nWStep = myImage.GetWStep();

		if (sizeof(T) == 1)
		{
			for (int r = 0; r < m_nHeight; r++)
			{
				T* pDst = GetPtr(r);
				From* pSrc = myImage.GetPtr(r);
				for (int c = 0; c < nWStep; c++)
				{
					pDst[c] = (T)CLIP(pSrc[c]);
				}
			}
		}
		else
		{
			for (int r = 0; r < m_nHeight; r++)
			{
				T* pDst = GetPtr(r);
				From* pSrc = myImage.GetPtr(r);
				for (int c = 0; c < nWStep; c++)
				{
					pDst[c] = (T)pSrc[c];
				}
			}
		}
		// -------------------------------------- //
	}

	// 기본 소멸자
	// 포인터 m_pImageData 멤버 변수에 할당된 값이 있을 때
	// 이를 delete 예약어를 사용하여 메모리를 해제한다.
	~CMyImage(void)
	{
		if (m_pImageData) delete[] m_pImageData;
	}

	// 복사 생성자와 대입 연산자의 재정의
	CMyImage& operator=(const CMyImage& myImage)
	{
		if (this == &myImage)
			return *this;

		m_nChannels = myImage.m_nChannels;
		m_nHeight = myImage.m_nHeight;
		m_nWidth = myImage.m_nWidth;
		m_nWStep = myImage.m_nWStep;

		if (m_pImageData)
			delete[] m_pImageData;

		if (myImage.m_pImageData != NULL)
		{
			m_pImageData = new T[m_nHeight*m_nWStep];
			memcpy(m_pImageData, myImage.m_pImageData, m_nHeight*m_nWStep * sizeof(T));
		}

		return *this;
	}

	// 멤버 함수
	int GetChannel() const { return m_nChannels; }
	int GetHeight() const { return m_nHeight; }
	int GetWidth() const { return m_nWidth; }
	int GetWStep() const { return m_nWStep; }

	// 영상 픽셀 데이터의 포인터를 얻는 함수
	// 원하는 세로(행) 좌표 r 및 가로(열) 좌표 c를 입력받아서
	// 해당 위치의 포인터를 반환한다. (포인터 값을 계산하여 반환)
	// 행 위치와 열 위치의 기본 값은 0으로 설정한다. 
	// (포인터의 처음 위치를 얻을 때 매개 변수를 전혀 입력하지 않아도 되게..)
	T* GetPtr(int r = 0, int c = 0) const { return m_pImageData + r * m_nWStep + c; }

	// 소수 픽셀에 접근하는 함수를 inline 함수로 정의(코드의 길이가 짧기 때문)
	// 영상에서, 가로와 세로 위치인 x, y 그리고 채널 순서 c에 해당하는 픽셀의 참조자를 받아오는 함수
	// 회색조 영상의 채널 순서 c값은 0이다.
	inline T& GetAt(int x, int y, int c = 0) const
	{
		// assert 매크로를 이용하여 혹시 유효하지 않은 위치
		// 즉 영상의 크기를 벗어나는 위치에 접근하려고 하는 것은 아닌지 검사하여 준다.
		assert(x >= 0 && x < m_nWidth && y >= 0 && y < m_nHeight);
		return m_pImageData[m_nWStep*y + m_nChannels * x + c];
	}

	// 알고리즘 수행 도중 임시 값 또는 결과값을 저장할 공간으로 새로운 영상을 만들어
	// 전체 픽셀의 값을 특정 상수로 초기화하는 함수
	void SetConstValue(T val)
	{
		if (val == 0)   // 조건 (1) : 초기화할 값이 0일 경우 memset 함수 사용
		{
			memset(m_pImageData, 0, m_nWStep*m_nHeight * sizeof(T));
			return;
		}

		if (sizeof(T) == 1)  // 조건 (2) : 영상의 데이터 형식이 BYTE형일 경우 memset 함수 사용
		{
			memset(m_pImageData, val, m_nWStep*m_nHeight);
		}
		else  // 나머지 경우들 : 이 경우는 for문을 이용하여 모든 픽셀을 하나씩 방문하면서 초기화
		{
			T* pData = m_pImageData;
			for (int r = 0; r < m_nHeight; r++)
			{
				for (int c = 0; c < m_nWidth; c++)
				{
					pData[c] = val;
				}
				pData += m_nWStep;
			}
		}
	}

	// 영상의 데이터가 유효한지를 검사하는 함수
	bool IsEmpty() const
	{
		return m_pImageData ? false : true;
	}

	bool LoadImage(const char* filename)
	{
		assert(sizeof(T) == 1); // BYTE형의 경우만 가능

		if (strcmp(".BMP", &filename[strlen(filename) - 4]))
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, filename, "rb"); // 바이너리 읽기 모드
			if (!pFile)
				return false;

			BITMAPFILEHEADER fileHeader;

			if (!fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pFile))
			{
				fclose(pFile);
				return false;
			}

			if (fileHeader.bfType != 0x4D42) // 'BM' 문자 검사
			{
				fclose(pFile);
				return false;
			}

			BITMAPINFOHEADER infoHeader;
			if (!fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, pFile))
			{
				fclose(pFile);
				return false;
			}

			if (infoHeader.biBitCount != 8 && infoHeader.biBitCount != 24)
			{
				fclose(pFile);
				return false;
			}

			if (m_nWidth != infoHeader.biWidth && m_nHeight != infoHeader.biHeight
				&& m_nChannels != infoHeader.biBitCount / 8)
			{
				if (m_pImageData)
					delete[] m_pImageData;

				m_nChannels = infoHeader.biBitCount / 8;
				m_nHeight = infoHeader.biHeight;
				m_nWidth = infoHeader.biWidth;
				m_nWStep = (m_nWidth*m_nChannels * sizeof(T) + 3)&~3;

				m_pImageData = new T[m_nHeight*m_nWStep];
			}

			fseek(pFile, fileHeader.bfOffBits, SEEK_SET);

			int r;
			for (r = m_nHeight - 1; r >= 0; r--)
			{
				if (!fread(&m_pImageData[r*m_nWStep], sizeof(BYTE), m_nWStep, pFile))
				{
					fclose(pFile);
					return false;
				}
			}

			fclose(pFile);

			return true;
		}
		else
		{
			return false;
		}
	}

	bool SaveImage(const char* filename)
	{
		assert(sizeof(T) == 1); // BYTE형의 경우만 가능

		if (strcmp(".BMP", &filename[strlen(filename) - 4]))
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, filename, "wb");
			if (!pFile)
				return false;

			BITMAPFILEHEADER fileHeader;
			fileHeader.bfType = 0x4D42; // 'BM'
			fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + m_nWStep * m_nHeight + (m_nChannels == 1) * 1024;
			fileHeader.bfReserved1 = 0;
			fileHeader.bfReserved2 = 0;
			fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (m_nChannels == 1) * 256 * sizeof(RGBQUAD);

			fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pFile);

			BITMAPINFOHEADER infoHeader;
			infoHeader.biSize = sizeof(BITMAPINFOHEADER);
			infoHeader.biWidth = m_nWidth;
			infoHeader.biHeight = m_nHeight;
			infoHeader.biPlanes = 1;
			infoHeader.biBitCount = m_nChannels * 8;
			infoHeader.biCompression = BI_RGB;
			infoHeader.biSizeImage = m_nWStep * m_nHeight;
			infoHeader.biClrImportant = 0;
			infoHeader.biClrUsed = 0;
			infoHeader.biXPelsPerMeter = 0;
			infoHeader.biYPelsPerMeter = 0;

			fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

			if (m_nChannels == 1)
			{
				for (int l = 0; l < 256; l++)
				{
					RGBQUAD GrayPalette = { l, l, l, 0 };
					fwrite(&GrayPalette, sizeof(RGBQUAD), 1, pFile);
				}
			}

			int r;
			for (r = m_nHeight - 1; r >= 0; r--)
			{
				fwrite(&m_pImageData[r*m_nWStep], sizeof(BYTE), m_nWStep, pFile);
			}

			fclose(pFile);
			return true;
		}
		else
		{
			return false;
		}
	}
public:
	T* m_pImageData; // 픽셀 배열 포인터, 멤버 변수 형식의 템플릿 정의

	// 멤버 변수
	int m_nChannels; // 채널 수
	int m_nHeight;   // 세로 픽셀 수
	int m_nWidth;    // 가로 픽셀 수
	int m_nWStep;    // 한 행당 데이터 원소 수

};

// 한 행당 데이터 원소 수는
// 영상의 가로 픽셀 수와 채널 수, 픽셀 데이터형의 크기 세 값의 조합으로 정해진다.
// m_nWStep = ((nWidth*nChannels*sizeof(T)+3)&~3) / sizeof(T);

typedef CMyImage <BYTE  > CByteImage;
typedef CMyImage <int   > CIntImage;
typedef CMyImage <float > CFloatImage;
typedef CMyImage <double> CDoubleImage;

