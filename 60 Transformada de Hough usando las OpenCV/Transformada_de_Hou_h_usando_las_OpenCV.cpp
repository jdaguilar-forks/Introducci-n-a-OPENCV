
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

//*******************************************************************************************************
// Transformada de Hough
//*******************************************************************************************************

int main(int argc, char** argv)
{
	//Nombre de la imagen que se va a cargar
	char NombreImagen[] = "Universidad_512x685.jpg";

	Mat src = imread(NombreImagen, 0);
	if (src.empty())
	{
		cout << "Error al cargar la imagen : " << NombreImagen << endl;
		return -1;
	}

	Mat dst, cdst;
	Canny(src, dst, 50, 200, 3); //Detección de los bordes en la imagen
	cvtColor(dst, cdst, CV_GRAY2BGR);

	vector<Vec2f> lines; // Vector para almacenar las lineas detectadas
	
	HoughLines(dst, lines, 1, CV_PI / 180, 200, 0, 0); // Detección de las lineas en la imagen 

	for (size_t i = 0; i < lines.size(); i++) //Codigo para pintar las lineas en la imagen
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
	}

	imshow("source", src);
	resizeWindow("source", 512, 512);
	imshow("detected lines", cdst);
	resizeWindow("detected lines", 512, 512);
	waitKey();

	return 0;
}


//*******************************************************************************************************
// Transformada de Hough probabilística
//*******************************************************************************************************

/*
int main(int argc, char** argv)
{
	//Nombre de la imagen que se va a cargar
	char NombreImagen[] = "Universidad_512x685.jpg";

	Mat src = imread(NombreImagen, 0);
	if (src.empty())
	{
		cout << "Error al cargar la imagen : " << NombreImagen << endl;
		return -1;
	}

	Mat dst, cdst;
	Canny(src, dst, 50, 200, 3); //Detección de los bordes en la imagen
	cvtColor(dst, cdst, CV_GRAY2BGR);

	vector<Vec4i> lines;
	HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
	}

	imshow("source", src);
	resizeWindow("source", 512, 512);
	imshow("detected lines", cdst);
	resizeWindow("detected lines", 512, 512);

	waitKey();

	return 0;
}
*/


//*******************************************************************************************************
// Transformada de Hough para localizar circulos
//*******************************************************************************************************

/*
int main(int argc, char** argv)
{
	Mat src, src_gray;

	//Nombre de la imagen que se va a cargar
	char NombreImagen[] = "RuedaCoche_685x512.jpg";

	src = imread(NombreImagen, 1);
	if (src.empty())
	{
		cout << "Error al cargar la imagen : " << NombreImagen << endl;
		return -1;
	}

	/// Conversión de la imagen a niveles de gris
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Reducción del ruido para evitar falsas detecciones
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;

	/// Aplicación de la Transformada de Hough para localizar los circulos
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 6, 100, 75, 0, 0);

	/// Dibujoi de los circulos localizados
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// centro del circulo
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// Borde del circulo
		circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}

	/// Presentación de los resultados
	namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
	imshow("Hough Circle Transform Demo", src);

	
	waitKey(0);
	return 0;
}
*/
