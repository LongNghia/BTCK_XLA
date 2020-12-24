#include "Convolution.h"



int Convolution::DoConvolution(const Mat& sourceImage, Mat& destinationImage) {
	//kiểm tra ảnh
	if (sourceImage.data == NULL)
		return 1;

	//tạo ma trận truy cập nhanh
	//SetKernelIndex();


	int height = sourceImage.rows, width = sourceImage.cols, nchannels = sourceImage.channels();

	// Tạo destinationImage Mat.
	if (nchannels == 1) {
		destinationImage = cv::Mat(height, width, CV_8UC1);
		//// Đi lần lượt từng pixel của ảnh nguồn.
		//for (int i = 0; i < height; i++)
		//{
		//	// Lấy địa chỉ dòng của ảnh đích, để lưu kết quả vào.
		//	uchar* data = destinationImage.ptr<uchar>(i);

		//	for (int j = 0; j < width; j++)
		//	{
		//		// Lưu tổng giá trị độ xám của vùng ảnh tương ứng với kernel
		//		int g_val = 0;

		//		// Duyệt mask, giá trị pixel đích là tích chập của mask với ảnh nguồn.
		//		for (int ii = 0; ii < _kernel.size(); ii++)
		//		{
		//			// _kernelIndex: mảng chỉ số truy cập nhanh
		//			int index_r = i - _kernelIndex[ii].x;
		//			//// Với pixel nằm ngoài biên, bỏ qua.
		//			//if (index_r < 0 || index_r > height - 1)
		//			//	//continue;
		//			//	index_r = index_r + 1;

		//			//int index_c = j - _kernelIndex[ii].y;
		//			//if (index_c < 0 || index_c > width - 1)
		//			//	//continue;
		//			//	index_c += 1;

		//			// Với pixel nằm ngoài biên, lấy giá trị lân cận
		//			if (index_r < 0)
		//				index_r = index_r + 1;
		//			else if (index_r > height - 1)
		//				index_r = index_r - 1;


		//			int index_c = j - _kernelIndex[ii].y;
		//			if (index_c < 0)
		//				index_c += 1;
		//			else if (index_c > width - 1)
		//				index_c -= 1;

		//			g_val += _kernel[ii] * sourceImage.at<uchar>(index_r, index_c);
		//		}

		//		// Gán giá trị cho matrix đích.
		//		data[j] = g_val;
		//	}
		//}



	}
	else {
		destinationImage = cv::Mat(height, width, CV_8UC3);
	}


	for (int i = 0; i < height; i++)
	{
		// Lấy địa chỉ dòng của ảnh đích, để lưu kết quả vào.
		uchar* data = destinationImage.ptr<uchar>(i);
		for (int chanIndex = 0; chanIndex < nchannels; chanIndex++)

			for (int j = 0; j < width; j++)
			{
				// Lưu tổng giá trị độ xám của vùng ảnh tương ứng với kernel
				int g_val = 0;

				// Duyệt mask, giá trị pixel đích là tích chập của mask với ảnh nguồn.
				for (int ii = 0; ii < _kernel.size(); ii++)
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

					g_val += _kernel[ii] * sourceImage.at<uchar>(index_r, index_c* nchannels + chanIndex);
				}

				// Gán giá trị cho matrix đích.

				data[j*nchannels + chanIndex] = g_val;
			}
	}

	return 0;
}


