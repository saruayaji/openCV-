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

//�`�����l���̕���
void splitColorImage()
{
	cv::Mat image = cv::imread("sample_split.jpg");
	cv::Mat negaMarge;
	if (image.empty())
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::imshow("image", image);

	cv::Mat channels[3];	//3���̉摜���i�[����z��
	cv::split(image, channels);	//1����3�`�����l���摜��3����1�`�����l���摜�ɕ���
	cv::imshow("Blue", channels[0]);
	cv::imshow("Green", channels[1]);
	cv::imshow("Red", channels[2]);

	channels[0] = ~channels[0];//bule�������K�|�W�ϊ�
	cv::merge(channels, 3, negaMarge);	//�`�����l������ёւ����摜�𐶐�


	cv::imshow("image", image);
	cv::imshow("negaMergeImage", negaMarge);


	cv::waitKey();
}

int main(int argc, char** argv)
{
	splitColorImage();
	return 0;
}