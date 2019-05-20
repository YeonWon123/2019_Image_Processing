#pragma once
#include <windows.h>
#include <assert.h>
#include <stdio.h>

#define CLIP(x) (x < 0)? 0 : x > 255 ? 255 : x

template<typename T>
class CMyImage {
public:
	//기본 생성자
	CMyImage(void) :m_nChannels(0), m_nHeight(0), m_nWidth(0), m_nWStep(0), m_pImageData(NULL) {}
	//기본 생성자 overloading
	CMyImage(int nWidth, int nHeight, int nChannels = 1) : m_nChannels(nChannels), m_nHeight(nHeight), m_nWidth(nWidth),
		m_nWStep(((nWidth*nChannels * sizeof(T) + 3)&~3) / sizeof(T))/*4의 배수로 맞추기 위해서*/ {
		m_pImageData = new T[m_nHeight*m_nWStep];
		//2차원 배열이 아닌 1차원 배열로 만든다.u
	}
	//복사 생성자(깊은 복사)
	CMyImage(const CMyImage& myImage) {
		m_nChannels = myImage.m_nChannels;
		m_nHeight = myImage.m_nHeight;
		m_nWidth = myImage.m_nWidth;
		m_nWStep = myImage.m_nWStep;
		m_pImageData = new T[m_nHeight*m_nWStep];
		memcpy(m_pImageData, myImage.m_pImageData, m_nHeight*m_nWStep * sizeof(T));
	}

	//대입 연산자
	CMyImage& operator=(const CMyImage& myImage) {
		if (this == &myImage) {
			return *this;
		}
		m_nChannels = myImage.m_nChannels;
		m_nHeight = myImage.m_nHeight;
		m_nWidth = myImage.m_nWidth;
		m_nWStep = myImage.m_nWStep;
		if (m_pImageData) {
			delete[] m_pImageData;
		}
		if (myImage.m_pImageData != NULL) {
			m_pImageData = new T[m_nHeight*m_nWStep];
			memcpy(m_pImageData, myImage.m_pImageData, m_nHeight*m_nWStep * sizeof(T));
		}
		return *this;
	}

	//형변환 생성자
	template <typename From>
	CMyImage(const CMyImage<From>& myImage) {
		m_nChannels = myImage.GetChannel();
		m_nHeight = myImage.GetHeight();
		m_nWidth = myImage.GetWidth();
		m_nWStep = ((m_nWidth*m_nChannels * sizeof(T) + 3)&~3) / sizeof(T);//데이터 형식변화로 다시 계산해야한다. 
		m_pImageData = new T[m_nHeight*m_nWStep];

		//---픽셀단위로 변환
		int nWStep = myImage.GetWStep();

		if (sizeof(T) == 1) { //만약 원본데이터형이 int, double이고 반환결과 영상이 BYTE형이면 0~255사이를 벗어나는 값은 전혀 엉뚱한 값으로 변환되기 떄문에 CLIP()매크로를 사용해야함
			for (int r = 0; r < m_nHeight; r++) {
				T* pDst = GetPtr(r);
				From* pSrc = myImage.GetPtr(r);
				for (int c = 0; c < nWStep; c++) {
					pDst[c] = (T)CLIP(pSrc[c]);
				}
			}
		}
		else {
			for (int r = 0; r < m_nHeight; r++) {
				T* pDst = GetPtr(r);
				From* pSrc = myImage.GetPtr(r);
				for (int c = 0; c < nWStep; c++) {
					pDst[c] = (T)pSrc[c];
					//픽셀의 데이터형에 따라 메모리에 저장되는 모습이 전혀 다르기 떄문에 for문을 이용하여 한 픽셀씩 직접 변환을 수행
				}
			}
		}
		//---픽셀단위로 변환 끝
	}

	//특정 픽셀에 접근
	inline T& GetAt(int x, int y, int c = 0) const {
		//회색조 영상의 채널 순서 c값은 항상 0이므로 기본 매개변수로 0 지정. 
		assert(x >= 0 && x < m_nWidth && y >= 0 && y < m_nHeight);
		//디버깅할 때 내부 조건에 만족 안될 시 오류를 발생시킨. 실제 프로그램을 실행할 때는 해당 코드는 사라진다.
		return m_pImageData[m_nWStep*y + m_nChannels * x + c];
		//참조자를 반환하기 떄문에 반환된 픽셀값을 변경할 수 있음.
	}

	//모든 픽셀의 값을 상수값으로 초기화
	void SetConstValue(T val)
	{
		// 초기화할 값이 0인 경우
		if (val == 0) {
			memset(m_pImageData, 0, m_nWStep*m_nHeight * sizeof(T));
			return;
		}

		// 영상의 데이터 형식이 BYTE형인 경우
		if (sizeof(T) == 1) {
			memset(m_pImageData, val, m_nWStep*m_nHeight);
		}
		//위의 두 경우에만 memset()함수를 쓸 수 있다. 
		//그래서 이 함수가 속도가 훨씬 빠름에도 밑의 경우에서는 픽셀 하나하나에 값을 입력한다. 

		//나머지 경우들
		else {
			T* pData = m_pImageData;
			for (int r = 0; r < m_nHeight; r++) {
				for (int c = 0; c < m_nWidth; c++) {
					pData[c] = val;
				}
				pData += m_nWStep;
			}
		}
	}

