

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	//Nombre de la imagen que se va a cargar	
	Mat src, src_gray, dst;
	
	/// Load an image
	src = imread("iCab_382x256.jpg", 1);

	/// Convert the image to Gray
	cvtColor(src, src_gray, CV_RGB2GRAY);

	/// Call the function to initialize
	threshold(src_gray, dst, 50, 255, THRESH_BINARY);

	//Mostrar la imagen
	cvNamedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", src);
	cvNamedWindow("ThreShold", CV_WINDOW_AUTOSIZE);
	imshow("ThreShold", dst);

	//Esperar a pulsar una tecla
	cvWaitKey(0);
	return 0;
}
