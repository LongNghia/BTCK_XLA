#include "Convolution.h"

int Convolution::DoConvolution(const Mat& sourceImage, Mat& destinationImage) {
	int height = sourceImage.rows;
	int width = sourceImage.cols;

	// Tạo destinationImage Mat.
	destinationImage = cv::Mat(height, width, CV_8UC1);

	// Đi lần lượt từng pixel của ảnh nguồn.
	for (int i = 0; i < height; i++)
	{
		// Lấy địa chỉ dòng của ảnh đích, để lưu kết quả vào.
		uchar* data = destinationImage.ptr<uchar>(i);

		for (int j = 0; j < width; j++)
		{
			// Lưu tổng giá trị độ xám của vùng ảnh tương ứng với kernel
			int g_val = 0;

			// Duyệt mask, giá trị pixel đích là tổ hợp tuyến tính của mask với ảnh nguồn.
			for (int ii = 0; ii < _kernel.size(); ii++)
			{
				// _kernelIndex: mảng chỉ số truy cập nhanh
				int index_r = i - _kernelIndex[ii].x;
				// Với pixel nằm ngoài biên, bỏ qua.
				if (index_r < 0 || index_r > height - 1)
					continue;

				int index_c = j - _kernelIndex[ii].y;
				if (index_c < 0 || index_c > width - 1)
					continue;

				g_val += _kernel[ii] * sourceImage.at<uchar>(index_r, index_c);
			}

			// Gán giá trị cho matrix đích.
			data[j] = g_val;
		}
	}
	return 1;
}


void Convolution::SetKernel(vector<float> kernel, int kWidth, int kHeight) {
	if ((int(kernel.size()) == kWidth * kHeight) & (kWidth % 2 == 1) & (kHeight % 2 == 1)) {
		this->_kernel = kernel;
		this->_kernelHeight = kHeight;
		this->_kernelWidth = kWidth;
	}
	else {
		try {
			throw "Invalid kernel!";
		}
		catch (string error) {
			cout << error;
		}
	}
}


vector<float> Convolution::GetKernel() {
	return _kernel;
}


void Convolution::SetKernelIndex() {
	KernelIndex k_index;

	int dx = -_kernelHeight / 2;
	for (int x = 0; x < _kernelHeight; x++) {
		k_index.x = dx;
		int dy = -_kernelWidth / 2;
		for (int y = 0; y < _kernelWidth; y++) {
			k_index.y = dy;
			_kernelIndex.push_back(k_index);
			dy++;
		}
		dx++;
	}
	//for (int ii = 0; ii < _kernelHeight*_kernelWidth; ii++)
	//	cout << "(" << _kernelIndex[ii].x << "," << _kernelIndex[ii].y << ")\n";

}


Convolution::Convolution() {
	_kernel = { 1 };
	_kernelHeight = 3;
	_kernelWidth = 5;
}
Convolution::~Convolution() {}


