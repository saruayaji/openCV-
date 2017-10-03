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

//�`�����l���̕����E����
void splitAndMergeColorImage()
{
	cv::Mat image = cv::imread("sample.jpg");

	if (image.empty())
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::imshow("image", image);

	cv::Mat channels[3];
	cv::split(image, channels);	//image��3��Mat�I�u�W�F�N�g�ɕ���

	cv::Mat mergeChannels[3];	//�`�����l�����ёւ��p��Mat�z��
	mergeChannels[0] = channels[2];	//Blue��Red��
	mergeChannels[1] = channels[1];	//Green�͂��̂܂�
	mergeChannels[2] = channels[0];	//Red��Blue��

	cv::Mat mergeImage;
	cv::merge(mergeChannels, 3, mergeImage);	//�`�����l������ёւ����摜�𐶐�

	cv::imshow("mergeImage", mergeImage);

	cv::waitKey();
}

int main(int argc, char** argv)
{
	splitAndMergeColorImage();
	return 0;
}