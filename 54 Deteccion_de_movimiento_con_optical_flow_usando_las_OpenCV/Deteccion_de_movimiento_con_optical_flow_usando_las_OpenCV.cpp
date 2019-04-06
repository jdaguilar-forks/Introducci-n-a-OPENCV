// Pyramidal_LucasKanade: Optical Flow

#include "opencv/cv.hpp"
#include <iostream>
#include <stdlib.h>

using namespace cv;
using namespace std;

#define MAX_CORNERS 500
#define ESCAPE 27

int main(int argc, char* argv[])
{

	VideoCapture capture;

	// Objects
	Mat frame;

	// keyboard pressed
	char keypressed = 0;
	bool success;

	// Load image from disk
	capture.open(0);
	// if not success, exit program
	if (!capture.isOpened()){
		cout << "error in VideoCapture: check path file" << endl;
		getchar();
		return 1;
	}

	/// Parameters for Shi-Tomasi algorithm
	vector<Point2f> cornersA, cornersB;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false; 
	double k = 0.04;
	int maxCorners = MAX_CORNERS;

	// winsize has to be 11 or 13, otherwise nothing is found
	vector<uchar> status;
	vector<float> error;
	int winsize = 11;
	int maxlvl = 5;

	// Objects
	Mat img_prev, img_next, grayA, grayB;

	success = capture.read(frame);
	// if no success exit program
	if (success == false){
		cout << "Cannot read the frame from file" << endl;
		getchar();
		return 1;
	}

	img_prev = frame.clone();

	// Windows for all the images
	namedWindow("Corners A", CV_WINDOW_AUTOSIZE);
	namedWindow("Corners B", CV_WINDOW_AUTOSIZE);

	while (keypressed != ESCAPE)
	{
		// read frame by frame in a loop
		success = capture.read(frame);
		// if no success exit program
		if (success == false){
			cout << "Cannot read the frame from file" << endl;
			return 1;
		}

		img_next = frame.clone();

		// convert to grayScale
		cvtColor(img_prev, grayA, CV_RGB2GRAY);
		cvtColor(img_next, grayB, CV_RGB2GRAY);

		/// Apply corner detection
		goodFeaturesToTrack(grayA,
			cornersA,
			maxCorners,
			qualityLevel,
			minDistance,
			Mat(),
			blockSize,
			useHarrisDetector,
			k);

		calcOpticalFlowPyrLK(grayA, grayB, cornersA, cornersB, status, error,
			Size(winsize, winsize), maxlvl);

		/// Draw corners detected
		//cout << "Number of cornersA detected: " << cornersA.size() << endl;
		//cout << "Optical Flow corners detected: " << cornersB.size() << endl;
		for (int i = 0; i < cornersA.size(); i++)
		{
			line(img_prev, cornersA[i], cornersB[i], Scalar(0, 255, 0), 2);
		}

		// Show image in the name of the window
		imshow("Corners A", img_prev);
		imshow("Corners B", img_next);

		// Function for show the image in ms.
		keypressed = waitKey(1);
		img_prev = img_next;

	}
	// Free memory
	img_prev.release();
	img_next.release();
	grayA.release();
	grayB.release();
	destroyAllWindows();
	// End of the program
	return 0;
}
