// Filtrado.cpp: define el punto de entrada de la aplicación de consola.
//
//-----------------Filtrado

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main()
{
	//Nombre de la imagen que se va a cargar
	char NombreImagen[] = "ivvi_512x512_gray_rg.jpg";
	char NombreImagenIvvi[] = "ivvi_512x512_gray.jpg";
	Mat src, imBlr, imGus, imMed, imBil, ivvi;

	//Cargamos la imagen y se comprueba que lo ha hecho correctamente
	src = cv::imread(NombreImagen);
	ivvi = cv::imread(NombreImagenIvvi);
	if (!src.data) {
		cout << "Error al cargar la imagen: " << NombreImagen << endl;
		exit(1);
	}

	// Homogeneous blur
	blur(src, imBlr, Size(5, 5), Point(-1, -1), 4);

	// Gaussian blur
	GaussianBlur(src, imGus, Size(5, 5), 0, 0, 4);

	// Median blur
	medianBlur(src, imMed, 5);

	//bilateral filter
	bilateralFilter(src, imBil, 15, 80, 80);

	//Mostrar la imagenes
	namedWindow("Vehiculo IVVI", CV_WINDOW_AUTOSIZE);
	imshow("Vehiculo IVVI", ivvi);

	namedWindow("Original con ruido", CV_WINDOW_AUTOSIZE);
	imshow("Original con ruido", src);

	namedWindow("blur", CV_WINDOW_AUTOSIZE);
	imshow("blur", imBlr);

	namedWindow("Gaussian", CV_WINDOW_AUTOSIZE);
	imshow("Gaussian", imGus);

	namedWindow("Median", CV_WINDOW_AUTOSIZE);
	imshow("Median", imMed);

	namedWindow("bilateral", CV_WINDOW_AUTOSIZE);
	imshow("bilateral", imBil);

	//Esperar a pulsar una tecla
	cvWaitKey(0);
	return 0;
}
