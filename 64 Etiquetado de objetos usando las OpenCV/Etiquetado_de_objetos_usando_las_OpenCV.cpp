
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/ml/ml.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {

	Mat image = imread("Clase1.jpg");
	
	if (!image.data) {
		cout << "Error!!\n";
		return 1;
	}
	imshow("Input Image", image);
	
	//Prepare the image for findContours
	cvtColor(image, image, CV_BGR2GRAY);
	threshold(image, image, 128, 255, CV_THRESH_BINARY);

	//Find the contours
	vector<vector<Point> > contours;
	Mat contourOutput = image.clone();
	findContours(contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	//Draw the contours
	Mat contourImage(image.size(), CV_8UC3, Scalar(0, 0, 0));
	Scalar colors[3];
	colors[0] = Scalar(255, 0, 0);
	colors[1] = Scalar(0, 255, 0);
	colors[2] = Scalar(0, 0, 255);
	
	for (size_t idx = 0; idx < contours.size(); idx++)
			drawContours(contourImage, contours, idx, colors[idx % 3]);	
		
	imshow("Contours", contourImage);	
	
	waitKey(0);
	return 0;
}