	//영상의 데이터가 유효한지를 검사.
	bool IsEmpty() const {
		return m_pImageData ? false : true;
		//m_pImageData포인터변수가 NULL값을 갖는지를 검사.
	}

	//기본 소멸자
	~CMyImage(void) {
		if (m_pImageData) {
			delete[] m_pImageData;
		}
	}

	int GetChannel()   const { return m_nChannels; }
	int GetHeight()   const { return m_nHeight; }
	int GetWidth()   const { return m_nWidth; }
	int GetWStep()   const { return m_nWStep; }
	T* GetPtr(int r = 0, int c = 0) const { return m_pImageData + r * m_nWStep + c; }
	/*GetPtr 함수는 영상 픽셀 데이터 특정 위치의 포인터를 반환한다.
	실제 프로그램을 작성할 시 행과 열을 각각 입력하지 않고 1차원 배열이기 때문에
	행단위로 포인터를 획득하는 경우가 많아서 변수 c의 기본값을 0으로 설정해 입력하지 않아도 되도록 했다.
	또한 변수 r을 0으로 설정해 영상 데이터 포인터의 처음 위치를 얻고자 할 때는 매개변수를 입력하지 않아도 된다.*/

	bool LoadImage(const char* filename) {
		assert(sizeof(T) == 1); // BYTE형의 경우만 가능

		if (strcmp(".BMP", &filename[strlen(filename) - 4])) {
			FILE* pFile = NULL;
			fopen_s(&pFile, filename, "rb"); // 바이너리 읽기 모드
			if (!pFile)
				return false;

			BITMAPFILEHEADER fileHeader;

			if (!fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pFile)) {
				fclose(pFile);
				return false;
			}

			if (fileHeader.bfType != 0x4D42) { // 'BM' 문자 검사
				fclose(pFile);
				return false;
			}

			BITMAPINFOHEADER infoHeader;
			if (!fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, pFile)) {
				fclose(pFile);
				return false;
			}

			if (infoHeader.biBitCount != 8 && infoHeader.biBitCount != 24) {
				fclose(pFile);
				return false;
			}

			if (m_nWidth != infoHeader.biWidth && m_nHeight != infoHeader.biHeight && m_nChannels != infoHeader.biBitCount / 8) {
				if (m_pImageData) {
					delete[] m_pImageData;
				}
				m_nChannels = infoHeader.biBitCount / 8;
				m_nHeight = infoHeader.biHeight;
				m_nWidth = infoHeader.biWidth;
				m_nWStep = (m_nWidth*m_nChannels * sizeof(T) + 3)&~3;

				m_pImageData = new T[m_nHeight*m_nWStep];
			}

			fseek(pFile, fileHeader.bfOffBits, SEEK_SET);

			int r;
			for (r = m_nHeight - 1; r >= 0; r--) {
				if (!fread(&m_pImageData[r*m_nWStep], sizeof(BYTE), m_nWStep, pFile)) {
					fclose(pFile);
					return false;
				}
			}

			fclose(pFile);
			return true;
		}
		else {
			return false;
		}
	}

	bool SaveImage(const char* filename) {
		assert(sizeof(T) == 1); // BYTE형의 경우만 가능

		if (strcmp(".BMP", &filename[strlen(filename) - 4])) {
			FILE* pFile = NULL;
			fopen_s(&pFile, filename, "wb");
			if (!pFile) {
				return false;
			}

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

			if (m_nChannels == 1) {
				for (int l = 0; l < 256; l++) {
					RGBQUAD GrayPalette = { l, l, l, 0 };
					fwrite(&GrayPalette, sizeof(RGBQUAD), 1, pFile);
				}
			}

			int r;
			for (r = m_nHeight - 1; r >= 0; r--) {
				fwrite(&m_pImageData[r*m_nWStep], sizeof(BYTE), m_nWStep, pFile);
			}

			fclose(pFile);
			return true;
		}
		else {
			return false;
		}
	}

protected:
	T*m_pImageData; //멤버 변수 형식의 템플릿 정의
				//영상의 픽셀 데이터가 저장되는 배열
	int m_nChannels; //채널 수
	int m_nHeight; //세로 픽셀 수
	int m_nWidth; //가로 픽셀 수
	int m_nWStep; //행당 데이터 원소 수

};

//타입형을 일일이 쓰면 번거로워 typedef 예약어를 이용해 클래스형 선언
typedef CMyImage<BYTE> CByteImage;
typedef CMyImage<int> CInteImage;
typedef CMyImage<float> CFloatImage;
typedef CMyImage<double> CDoubleImage;
