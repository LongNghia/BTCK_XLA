
#include <string>
#include <fstream>
#include<iomanip>

#include"Convolution.h"
#include "Blur.h"
#include "EdgeDetector.h"
using namespace std;



void main() {
	Convolution k;

	float t = 1.0 / 9;
	vector<float> kernel = { -1,-2,-1,0,0,0,1,2,1 };
	vector<float> kernel2 = { -1,0,1,-2,0,2,-1,0,1 };


	k.SetKernel(kernel,3, 3);


	Mat image = imread("building.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	Mat img;
	namedWindow("Show Image");
	imshow("Show Image", image);
	
	//Blur b;
	//b.BlurImage(image, img, 5, 5, 1);



	


	EdgeDetector ed;
	ed.DetectEdge(image, img, 5, 5, 1);




	//k.DoConvolution(image, img);
	//k.SetKernel(kernel2, 3, 3);

	//k.DoConvolution(img, img2);

	//namedWindow("Dest Image");

	imshow("Dest Image", img);

	waitKey(0);
}

