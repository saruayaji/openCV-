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

//����t�@�C���̕\��
void readVideo()
{
	cv::VideoCapture cap("sora.avi");	//����t�@�C���̓ǂݍ���

	if (cap.isOpened() == false)	//����t�@�C���𐳂����ǂݍ��߂���
	{
		cout << "����t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	while (true)
	{
		cv::Mat frame;
		cap >> frame;	//���悩��̉摜���擾
		frame = ~frame;
		if (frame.data == NULL)	//���悩��̉摜��S�ēǂݍ��񂾂�I��
			break;

		cv::imshow("Output", frame);

		cv::waitKey(33);	//�����̐��l��ω�������Ɓc�H
	}
}

int main(int argc, char** argv)
{
	readVideo();
	return 0;
}