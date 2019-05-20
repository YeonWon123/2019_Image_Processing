#include <windows.h> // BYTE �������� ��� ���� (typedef unsigned char BYTE)
#include <assert.h>
#include <stdio.h>

// ���� ���������� int�� double���̰� ��ȯ ��� ������ BYTE���� ��, 0~255�� �Ѿ�� ��ȯ�ǹǷ�
// 0 �̸��� ��� 0, 255 �̻��� ��� 255, �� �� �ƴ� ��� �� ���� ��ȯ�ϰ� �ϴ� ��ũ���̴�.
#define CLIP(x) (x < 0) ? 0 : x > 255 ? 255 : x

// CMyImage Ŭ������ ���ø����� �����Ѵ�.
// �̴� ������ ȸ������ �÷� ����� ���� ������� ����(int��)�� �ƴ� �� �ֱ� �����Դϴ�.
// ����þ� ���͸� �̿��Ͽ� ������ ������ ������, ������ �� �ȼ��� �Ǽ� ���� �������� ������
// ���� �� �ȼ��� �Ǽ� ���� ������ �˴ϴ�.
template <typename T>
class CMyImage
{
public:
	// �⺻ ������ (�� Ŭ������ ���ø��� �̿��Ͽ� ���ǵǹǷ�, ����� ���Ǹ� ���� ����.)
	CMyImage(void)
		: m_nChannels(0), m_nHeight(0), m_nWidth(0), m_nWStep(0), m_pImageData(NULL)
	{   }

	// ������ ũ��� ä�� ���� �Ű� ������ �޾�
	// �ȼ� �������� �޸𸮱��� �Ҵ��ϴ� �������� ����
	// �� ��� ������ ���� ��(m_nWStep)��
	// ������ ���� �ȼ� ���� ä�� ��, �ȼ� ���������� ũ�� 
	// �� ���� �������� ��������.
	CMyImage(int nWidth, int nHeight, int nChannels = 1)
		: m_nChannels(nChannels)
		, m_nHeight(nHeight)
		, m_nWidth(nWidth)
		, m_nWStep(((nWidth*nChannels * sizeof(T) + 3)&~3) / sizeof(T))
	{
		m_pImageData = new T[m_nHeight*m_nWStep];
	}

	// CMyImage Ŭ������ �������� �Ҵ�Ǵ� �޸��� �����͸� ��� ������ �����Ƿ�,
	// Ŭ������ ������ ��ü�� ������ ������, �ȼ� �����͸� ������ Ŭ���� ��ü�� �����Ѵ�.
	// �� ���� ����(deep copy)�� �ؾ� �ϹǷ�, ���� �����ڸ� �������Ѵ�.
	CMyImage(const CMyImage& myImage)
	{
		// ���� ������ ���� ��� ������ ��ȣ(=)�����ڸ� �̿��Ͽ� �״�� ����
		m_nChannels = myImage.m_nChannels;
		m_nHeight = myImage.m_nHeight;
		m_nWidth = myImage.m_nWidth;
		m_nWStep = myImage.m_nWStep;
		// �ȼ� ������ �������� m_pImageData ��� ������ 
		// ���ο� �޸𸮸� �Ҵ��ϰ� ���� memcpy() �Լ��� �̿��Ͽ�
		// �� ���� �ȼ� �������� ����� �����ϴ� ��� ���
		m_pImageData = new T[m_nHeight*m_nWStep];
		// memcpy(����Ǵ� ���� ��ġ, ������ �������� ��ġ, ����Ʈ ��);
		memcpy(m_pImageData, myImage.m_pImageData, m_nHeight*m_nWStep * sizeof(T));
	}

