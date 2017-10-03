#include <opencv2/opencv.hpp>
#include <iostream>

#ifdef _DEBUG	//lib�t�@�C���������N
#pragma comment(lib, "opencv_ts300d.lib")
#pragma comment(lib, "opencv_world300d.lib")
#else
#pragma comment(lib, "opencv_ts300.lib")
#pragma comment(lib, "opencv_world300.lib")
#endif

using namespace std;

//�摜�t�@�C���̕\��
void readImage()
{
	cv::Mat image = cv::imread("sample.jpg");	//�摜�̓ǂݍ���

	if (image.empty())	//�摜���������ǂݍ��߂��̂����m�F
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::imshow("Output", image);	//�摜�̕\��

	cv::waitKey();	//���͂�����܂őҋ@
}

int main(int argc, char** argv)
{
	readImage();
	return 0;
}
