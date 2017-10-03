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

//�F��Ԃ̕ϊ�
void convertColorSpace()
{
	cv::Mat image = cv::imread("sample.jpg");

	if (image.empty())
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::imshow("image", image);	//���摜�̕\��

	//BGR��Gray
	cv::Mat grayimage;
	cv::cvtColor(image, grayimage, CV_BGR2GRAY);
	cv::imshow("grayimage", grayimage);

	//BGR��HSV
	cv::Mat hsvimage;
	cv::cvtColor(image, hsvimage, CV_BGR2HSV);
	cv::imshow("hsvimage", hsvimage);

	cv::waitKey();
}

int main(int argc, char** argv)
{
	convertColorSpace();
	return 0;
}