#include"Blur.h"
#include"Convolution.h"
#include<math.h>
Blur::Blur() {}
Blur::~Blur() {}

//
//int median(vector<int> array) {
//	vector<int>array_copy = array;
//	sort(array_copy.begin(), array_copy.end());
//	return array_copy[array_copy.size() / 2];
//}
//
//int index(vector<int>array, int x) {
//	for (int i = 0; i < array.size(); i++)
//		if (array[i] == x)
//			return i;
//	return -1;
//}
//int median_index(vector<int>array) {
//	return index(array, median(array));
//}
int Blur::BlurImage(const Mat& sourceImage, Mat& destinationImage, int kWidth, int kHeight, int method) {
	if (sourceImage.data == NULL)
		return 1;

	Convolution k;
	int height = sourceImage.rows, width = sourceImage.cols, nchannels = sourceImage.channels();
	if (method == 0) {
		vector<float> kernel;
		for (int i = 0; i < kWidth * kHeight; i++)
			kernel.push_back(1.0 / (kWidth * kHeight));
		k.SetKernel(kernel, kWidth, kHeight);
		k.DoConvolution(sourceImage, destinationImage);
	}
	else
		if (method == 2) {
			vector<float> kernel;
			float sqr_sigma = 1;

			for (int y = -kHeight / 2; y <= kHeight / 2; y++)
				for (int x = -kWidth / 2; x <= kWidth / 2; x++)
					kernel.push_back(exp(-(x * x + y * y) / (2 * sqr_sigma)) / (2 * 3.14159265358979323846 * sqr_sigma));
			Convolution k;
			k.SetKernel(kernel, kWidth, kHeight);
			k.DoConvolution(sourceImage, destinationImage);
		}
		else
			if (method == 1) {	//median

				// lưu chỉ số truy cập nhanh 
				vector<KernelIndex> _kernelIndex = k.SetKernelIndex(kHeight, kWidth);
				
																				 
				//for (int i = 0; i < _kernelIndex.size(); i++) {
				//	cout << _kernel[i].x << ", " << _kernelIndex[i].y << endl;;
				//}

				const int dx = kWidth / 2;
				const int dy = kHeight / 2;
				Mat img = sourceImage;
				for (int i = 0; i < height; i++)
				{

					uchar* prows = img.ptr<uchar>(i);
					uchar* data = destinationImage.ptr<uchar>(i);

					for (int chanIndex = 0; chanIndex < nchannels; chanIndex++) {

						for (int j = 0; j < width; j++)
						{
							vector<int> temp;

							for (int ii = 0; ii < _kernelIndex.size(); ii++)
							{
								// _kernelIndex: mảng chỉ số truy cập nhanh
								int index_r = i - _kernelIndex[ii].x;

								// Với pixel nằm ngoài biên, lấy giá trị pixel lân cận
								if (index_r < 0)
									//index_r = index_r + 1;
									index_r = 0;

								else if (index_r > height - 1)
									//index_r = index_r - 1;
									index_r = height - 1;


								int index_c = j - _kernelIndex[ii].y;

								if (index_c < 0)
									//index_c += 1;
									index_c = 0;

								else if (index_c > width - 1)
									//index_c -= 1;
									index_c = width - 1;

								temp.push_back(sourceImage.at<uchar>(index_r, index_c* nchannels + chanIndex));
							}

							sort(temp.begin(), temp.end());
							data[j*nchannels + chanIndex] = temp[temp.size()/2];

						}
					}
				}
			}
			else
				return 1;
	return 0;
}