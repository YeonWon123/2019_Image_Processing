#include "IppEnhance.h"

bool IppAdd(IppByteImage& img1, IppByteImage&img2, IppByteImage& img3) {
	int w = img1.GetWidth();
	int h = img1.GetHeight();
	if (w != img2.GetWidth() || h != img2.GetHeight()) {
		return false;
	}

	img3.CreateImage(w, h);
	int size = img3.GetSize();
	BYTE* p1 = img1.GetPixels();
	BYTE* p2 = img2.GetPixels();
	BYTE* p3 = img3.GetPixels();

	for (int i = 0; i < size; i++) {
		p3[i] = limit(p1[i] + p2[i]);
	}
	return true;
}

bool IppSub(IppByteImage& img1, IppByteImage&img2, IppByteImage& img3) {
	int w = img1.GetWidth();
	int h = img1.GetHeight();
	if (w != img2.GetWidth() || h != img2.GetHeight()) {
		return false;
	}

	img3.CreateImage(w, h);
	int size = img3.GetSize();
	BYTE* p1 = img1.GetPixels();
	BYTE* p2 = img2.GetPixels();
	BYTE* p3 = img3.GetPixels();

	for (int i = 0; i < size; i++) {
		p3[i] = limit(p1[i] - p2[i]);
	}
	return true;
}

//위의 뺄셈연산의 경우 입력영상의 순서가 결과에 영향을 주지만 차이연산은 순서에 상관없이 두 영상의 차이점을 그대로 나타낼 수 있는 장점이 있다.
//따라서 차이연산은 두 영상의 변화된 부분을 찾는 용도로 적합하다.
bool IppDiff(IppByteImage& img1, IppByteImage&img2, IppByteImage& img3) {
	int w = img1.GetWidth();
	int h = img1.GetHeight();
	if (w != img2.GetWidth() || h != img2.GetHeight()) {
		return false;
	}

	img3.CreateImage(w, h);
	int size = img3.GetSize();
	BYTE* p1 = img1.GetPixels();
	BYTE* p2 = img2.GetPixels();
	BYTE* p3 = img3.GetPixels();

	int diff;
	for (int i = 0; i < size; i++) {
		diff = p1[i] - p2[i];
		p3[i] = static_cast<BYTE>((diff >= 0) ? diff : -diff);
	}
	return true;
}
