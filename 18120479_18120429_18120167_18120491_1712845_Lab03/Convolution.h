#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include<string>
#include <vector>
#include <opencv2/core/types_c.h>
using namespace std;
using namespace cv;

struct KernelIndex {
	int x, y;
};

class Convolution
{
	vector<float> _kernel;// lưu giá trị của ma trận kernel dùng để tích chập
	int _kernelWidth;//chiều rộng kernel
	int _kernelHeight;//chiều dài kernel
	vector<KernelIndex> _kernelIndex;// lưu chỉ số truy cập nhanh 

public:
	//trả về kernel 
	vector<float> GetKernel();
	//set kernel, chiều rộng, chiều dài kernel phải là số lẻ
	void SetKernel(vector<float> kernel, int kWidth, int kHeight);
	//set chỉ số truy cập nhanh của kernel
	vector<KernelIndex> SetKernelIndex(int kheight, int kwidth);


	/*
	Hàm tính convolution của 1 ảnh xám với kernel được xác định trước
	sourceImage: ảnh input
	destinationImage: ảnh output
	Hàm trả về
	0: nếu tính thành công
	1: nếu tính thất bại (không đọc được ảnh input,...)
	*/
	int DoConvolution(const Mat& sourceImage, Mat& destinationImage);	
	Convolution();
	~Convolution();

};





////////////////////////////////BAI CUA NHAN
//
//
//#pragma once
//
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <opencv2/core/types_c.h>
//using namespace std;
//using namespace cv;
//
//struct KernelIndex {
//	int x, y;
//};
//
//class Convolution
//{
//	vector<float> _kernel;// lưu giá trị của ma trận kernel dùng để tích chập
//	int _kernelWidth;//chiều rộng kernel
//	int _kernelHeight;//chiều dài kernel
//	vector<KernelIndex> _kernelIndex;// lưu chỉ số truy cập nhanh 
//
//public:
//	//trả về kernel 
//	vector<float> GetKernel();
//	//set kernel, chiều rộng, chiều dài kernel phải là số lẻ
//	void SetKernel(vector<float> kernel, int kWidth, int kHeight);
//	vector<int> GetKernelSize();
//	/*
//	Hàm tính convolution của 1 ảnh xám với kernel được xác định trước
//	sourceImage: ảnh input
//	destinationImage: ảnh output
//	Hàm trả về
//	0: nếu tính thành công
//	1: nếu tính thất bại (không đọc được ảnh input,...)
//	*/
//	int DoConvolution(const Mat& sourceImage, Mat& destinationImage);
//	Convolution();
//	~Convolution();
//};