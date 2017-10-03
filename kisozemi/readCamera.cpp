  
 include <opencv2/opencv.hpp>
#include <iostream>

#ifdef _DEBUG	//lib�t�@�C���������N
#pragma comment(lib, "opencv_ts300d.lib")
#pragma comment(lib, "opencv_world300d.lib")
#else
#pragma comment(lib, "opencv_ts300.lib")
#pragma comment(lib, "opencv_world300.lib")
#endif

using namespace std;

//�J�������͂̕\��
void readCamera()
{
	cv::VideoCapture cap(0);	//�J�������͂̓ǂݍ���

	if (cap.isOpened() == false)	//�J�������͂̓ǂݍ��݂Ɏ��s������I��
	{
		cout << "�J�������͂�ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	while (true)
	{
		cv::Mat frame;
		cap >> frame;	//�J��������̉摜���擾

		if (frame.empty())	//�摜���������ǂݍ��߂��̂����m�F
		{
			cout << "�J�������͂̂��߂ɑҋ@" << endl;
			continue;
		}

		cv::imshow("Output", frame);	//�摜�̕\��

		if (cv::waitKey(33) >= 0)	//33ms�ҋ@��A���͂������break
			break;
	}
}

int main(int argc, char** argv)
{
	readCamera();
	return 0;
}