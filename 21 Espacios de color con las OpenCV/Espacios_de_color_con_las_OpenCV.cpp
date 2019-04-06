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
	char NombreImagen[] = "ivvi_684x684.jpg";
	Mat imRGB, imHSV; 

	//Cargamos la imagen y se comprueba que lo ha hecho correctamente
	imRGB = imread(NombreImagen);
	if (!imRGB.data) {
		cout << "Error al cargar la imagen: " << NombreImagen << endl;
		exit(1);
	}

	//Separar la imagen a 3 subimagenes ( A, V y R )
	vector<Mat> bgr_planes;
	split(imRGB, bgr_planes);
	
	cvtColor(imRGB, imHSV, CV_BGR2HSV);
	vector<Mat> hsv_planes;
	split(imHSV, hsv_planes);

	//Mostrar la imagen
	
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", imRGB);

	namedWindow("HSV", CV_WINDOW_AUTOSIZE);
	imshow("HSV", imHSV);
	
	//Esperar a pulsar una tecla
	cvWaitKey(0);
	return 0;
}
