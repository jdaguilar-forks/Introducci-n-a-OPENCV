

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	//Nombre de la imagen que se va a cargar
	char NombreImagen[] = "Imagen1.jpg";
	Mat imagen;
	//Cargar la imagen
	imagen = imread(NombreImagen, -1);
	if (!imagen.data){
		cout << "Error al cargar la imagen: " << NombreImagen << endl;
		exit(1);
	}
	//Variables para el histograma
	int histSize = 256;
	/// el rango del nivel del gris 0-255
	float range[] = { 0, 256 };
	const float* histRange = { range };


	//calcular el histograma
	Mat original_hist;
	calcHist(&imagen, 1, 0, Mat(), original_hist, 1, &histSize, &histRange, true, false);

    // encontrar valores minimos y maximo para el contraste
	int min, max, contraste;
    //recorremos el histograma de menor a mayor buscando el primer nivel de girs distinto de cero
    
    for(min=0; original_hist.at<float>(min)==0;++min);
    //recorremos el histograma de menor a mayor buscando el primer nivel de girs distinto de cero
    for(max=255; original_hist.at<float>(max)==0;--max);
    contraste=max-min;
    

	Mat ImagenBordes,contour_hist;

	// opcion 1 Canny
	Canny(imagen, ImagenBordes, 100, 150, 3);

	// opcion 2 Sobel
	/*
    // Generar grad_x and grad_y 
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	int c;

	Sobel(imagen, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	Sobel(imagen, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	// Total Gradiente (approximado)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, ImagenBordes);
	threshold(ImagenBordes, ImagenBordes, 80, 255, THRESH_BINARY);
    */

	//Variables para el histograma BW
	int histSize2 = 256;
	/// el rango del nivel del BW 0-255
	float range2[] = { 0, 256 };
	const float* histRange2 = { range2 };

	calcHist(&ImagenBordes, 1, 0, Mat(), contour_hist, 1, &histSize2, &histRange2, true, false);
    
    cout << "Contraste: " << contraste << endl;
    cout << "Puntos de borde: " << contour_hist.at<float>(255) << endl;

	//Mostrar la imagen
	namedWindow("Imagen original");
	imshow("Imagen original", imagen);

	namedWindow("Canny");
	imshow("Canny", ImagenBordes);

	//Esperar a que se pulse una tecla
	waitKey(0);
}

