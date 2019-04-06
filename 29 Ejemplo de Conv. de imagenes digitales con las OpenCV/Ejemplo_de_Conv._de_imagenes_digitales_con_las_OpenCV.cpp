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
	//Nombre de la imagen que se va a cargar
	char NombreImagen[] = "IMG.jpg";
	Mat src, dst;

	//Cargamos la imagen y se comprueba que lo ha hecho correctamente
	src = imread(NombreImagen);
	if (!src.data) {
		cout << "Error al cargar la imagen: " << NombreImagen << endl;
		exit(1);
	}
	
	Mat kernel;
	kernel = Mat::ones(5, 5, CV_32F) / (float)(5 * 5);
	cout << "kernel: " << kernel << endl;

	filter2D(src, dst, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
	
	namedWindow("src", CV_WINDOW_AUTOSIZE);
	imshow("src", src);
	namedWindow("dst", CV_WINDOW_AUTOSIZE);
	imshow("dst", dst);

	//Esperar a pulsar una tecla
	cvWaitKey(0);
	return 0;
}
