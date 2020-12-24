#include"EdgeDetector.h"
#include"Convolution.h"

void printKernel(vector <float> k) {
	for (int i = 0; i < k.size(); i++) {
		cout << k[i] << ", ";
	}
	cout << endl;
}



EdgeDetector::EdgeDetector() {}
EdgeDetector::~EdgeDetector() {}
int EdgeDetector::DetectEdge(const Mat& sourceImage, Mat& destinationImage, int kWidth, int kHeight, int method) {
	if (sourceImage.data == NULL)
		return 1;

	int height = sourceImage.rows, width = sourceImage.cols, nchannels = sourceImage.channels();
	destinationImage = cv::Mat(height, width, CV_8UC1);
	vector<float>k_x, k_y, k;

	Convolution kernel_x, kernel_y, kernel;
	//Mat gradient_x = Mat(sourceImage.rows, sourceImage.cols, CV_32FC1);
	//Mat gradient_y = Mat(sourceImage.rows, sourceImage.cols, CV_32FC1);

	Mat gradient_x = Mat(height, width, CV_8UC1);
	Mat gradient_y = Mat(height, width, CV_8UC1);


	Mat laplace = Mat(sourceImage.rows, sourceImage.cols, CV_32FC1);
	Mat temp = sourceImage;
	if (method == 1) {
		//for (int y = -kHeight / 2; y < -1; y++)
		//	for (int x = 0; x < kWidth; x++)
		//		k_x.push_back(0);
		//for (int x = -kWidth / 2; x < -1; x++)
		//	k_x.push_back(0);
		//k_x.push_back(1.0 / 4);
		//k_x.push_back(0);
		//k_x.push_back(-1.0 / 4);
		//for (int x = 2; x <= kWidth / 2; x++)
		//	k_x.push_back(0);
		//for (int x = -kWidth / 2; x < -1; x++)
		//	k_x.push_back(0);
		//k_x.push_back(2.0 / 4);
		//k_x.push_back(0);
		//k_x.push_back(-2.0 / 4);
		//for (int x = 2; x <= kWidth / 2; x++)
		//	k_x.push_back(0);
		//for (int x = -kWidth / 2; x < -1; x++)
		//	k_x.push_back(0);
		//k_x.push_back(1.0 / 4);
		//k_x.push_back(0);
		//k_x.push_back(-1.0 / 4);
		//for (int x = 2; x <= kWidth / 2; x++)
		//	k_x.push_back(0);
		//for (int y = 2; y <= kHeight / 2; y++)
		//	for (int x = 0; x < kWidth; x++)
		//		k_x.push_back(0);

		//for (int y = -kHeight / 2; y < -1; y++)
		//	for (int x = 0; x < kWidth; x++)
		//		k_y.push_back(0);
		//for (int x = -kWidth / 2; x < -1; x++)
		//	k_y.push_back(0);
		//k_y.push_back(-1.0 / 4);
		//k_y.push_back(-2.0 / 4);
		//k_y.push_back(-1.0 / 4);
		//for (int x = 2; x <= kWidth / 2; x++)
		//	k_y.push_back(0);
		//for (int x = 0; x < kWidth; x++)
		//	k_y.push_back(0);
		//for (int x = -kWidth / 2; x < -1; x++)
		//	k_y.push_back(0);
		//k_y.push_back(1.0 / 4);
		//k_y.push_back(2.0 / 4);
		//k_y.push_back(1.0 / 4);
		//for (int x = 2; x <= kWidth / 2; x++)
		//	k_y.push_back(0);
		//for (int y = 2; y <= kHeight / 2; y++)
		//	for (int x = 0; x < kWidth; x++)
		//		k_y.push_back(0);
		//kernel_x.SetKernel(k_x, kWidth, kHeight);
		//kernel_y.SetKernel(k_y, kWidth, kHeight);

		k_x = {1,0,-1,2,0,-2,1,0,-1};
		k_y = { -1,-2,-1,0,0,0,-1,-2,-1 };

		kernel_x.SetKernel(k_x, kWidth, kHeight);
		kernel_y.SetKernel(k_y, kWidth, kHeight);


		//test
		printKernel(kernel_x.GetKernel());
		printKernel(kernel_y.GetKernel());

		kernel_x.DoConvolution(sourceImage, gradient_x);
		kernel_y.DoConvolution(sourceImage, gradient_y);

		for (int y = 0; y < destinationImage.rows; y++) {
			uchar* prowd = destinationImage.ptr<uchar>(y);
			uchar* prowg_x = gradient_x.ptr<uchar>(y);
			uchar* prowg_y = gradient_y.ptr<uchar>(y);

			for (int x = 0; x < destinationImage.cols; x++) {
				int val = (int)sqrt(prowg_x[x] * prowg_x[x] + prowg_y[x] * prowg_y[x]);
				if (val < 0) val = 0;
				if (val > 255) val = 255;
				prowd[x] = 255-val;
			}
		}
		//destinationImage = gradient_y;
	}
	else
		if (method == 2) {
			for (int y = -kHeight / 2; y < -1; y++)
				for (int x = 0; x < kWidth; x++)
					k_x.push_back(0);
			for (int x = -kWidth / 2; x < -1; x++)
				k_x.push_back(0);
			k_x.push_back(1.0 / 3);
			k_x.push_back(0);
			k_x.push_back(-1.0 / 3);
			for (int x = 2; x <= kWidth / 2; x++)
				k_x.push_back(0);
			for (int x = -kWidth / 2; x < -1; x++)
				k_x.push_back(0);
			k_x.push_back(1.0 / 3);
			k_x.push_back(0);
			k_x.push_back(-1.0 / 3);
			for (int x = 2; x <= kWidth / 2; x++)
				k_x.push_back(0);
			for (int x = -kWidth / 2; x < -1; x++)
				k_x.push_back(0);
			k_x.push_back(1.0 / 3);
			k_x.push_back(0);
			k_x.push_back(-1.0 / 3);
			for (int x = 2; x <= kWidth / 2; x++)
				k_x.push_back(0);
			for (int y = 2; y <= kHeight / 2; y++)
				for (int x = 0; x < kWidth; x++)
					k_x.push_back(0);

			for (int y = -kHeight / 2; y < -1; y++)
				for (int x = 0; x < kWidth; x++)
					k_y.push_back(0);
			for (int x = -kWidth / 2; x < -1; x++)
				k_y.push_back(0);
			k_y.push_back(-1.0 / 3);
			k_y.push_back(-1.0 / 3);
			k_y.push_back(-1.0 / 3);
			for (int x = 2; x <= kWidth / 2; x++)
				k_y.push_back(0);
			for (int x = 0; x < kWidth; x++)
				k_y.push_back(0);
			for (int x = -kWidth / 2; x < -1; x++)
				k_y.push_back(0);
			k_y.push_back(1.0 / 3);
			k_y.push_back(1.0 / 3);
			k_y.push_back(1.0 / 3);
			for (int x = 2; x <= kWidth / 2; x++)
				k_y.push_back(0);
			for (int y = 2; y <= kHeight / 2; y++)
				for (int x = 0; x < kWidth; x++)
					k_y.push_back(0);
			kernel_x.SetKernel(k_x, kWidth, kHeight);
			kernel_y.SetKernel(k_y, kWidth, kHeight);

			kernel_x.DoConvolution(sourceImage, gradient_x);
			kernel_y.DoConvolution(sourceImage, gradient_y);

			for (int y = 0; y < destinationImage.rows; y++) {
				uchar* prowd = destinationImage.ptr<uchar>(y);
				uchar* prowg_x = gradient_x.ptr<uchar>(y);
				uchar* prowg_y = gradient_y.ptr<uchar>(y);

				for (int x = 0; x < destinationImage.cols; x++) {
					int val = (int)sqrt(prowg_x[x] * prowg_x[x] + prowg_y[x] * prowg_y[x]);
					if (val < 0) val = 0;
					if (val > 255) val = 255;
					prowd[x] = 255 - val;
				}
			}
		}
		else
			if (method == 3) {
				for (int y = -kHeight / 2; y < -1; y++)
					for (int x = 0; x < kWidth; x++)
						k.push_back(0);
				for (int x = -kWidth / 2; x < -1; x++)
					k.push_back(0);
				k.push_back(1);
				k.push_back(1);
				k.push_back(1);
				for (int x = 2; x <= kWidth / 2; x++)
					k.push_back(0);
				for (int x = -kWidth / 2; x < -1; x++)
					k.push_back(0);
				k.push_back(1);
				k.push_back(-8);
				k.push_back(1);
				for (int x = 2; x <= kWidth / 2; x++)
					k.push_back(0);
				for (int x = -kWidth / 2; x < -1; x++)
					k.push_back(0);
				k.push_back(1);
				k.push_back(1);
				k.push_back(1);
				for (int x = 2; x <= kWidth / 2; x++)
					k.push_back(0);
				for (int y = 2; y <= kHeight / 2; y++)
					for (int x = 0; x < kWidth; x++)
						k.push_back(0);
				kernel.SetKernel(k, kWidth, kHeight);
				kernel.DoConvolution(sourceImage, laplace);
				for (int y = 0; y < destinationImage.rows; y++) {
					uchar* prowd = destinationImage.ptr<uchar>(y);
					uchar* prowl = laplace.ptr<uchar>(y);
					for (int x = 0; x < destinationImage.cols; x++, prowd++, prowl++) {
						if ((prowl[0] < 30) & (prowl[0] > -30))
							prowd[0] = 255;
						else
							prowd[0] = 0;
					}
				}
			}
}