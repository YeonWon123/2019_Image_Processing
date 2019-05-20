#include <iostream>
#include <opencv/highgui.h>
#include <opencv/cv.h>

int main() {

	std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
	IplImage* image = cvLoadImage("image.jpg");     // 이미지의 경로
	cvNamedWindow("OpenCV Sample", CV_WINDOW_AUTOSIZE);
	cvShowImage("OpenCV Sample", image);

	cvWaitKey(0);
	cvReleaseImage(&image);
	cvDestroyAllWindows();

	return 0;
}