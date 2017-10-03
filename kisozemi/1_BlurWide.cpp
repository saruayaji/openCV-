#include <opencv2/opencv.hpp>
#include <iostream>
/*
#ifdef _DEBUG	//lib�t�@�C���������N
#pragma comment(lib, "opencv_ts300d.lib")
#pragma comment(lib, "opencv_world300d.lib")
#else
#pragma comment(lib, "opencv_ts300.lib")
#pragma comment(lib, "opencv_world300.lib")
#endif
*/
using namespace std;

// �������t�B���^�̔�r
void getBlurImageWide()
{
	cv::Mat mat = cv::imread("lena.jpg");
	if (mat.empty())
	{
		cout << "�摜�𐳂����ǂݍ��߂܂���ł���" << endl;
		return;
	}

	int kernelsizeHeight = 15;	//�J�[�l���T�C�Y�͊hight
	int kernelsizeWidth = 1;	//�J�[�l���T�C�Y�͊wid

	cv::Mat blurred;
	cv::blur(mat, blurred, cv::Size(kernelsizeWidth, kernelsizeHeight));					// ���ω��t�B���^
	
	cv::imshow("original", mat);
	cv::imshow("blurWide", blurred);
	cv::waitKey();
}

int main()
{
	getBlurImageWide();

	return 0;
}