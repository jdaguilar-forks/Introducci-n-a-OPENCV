//------------------Correlacion

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main()
{
	int i;
	//Nombre de la imagen que se va a cargar
	char NombreImagen[] = "corr_norm.tif";
	char NombreModelo[] = "modelo.tif";

	//Cargamos las imagenes y se comprueba que lo ha hecho correctamente
	Mat src = imread(NombreImagen);
	Mat templ = imread(NombreModelo);

	if (!src.data || !templ.data) {
		cout << "Error al cargar la imagenes" << endl;
		exit(1);
	}

	Mat ftmp[6];
	int iwidth;
	int iheight;

	//Reservamos memoria para los diversos metodos
	iwidth = src.cols - templ.cols + 1;
	iheight = src.rows - templ.rows + 1;

	for (i = 0; i < 6; ++i)
		ftmp[i].create(iheight, iwidth, CV_32SC1);

	//Correlacion	
	for (i = 0; i < 6; ++i)
	{
		matchTemplate(src, templ, ftmp[i], i);
		normalize(ftmp[i], ftmp[i], 1, 0, CV_MINMAX);
	}

	//Pantalla
	namedWindow("Modelo", CV_WINDOW_AUTOSIZE);
	imshow("Modelo", templ);

	namedWindow("Imagen", CV_WINDOW_AUTOSIZE);
	imshow("Imagen", src);

	namedWindow("SQDIFF", CV_WINDOW_AUTOSIZE);
	imshow("SQDIFF", ftmp[0]);
	
	namedWindow("SQDIFF_NORMED", CV_WINDOW_AUTOSIZE);
	imshow("SQDIFF_NORMED", ftmp[1]);
	
	namedWindow("CCORR", CV_WINDOW_AUTOSIZE);
	imshow("CCORR", ftmp[2]);
	
	namedWindow("CCORR_NORMED", CV_WINDOW_AUTOSIZE);
	imshow("CCORR_NORMED", ftmp[3]);
	
	namedWindow("CCOEFF", CV_WINDOW_AUTOSIZE);
	imshow("CCOEFF", ftmp[4]);
	
	namedWindow("CCOEFF_NORMED", CV_WINDOW_AUTOSIZE);
	imshow("CCOEFF_NORMED", ftmp[5]);
	
	
	//Esperar a pulsar una tecla
	cvWaitKey(0);
	return 0;
}

