#include "IppConvert.h"
#include "IppGeometry.h"

int main()
{
	IppDib dib;
	IppRgbImage img;
	IppByteImage img2;
	IppByteImage img_result;
	dib.Load("lena.bmp");

	IppDibToImage(dib, img);
	img2.Convert(img);

	IppResizeCubic(img2, img_result, img2.GetWidth()*2, img2.GetHeight()*2);
	IppResizeCubic(img2, img_result, img2.GetWidth()*2, img2.GetHeight()*2);

	IppDib dib2;
	IppImageToDib(img_result, dib2);
	dib2.Save("Result.bmp");

	return 0;
}