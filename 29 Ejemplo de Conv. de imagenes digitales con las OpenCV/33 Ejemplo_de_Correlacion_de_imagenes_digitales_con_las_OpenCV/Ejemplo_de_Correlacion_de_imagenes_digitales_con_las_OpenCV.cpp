//------------------Correlacion normalizada y búsqueda de máximos

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
	char NombreModelo[] = "MM.jpg";
	
	//Cargamos las imagenes y se comprueba que lo ha hecho correctamente
	Mat src = imread(NombreImagen);
	Mat templ = imread(NombreModelo);

	if (!src.data || !templ.data) {
		cout << "Error al cargar la imagenes" << endl;
		exit(1);
	}

	Mat dst;

	//Reservamos memoria para los diversos metodos
	int iwidth = src.cols - templ.cols + 1;
	int iheight = src.rows - templ.rows + 1;

	dst.create(iheight, iwidth, CV_32FC1);

	int match_method = CV_TM_CCOEFF_NORMED;

	//Correlacion	
	matchTemplate(src, templ, dst, match_method);
	normalize(dst, dst, 0, 1, NORM_MINMAX, -1, Mat());

	double minVal, maxMal;
	Point minLoc, maxLoc;
	Point matchLoc;

	minMaxLoc(dst, &minVal, &maxMal, &minLoc, &maxLoc, Mat());

	//cout << "Min:" << minVal << "Max: " << maxMal << endl;
	
	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}

	rectangle(src, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(255, 0, 0), 4, 8, 0);
	rectangle(dst, Point(matchLoc.x - (templ.cols / 2), matchLoc.y - (templ.rows / 2)), Point(matchLoc.x + (templ.cols / 2), matchLoc.y + (templ.rows / 2)), Scalar::all(0), 4, 8, 0);

	imshow("src", src);
	imshow("Result", dst);
	imshow("templ", templ);

	//Esperar a pulsar una tecla
	cvWaitKey(0);
	return 0;
}

