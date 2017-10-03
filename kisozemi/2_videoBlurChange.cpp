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




// ���K���Q�̌�����
void blurToOrientationLoop()
{
	cv::Mat mat = cv::imread("lena.jpg");
	if (mat.empty())
	{
		cout << "�摜���������ǂݍ��܂�܂���ł���" << endl;
		return;
	}

	int one_msec = 1000;				// 1�b�̃~���b�\��
	int fps = 30;						// 1�b�Ԃ̉摜����
	int oneframetime = one_msec / fps;	// 1���̉摜��\�����鎞�ԁi�~���b�j
	int kernelsize = 2;	//�J�[�l���T�C�Y�͊
	cv::Mat  outputImage;
	int karnrlsizeflag =1;

	while (true)
	{
		if (kernelsize % 100 == 1) {
			karnrlsizeflag *= -1;
		}
		
		if (karnrlsizeflag >= 0) kernelsize++;
		else  kernelsize-- ;


		printf("%d\t%d\n", kernelsize % 100 , karnrlsizeflag);
		cv::blur(mat, outputImage, cv::Size(kernelsize, kernelsize));					// ���ω��t�B���^
		cv::imshow("Output", outputImage);
		if (cv::waitKey(oneframetime) >= 0)	// �L�[���͂���������break
			break;
	}
}

int main()
{

	blurToOrientationLoop();
	return 0;
}