// RealceDeBordes.cpp : Defines the entry point for the console application.
//


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	//Nombre de la imagen que se va a cargar
	char NombreImagen[] = "ivvi_684x684_gray.jpg";
	
	Mat imagen;
	//Cargar la imagen
	imagen = imread(NombreImagen, -1);
	if (!imagen.data){
		cout << "Error al cargar la imagen: " << NombreImagen << endl;
		exit(1);
	}

	Mat ImagenFilt(imagen.cols, imagen.rows, CV_8U);

	Mat Kernel(3, 3, CV_8S);
	
	Kernel.at<char>(0) = -1; Kernel.at<char>(1) = -1; Kernel.at<char>(2) = -1;
	Kernel.at<char>(3) = -1; Kernel.at<char>(4) = 9; Kernel.at<char>(5) = -1;
	Kernel.at<char>(6) = -1; Kernel.at<char>(7) = -1; Kernel.at<char>(8) = -1;

	filter2D(imagen, ImagenFilt, CV_8U, Kernel);
	
	//Mostrar la imagen
	namedWindow("Imagen original");
	imshow("Imagen original", imagen);
	namedWindow("Imagen con realce de bordes");
	imshow("Imagen con realce de bordes", ImagenFilt);

	//Esperar a que se pulse una tecla
	waitKey(0);
}
