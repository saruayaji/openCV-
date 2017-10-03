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

//�摜���̂���̈�𒊏o
void extractROI()
{
	cv::Mat image = cv::imread("sample.jpg");
	if (image.empty())
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::Mat roi(image, cv::Rect(200, 150, 250, 150));	//�̈�̐؂蔲��
	cv::imshow("ROI", roi);	//ROI�̕\��
	image = ~image;
	roi = ~roi;
	cv::imshow("image", image);	//�ҏW��̉摜�̕\��
	
	cv::waitKey();
}

int main(int argc, char** argv)
{
	extractROI();
	return 0;
}