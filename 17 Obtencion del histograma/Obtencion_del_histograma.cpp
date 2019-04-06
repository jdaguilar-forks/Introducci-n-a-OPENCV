
//----------------- Obtenci�n del histograma

//#include "stdafx.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main()
{
	//Nombre del fichero
	char NombreImagen[] = "ivvi_684x684.jpg";
	Mat src;
	
	//Cargamos la imagen y se comprueba que lo ha hecho correctamente
	src = cv::imread(NombreImagen);
	if (!src.data) {
		cout << "Error al cargar la imagen: " << NombreImagen << endl;
		exit(1);
	}
	
	/// Separar la imagen a 3 subimagenes ( A, V y R )
	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	//Variables para el histograma
	int histSize = 256;
	
	/// los rangos (A,V,R) 
	float range[] = { 0, 256 };
	const float* histRange = { range };
	
	bool uniform = true; 
	bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	//calcular el histograma
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	cout << "hist: " << b_hist << endl;

	// Dibujar el histograms para A, V y R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalizar el resultado a [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	cout << "hist: " << b_hist << endl;

	/// Dibujar para  cada canal
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	//Mostrar la imagen
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", src);
	namedWindow("Histograma", CV_WINDOW_AUTOSIZE);
	imshow("Histograma", histImage);

	//Esperar a pulsar una tecla
	cvWaitKey(0);
	return 0;
}

