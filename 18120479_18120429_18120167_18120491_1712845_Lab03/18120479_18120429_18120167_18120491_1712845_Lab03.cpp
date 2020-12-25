#include <string>
#include <fstream>
#include<iomanip>

#include"Convolution.h"
#include "Blur.h"
#include "EdgeDetector.h"
using namespace std;


//help menu
void help() {
	string line;
	ifstream myfile("help.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}


//show an existing image
void showImage(Mat &img, string name = "Destination Image") {
	if (img.data) {
		imshow(name, img);
		waitKey(0);
	}
}


void main2() {
	Convolution k;

	float t = 1.0 / 9;
	vector<float> kernel = { -1,-2,-1,0,0,0,1,2,1 };
	vector<float> kernel2 = { -1,0,1,-2,0,2,-1,0,1 };


	k.SetKernel(kernel, 3, 3);


	Mat image = imread("5.png", IMREAD_COLOR);


	Mat img;
	namedWindow("Show Image");
	imshow("Show Image", image);

	Blur b;
	b.BlurImage(image, img, 3, 3, 1);




	//EdgeDetector ed;
	//ed.DetectEdge(image, img, 3, 3, 3);




	//k.DoConvolution(image, img);
	//k.SetKernel(kernel2, 3, 3);

	//k.DoConvolution(img, img2);

	//namedWindow("Dest Image");

	imshow("Dest Image", img);

	waitKey(0);
}




//<Program.exe> <Command> <InputPath> <CmdArguments>
int main(int argc, char** argv) {
	string command, path;
	int result;
	Convolution convolution;
	Blur blur;
	EdgeDetector edgeDetector;

	Mat  sourceImage;
	Mat destImage;
	Mat histMatrix, histImage;

	//làm trơn ảnh
	if (argc >= 3) {
		command = string(argv[1]);

		path = string(argv[2]);

		sourceImage = imread(path, IMREAD_ANYCOLOR);
		imshow("Source Image", sourceImage);
	}
	if (argc == 5) {
		//kích thước kernel
		int arg1 = stoi(argv[3]);
		int arg2 = stoi(argv[4]);

		if (arg1 % 2 != 1 && arg2 % 2 != 1) {
			cout << "Kich thuoc kernel la so le!\n";
			return 1;
		}

		//lọc trung bình
		if (command == "--mean") {
			cout << "hi tehr";
			result = blur.BlurImage(sourceImage, destImage, arg1, arg2, 0);
			cout << "result: " << result << endl;
			if (result==0) showImage(destImage);
		}
		//lọc trung vị
		else if (command == "--median") {
			result = blur.BlurImage(sourceImage, destImage, arg1, arg2, 1);
			if (result==0) showImage(destImage);
		}
		//lọc gaussian
		else  if (command == "--gauss") {
			result = blur.BlurImage(sourceImage, destImage, arg1, arg2, 2);
			if (result==0) showImage(destImage);
		}
		else {
			help();
		}
	}
	//phát hiện biên cạnh
	else  if (argc == 3) {

		sourceImage = imread(path, IMREAD_GRAYSCALE);

		//phương pháp sobel
		if (command == "--sobel")
		{
			result = edgeDetector.DetectEdge(sourceImage, destImage, 3, 3, 1);
			if (result==0) showImage(destImage);

		}
		//phương pháp prewitt
		else if (command == "--prewitt")
		{
			result = edgeDetector.DetectEdge(sourceImage, destImage, 3, 3, 2);
			if (result==0) showImage(destImage);

		}
		//phương pháp laplace
		else if (command == "--laplace")
		{
			result = edgeDetector.DetectEdge(sourceImage, destImage, 3, 3, 3);
			if (result==0) showImage(destImage);
		}
	}
	else {
		help();
	}
	return 0;
}