void Convolution::SetKernel(vector<float> kernel, int kWidth, int kHeight) {
	if ((int(kernel.size()) == kWidth * kHeight) & (kWidth % 2 == 1) & (kHeight % 2 == 1)) {
		this->_kernel = kernel;
		this->_kernelHeight = kHeight;
		this->_kernelWidth = kWidth;
		//tạo mảng chỉ số truy cập nhanh
		SetKernelIndex(_kernelHeight, _kernelWidth);

		//test kernel index
		for (int i = 0; i < _kernelIndex.size(); i++) {
			cout << _kernelIndex[i].x << ", " << _kernelIndex[i].y << endl;;
		}
		cout << endl;
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


vector<KernelIndex> Convolution::SetKernelIndex(int kheight, int kwidth) {
	_kernelIndex.clear();

	KernelIndex k_index;
	int dx = -kheight / 2;
	for (int x = 0; x < kheight; x++) {
		k_index.x = dx;
		int dy = -kwidth / 2;
		for (int y = 0; y < kwidth; y++) {
			k_index.y = dy;
			_kernelIndex.push_back(k_index);
			dy++;
		}
		dx++;
	}
	return _kernelIndex;
}



Convolution::Convolution() {
	_kernel = { 1 };
	_kernelHeight = 1;
	_kernelWidth = 1;
}


Convolution::~Convolution() {}





////////////////////////////////BAI CUA NHAN
//#include"Convolution.h"
//#include<string>
//vector<int> Convolution::GetKernelSize() {
//	vector<int> _size;
//	_size.push_back(_kernelHeight);
//	_size.push_back(_kernelWidth);
//	return _size;
//}
//vector<float> Convolution::GetKernel() {
//	return this->_kernel;
//}
//void Convolution::SetKernel(vector<float> kernel, int kWidth, int kHeight) {
//	if ((int(kernel.size()) == kWidth * kHeight) & (kWidth % 2 == 1) & (kHeight % 2 == 1)) {
//		this->_kernel = kernel;
//		this->_kernelHeight = kHeight;
//		this->_kernelWidth = kWidth;
//	}
//	else {
//		try {
//			throw "Invalid kernel!";
//		}
//		catch (string error) {
//			cout << error;
//		}
//		return;
//	}
//}
//float convolution(vector<float> k, vector<int> data) {
//	if (k.size() == data.size()) {
//		float sum = 0;
//		for (int i = 0; i < k.size(); i++)
//			sum = sum + k[i] * (float)data[k.size() - 1 - i];
//		//cout << sum << ",";
//		return sum;
//	}
//	else
//		return 0;
//}
//vector<int> put_into_kernel(Mat img, int x, int y, Convolution kernel, int channel) {
//	vector<int>_data;
//	vector<int>s = kernel.GetKernelSize();
//	Mat im = img;
//	Mat temp(img.rows + s[0] - 1, img.cols + s[1] - 1, CV_LOAD_IMAGE_UNCHANGED);
//	for (int _y = 0; _y < s[0] / 2; _y++) {
//		uchar* prow_copy = temp.ptr<uchar>(_y);
//		for (int _x = 0; _x < temp.cols; _x++, prow_copy += 1)
//			prow_copy[channel] = 0;
//	}
//	for (int _y = 0; _y < im.rows; _y++) {
//		uchar* prow = im.ptr<uchar>(_y);
//		uchar* prow_copy = temp.ptr<uchar>(_y + s[0] / 2);
//		for (int _x = 0; _x < s[1] / 2; _x++, prow_copy += 1)
//			prow_copy[channel] = 0;
//		for (int _x = 0; _x < im.cols; _x++, prow += im.channels(), prow_copy += 1)
//			prow_copy[channel] = prow[channel];
//		for (int _x = 0; _x < s[1] / 2; _x++, prow_copy += 1)
//			prow_copy[channel] = 0;
//	}
//	for (int _y = im.rows + s[0] / 2; _y < temp.rows; _y++) {
//		uchar* prow_copy = temp.ptr<uchar>(_y);
//		for (int _x = 0; _x < temp.cols; _x++, prow_copy += 1)
//			prow_copy[channel] = 0;;
//	}
//	for (int _y = y; _y < y + s[0]; _y++) {
//		uchar* prow_copy = temp.ptr<uchar>(_y);
//		for (int _x = 0; _x < x; _x++, prow_copy += 1);
//		for (int _x = x; _x < x + s[1]; _x++, prow_copy += 1)
//			_data.push_back(prow_copy[channel]);
//	}
//	return _data;
//}
//
//
//Convolution::Convolution() {
//	_kernel = { 1 };
//	_kernelHeight = 1;
//	_kernelWidth = 1;
//}
//Convolution::~Convolution() {}
//int Convolution::DoConvolution(const Mat& sourceImage, Mat& destinationImage) {
//	if (sourceImage.data == NULL)
//		return 1;
//	int height = sourceImage.rows, width = sourceImage.cols, nchannels = sourceImage.channels();
//	vector<float> k = this->GetKernel();
//	Mat img = sourceImage;
//	Mat img_copy = sourceImage;
//	for (int y = 0; y < height; y++)
//	{
//		uchar* prowd = destinationImage.ptr<uchar>(y);
//		for (int x = 0; x < width; x++, prowd += nchannels)
//			for (int i = 0; i < nchannels; i++) {
//				//cout << "(" << x << ", " << y << "), ";
//				vector<int>frm = put_into_kernel(img_copy, x, y, *this, i);
//				prowd[i] = (int)convolution(k, frm);
//				//cout << (int)prowd[i]<<", ";
//			}
//		//cout << endl;
//	/*int _x = 112;
//	int _y = 212;
//	put_into_kernel(img, _x, _y, *this, 1);
//	cout << height << " x " << width << endl;
//	show_cut(img, _x, _y, *this);*/
//	}
//	return 0;
//}