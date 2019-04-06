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
	char NombreImagen[] = "IVVI.jpg";
	Mat src, dst;

	//Cargamos la imagen y se comprueba que lo ha hecho correctamente
	src = imread(NombreImagen);
	if (!src.data) {
		cout << "Error al cargar la imagen: " << NombreImagen << endl;
		exit(1);
	}
	imshow("src", src);

	//Scale
	resize(src, dst, Size(0, 0), 0.5, 0.5, INTER_LINEAR);
	imshow("scale", dst);

	//Translation
	dst = Mat::zeros(src.size(), src.type());
	src(Rect(100, 100, src.cols - 100, src.rows - 100)).copyTo(dst(cv::Rect(0, 0, src.cols - 100, src.rows - 100)));
	imshow("translate", dst);

	//Rotate
	int len = max(src.cols, src.rows);
	double angle = 60;
	Point2f pt(len / 2.0, len / 2.0);
	Mat r = getRotationMatrix2D(pt, angle, 1.0);
	warpAffine(src, dst, r, Size(len, len));
	imshow("rotate", dst);

	//Reflection
	flip(src, dst, 1);
	imshow("reflection", dst);

	//Esperar a pulsar una tecla
	cvWaitKey(0);
	return 0;
}

