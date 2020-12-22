
#include <string>
#include <fstream>
#include<iomanip>

#include"Convolution.h"

using namespace std;



void main() {
	Convolution c;
	c.SetKernelIndex();
	//string path = "5.png";
	string path = "building.jpg";

	Mat  sourceImage;
	Mat destImage;
	float t = 1.0 / 25;
	vector<float> kernel = {-1,0,1,-2,0,2,-1,0,1};

	c.SetKernel(kernel, 3, 3);

	sourceImage = imread(path, IMREAD_GRAYSCALE);
	
	imshow("Source Image", sourceImage);
	c.DoConvolution(sourceImage, destImage);
	imshow("Dest Image", destImage);

	waitKey(0);
}

