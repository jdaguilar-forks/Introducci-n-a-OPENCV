
//#include "stdafx.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//-------------  LUTs
int main()
{
	//Nombre del fichero
	char NombreImagen[] = "ivvi_684x684_gray.jpg";
	
	Mat imagen;
	Mat ImagenResultadoLUT;

	//Cargamos la imagen y se comprueba que lo ha hecho correctamente
	imagen = cv::imread(NombreImagen);
	if (!imagen.data) {
		cout << "Error al cargar la imagen: " << NombreImagen << endl;
		exit(1);
	}

	Mat lut(1,256,CV_8U);
	
	for (int i = 0; i < 256; i++){
		lut.at<uchar>(i) = 255 - i; //Función Inversa
	}
	LUT(imagen, lut, ImagenResultadoLUT);

	//Mostrar la imagen
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", imagen );

	namedWindow("ImagenResultadoLUT", CV_WINDOW_AUTOSIZE);
	imshow("ImagenResultadoLUT", ImagenResultadoLUT);
	
	//Esperar a pulsar una tecla
	cvWaitKey(0);
	return 0;
}

