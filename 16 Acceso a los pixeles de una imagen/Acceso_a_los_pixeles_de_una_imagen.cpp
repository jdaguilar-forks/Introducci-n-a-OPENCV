
//#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// --------- Dibujar un rectangulo
int main()
{
	//Nombre de la imagen que se va a cargar
	char NombreImagen[] = "ivvi_684x684_gray.jpg";
	Mat imagen;
	int i,j;

	//Cargamos la imagen y se comprueba que lo ha hecho correctamente
	imagen = cv::imread(NombreImagen);
	if (!imagen.data) {
		cout << "Error al cargar la imagen: " << NombreImagen << endl;
		exit(1);
	}
	
	for (i = imagen.rows / 4; i < 3 * imagen.rows / 4; ++i){
		for (j = imagen.cols / 4; j < 3 * imagen.cols / 4; ++j){
			
			imagen.at<Vec3b>(Point(i, j)) = Vec3b(0, 0, 0);
		}
	}
	

	//Mostrar la imagen
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", imagen);

	// Guardo el resultado
	imwrite("Resultado.jpg", imagen);

	//Esperar a pulsar una tecla
	cvWaitKey(0);
	return 0;
}