	// ��ȯ ������ ����
	// ��ȣ(=) �����ڸ� �̿��Ͽ� ���� ������ �� ��
	// ���� ������ ����Ǳ� ���� �캯�� �º��� ������ ���Ŀ� �°� �̸� ����ȯ
	template <typename From>
	CMyImage(const CMyImage<From>& myImage)
	{
		// ----- ���� �����ڿ� ������ �κ�  ----- //
		m_nChannels = myImage.GetChannel();
		m_nHeight = myImage.GetHeight();
		m_nWidth = myImage.GetWidth();
		m_nWStep = ((m_nWidth*m_nChannels * sizeof(T) + 3)&~3) / sizeof(T);
		m_pImageData = new T[m_nHeight*m_nWStep];
		// ------------------------------------ //

		// -------- �ȼ� ������ ��ȯ�� --------- //
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

	// �⺻ �Ҹ���
	// ������ m_pImageData ��� ������ �Ҵ�� ���� ���� ��
	// �̸� delete ���� ����Ͽ� �޸𸮸� �����Ѵ�.
	~CMyImage(void)
	{
		if (m_pImageData) delete[] m_pImageData;
	}

	// ���� �����ڿ� ���� �������� ������
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

	// ��� �Լ�
	int GetChannel() const { return m_nChannels; }
	int GetHeight() const { return m_nHeight; }
	int GetWidth() const { return m_nWidth; }
	int GetWStep() const { return m_nWStep; }

	// ���� �ȼ� �������� �����͸� ��� �Լ�
	// ���ϴ� ����(��) ��ǥ r �� ����(��) ��ǥ c�� �Է¹޾Ƽ�
	// �ش� ��ġ�� �����͸� ��ȯ�Ѵ�. (������ ���� ����Ͽ� ��ȯ)
	// �� ��ġ�� �� ��ġ�� �⺻ ���� 0���� �����Ѵ�. 
	// (�������� ó�� ��ġ�� ���� �� �Ű� ������ ���� �Է����� �ʾƵ� �ǰ�..)
	T* GetPtr(int r = 0, int c = 0) const { return m_pImageData + r * m_nWStep + c; }

	// �Ҽ� �ȼ��� �����ϴ� �Լ��� inline �Լ��� ����(�ڵ��� ���̰� ª�� ����)
	// ���󿡼�, ���ο� ���� ��ġ�� x, y �׸��� ä�� ���� c�� �ش��ϴ� �ȼ��� �����ڸ� �޾ƿ��� �Լ�
	// ȸ���� ������ ä�� ���� c���� 0�̴�.
	inline T& GetAt(int x, int y, int c = 0) const
	{
		// assert ��ũ�θ� �̿��Ͽ� Ȥ�� ��ȿ���� ���� ��ġ
		// �� ������ ũ�⸦ ����� ��ġ�� �����Ϸ��� �ϴ� ���� �ƴ��� �˻��Ͽ� �ش�.
		assert(x >= 0 && x < m_nWidth && y >= 0 && y < m_nHeight);
		return m_pImageData[m_nWStep*y + m_nChannels * x + c];
	}

	// �˰��� ���� ���� �ӽ� �� �Ǵ� ������� ������ �������� ���ο� ������ �����
	// ��ü �ȼ��� ���� Ư�� ����� �ʱ�ȭ�ϴ� �Լ�
	void SetConstValue(T val)
	{
		if (val == 0)   // ���� (1) : �ʱ�ȭ�� ���� 0�� ��� memset �Լ� ���
		{
			memset(m_pImageData, 0, m_nWStep*m_nHeight * sizeof(T));
			return;
		}

		if (sizeof(T) == 1)  // ���� (2) : ������ ������ ������ BYTE���� ��� memset �Լ� ���
		{
			memset(m_pImageData, val, m_nWStep*m_nHeight);
		}
		else  // ������ ���� : �� ���� for���� �̿��Ͽ� ��� �ȼ��� �ϳ��� �湮�ϸ鼭 �ʱ�ȭ
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

	// ������ �����Ͱ� ��ȿ������ �˻��ϴ� �Լ�
	bool IsEmpty() const
	{
		return m_pImageData ? false : true;
	}

	bool LoadImage(const char* filename)
	{
		assert(sizeof(T) == 1); // BYTE���� ��츸 ����

		if (strcmp(".BMP", &filename[strlen(filename) - 4]))
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, filename, "rb"); // ���̳ʸ� �б� ���
			if (!pFile)
				return false;

			BITMAPFILEHEADER fileHeader;

			if (!fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pFile))
			{
				fclose(pFile);
				return false;
			}

			if (fileHeader.bfType != 0x4D42) // 'BM' ���� �˻�
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
		assert(sizeof(T) == 1); // BYTE���� ��츸 ����

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
	T* m_pImageData; // �ȼ� �迭 ������, ��� ���� ������ ���ø� ����

	// ��� ����
	int m_nChannels; // ä�� ��
	int m_nHeight;   // ���� �ȼ� ��
	int m_nWidth;    // ���� �ȼ� ��
	int m_nWStep;    // �� ��� ������ ���� ��

};

// �� ��� ������ ���� ����
// ������ ���� �ȼ� ���� ä�� ��, �ȼ� ���������� ũ�� �� ���� �������� ��������.
// m_nWStep = ((nWidth*nChannels*sizeof(T)+3)&~3) / sizeof(T);

typedef CMyImage <BYTE  > CByteImage;
typedef CMyImage <int   > CIntImage;
typedef CMyImage <float > CFloatImage;
typedef CMyImage <double> CDoubleImage;

