
// Sobel.cpp: define el punto de entrada de la aplicación de consola.
//
//----------------Sobel


#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include<iostream>

using namespace cv;
using namespace std;
int main()
{
	//Nombre de la imagen que se va a cargar
	char NombreImagen[] = "ivvi_684x684_gray.jpg";
	Mat src, src_gray;
	Mat grad;

	/// Generar grad_x and grad_y
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	char* window_name = "Sobel Demo - Simple Edge Detector";
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	int c;

	/// Cargamos la imagen
	src = imread(NombreImagen);

	if (!src.data) {
		cout << "Error al cargar la imagen: " << NombreImagen << endl;
		exit(1);
	}

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	/// Gradiente X
	Sobel(src, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	/// Gradiente Y
	Sobel(src, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	/// Total Gradiente (approximado)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	threshold(grad, grad, 80, 255, THRESH_BINARY);

	//Mostrar la imagen
	cvNamedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", src);
	cvNamedWindow("Sobel", CV_WINDOW_AUTOSIZE);
	imshow("Sobel", grad);

	//Esperar a pulsar una tecla
	cvWaitKey(0);
	return 0;
}
