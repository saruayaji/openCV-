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
void Practice3() {
	cv::Mat mat = cv::imread("lena.jpg");
	if (mat.empty())
	{
		cout << "�摜���������ǂݍ��܂�܂���ł���" << endl;
		return;
	}


	cv::Mat gray;
	cv::Mat RGBforHSV;
	cv::Mat HSVforRGB;


	cv::cvtColor(mat, gray, CV_BGR2GRAY);	//�O���[�X�P�[����
	cv::cvtColor(mat, RGBforHSV, CV_BGR2HSV);  //BGR �� HSV�ϊ�
											   /*�ȉ��`�����l������*/
	cv::Mat channels[3];
	cv::split(RGBforHSV, channels);
	cv::Mat mergeChannels[3];	//�`�����l�����ёւ��p��Mat�z��
	mergeChannels[0] = channels[0];	//H=H
	mergeChannels[1] = channels[1];	//S=S
									//mergeChannels[2] = channels[2];	//V=V

									/*�ȉ��`�����l��������*/
	int kernelsize = 7;	//�J�[�l���T�C�Y�͊	
	cv::Mat blurred_V;  //V�𕽊���
	cv::blur(channels[2], blurred_V, cv::Size(kernelsize, kernelsize));
	mergeChannels[2] = blurred_V;

	/*�`�����l������*/
	cv::Mat mergeImage;
	cv::merge(mergeChannels, 3, mergeImage);

	/*HSV �� BGR�ϊ�*/
	cv::cvtColor(mergeImage, HSVforRGB, CV_HSV2BGR);  //HSV �� BGR�ϊ�


	cv::imshow("original", mat);
	cv::imshow("cvtColor_for_HSV ", RGBforHSV);  //HSV�ϊ��摜
	cv::imshow("blur_V", HSVforRGB);  //������

	cv::waitKey();


}

int main()
{
	Practice3();
	return 0;
}