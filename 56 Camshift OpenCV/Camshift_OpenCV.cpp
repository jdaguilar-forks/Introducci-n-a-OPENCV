
#include <iostream>
#include <ctype.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

using namespace std;
using namespace cv;

Mat image;
Mat histImage(400, 512, CV_8UC3, Scalar(0, 0, 0));
bool backprojMode = false;
bool selectObject = false;
int trackObject = 0;
bool showHist = true;
Point origin;
Rect selection;
int vmin = 10, vmax = 256, smin = 30;

void onMouse(int event, int x, int y, int, void*)
{
	if (selectObject)
	{
		selection.x = MIN(x, origin.x);
		selection.y = MIN(y, origin.y);
		selection.width = std::abs(x - origin.x);
		selection.height = std::abs(y - origin.y);
		selection &= Rect(0, 0, image.cols, image.rows);
	}

	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		origin = Point(x, y);
		selection = Rect(x, y, 0, 0);
		selectObject = true;
		break;
	case CV_EVENT_LBUTTONUP:
		selectObject = false;
		if (selection.width > 0 && selection.height > 0)
			trackObject = -1;
		break;
	}
}

int main()
{
	VideoCapture cap(0);
	Rect trackWindow;
	RotatedRect trackBox;
	int hsize = 16;
	float hranges[] = { 0, 180 };
	const float* phranges = hranges;
		
	namedWindow("CamShift Demo", 1);
	setMouseCallback("CamShift Demo", onMouse, 0);
	
	Mat hsv, hue, mask, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;

	for (;;)
	{
		Mat frame;
		cap >> frame;
				
		if (frame.empty())
			break;

		frame.copyTo(image);
		cvtColor(image, hsv, CV_BGR2HSV);

		if (trackObject)
		{
			int _vmin = vmin, _vmax = vmax;

			inRange(hsv, Scalar(0, smin, MIN(_vmin, _vmax)),
				Scalar(180, 256, MAX(_vmin, _vmax)), mask);
			int ch[] = { 0, 0 };
			hue.create(hsv.size(), hsv.depth());
			mixChannels(&hsv, 1, &hue, 1, ch, 1);

			if (trackObject < 0)
			{
				Mat roi(hue, selection), maskroi(mask, selection);
				calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
				normalize(hist, hist, 0, 255, CV_MINMAX);



				trackWindow = selection;
				trackObject = 1;

				histimg = Scalar::all(0);
				int binW = histimg.cols / hsize;
				Mat buf(1, hsize, CV_8UC3);
				for (int i = 0; i < hsize; i++)
					buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180. / hsize), 255, 255);
				cvtColor(buf, buf, CV_HSV2BGR);

				for (int i = 0; i < hsize; i++)
				{
					int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows / 255);
					rectangle(histimg, Point(i*binW, histimg.rows), Point((i + 1)*binW, histimg.rows - val), 
						Scalar(buf.at<Vec3b>(i)), -1, 8);
				}


			}

			calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
			backproj &= mask;
			RotatedRect trackBox = CamShift(backproj, trackWindow, 
				TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1));

			if (backprojMode)
				cvtColor(backproj, image, CV_GRAY2BGR);
			ellipse(image, trackBox, Scalar(0, 0, 255), 3, CV_AA);


		}

		if (selectObject && selection.width > 0 && selection.height > 0)
		{
			Mat roi(image, selection);
			bitwise_not(roi, roi);
		}
			
		imshow("CamShift Demo", image);

		char c = (char)waitKey(10);
		if (c == 27)
			break;		
	}	
	return 0;
}
