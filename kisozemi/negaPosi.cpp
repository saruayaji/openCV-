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

//�l�K�|�W���]
void negaPosi()
{
	cv::Mat image = cv::imread("sampleMono.jpg");

	if (image.empty())
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::imshow("image", image);

	image = ~image;	//�l�K�|�W���]

	cv::imshow("invert", image);	//�l�K�|�W���]�摜�̕\��

	cv::waitKey();
}

int main(int argc, char** argv)
{
	negaPosi();
	return 0;
}