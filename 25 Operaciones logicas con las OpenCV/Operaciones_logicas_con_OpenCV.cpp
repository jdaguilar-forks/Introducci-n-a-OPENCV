//------------------ Imagen RGB

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main()
{
	//Crear las imagenes
	Mat img1 = Mat::zeros(Size(400, 200), CV_8UC1);
	Mat img2 = Mat::zeros(Size(400, 200), CV_8UC1);

	img1(Range(0, img1.rows), Range(0, img1.cols / 2)) = 255; 
	imshow("img1", img1);

	img2(Range(100, 150), Range(150, 350)) = 255;
	imshow("img2", img2);

	Mat res;

	bitwise_and(img1, img2, res);
	imshow("AND", res);

	//Esperar a pulsar una tecla
	cvWaitKey(0);
	return 0;
}
