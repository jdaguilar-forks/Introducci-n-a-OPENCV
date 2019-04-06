
#include <opencv/cv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	//Nombre de la imagen que se va a cargar
	Mat src, dst;	
	//Cargamos la imagen y se comprueba que lo ha hecho correctamente
	src = imread("LetrasI_BW.jpg", 1);
	if (!src.data) {
		cout<< "Error al cargar la imagen: " << "LetrasI.jpg" <<endl;
		exit(1);
	}
	
	erode(src, dst, Mat(), Point(-1, -1), 1);
		
	//Mostrar la imagen
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", src );

	namedWindow("Morphology", CV_WINDOW_AUTOSIZE);
	imshow("Morphology", dst);
	
	//Esperar a pulsar una tecla
	waitKey(0);	
	return 0;
}
