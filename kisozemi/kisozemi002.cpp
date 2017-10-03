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

// �������t�B���^�̔�r
void getBlurImage()
{
	cv::Mat mat = cv::imread("lena.jpg");
	if (mat.empty())
	{
		cout << "�摜�𐳂����ǂݍ��߂܂���ł���" << endl;
		return;
	}

	int kernelsize = 7;	//�J�[�l���T�C�Y�͊
	cv::Mat blurred, gaussian, median;
	cv::blur(mat, blurred, cv::Size(kernelsize, kernelsize));					// ���ω��t�B���^
	cv::GaussianBlur(mat, gaussian, cv::Size(kernelsize, kernelsize), 2, 0);	// �K�E�V�A���t�B���^
	cv::medianBlur(mat, median, kernelsize);									// ���f�B�A���t�B���^

	cv::imshow("original", mat);
	cv::imshow("blur", blurred);
	cv::imshow("gaussian blur", gaussian);
	cv::imshow("median blur", median);
	cv::waitKey();
}

// �G�b�W���o�t�B���^�̔�r
void getEdgeImage()
{
	cv::Mat mat = cv::imread("lena.jpg");
	if (mat.empty())
	{
		cout << "�摜�𐳂����ǂݍ��߂܂���ł���" << endl;
		return;
	}

	cv::Mat gray;
	cv::cvtColor(mat, gray, CV_BGR2GRAY);

	cv::Mat laplacian, sobel, canny;
	cv::Laplacian(gray, laplacian, CV_8U, 3);	//���v���V�A���t�B���^
	cv::Sobel(gray, sobel, CV_8U, 1, 0);		//�\�[�x���t�B���^
	cv::Canny(gray, canny, 100, 200);			//�L���j�[�t�B���^

	cv::imshow("original", mat);
	cv::imshow("laplacian", laplacian);
	cv::imshow("sobel", sobel);
	cv::imshow("canny", canny);
	cv::waitKey();
}

// �N�s��
void sharpening()
{
	cv::Mat mat = cv::imread("lena.jpg");
	if (mat.empty())
	{
		cout << "�摜���������ǂݍ��܂�܂���ł���" << endl;
		return;
	}

	cv::Mat gray,laplacian,blur;
	cv::cvtColor(mat, gray, CV_BGR2GRAY);	//�O���[�X�P�[����

	double delta = 1.0;
	while (true)
	{
		cout << "delta=" << delta << endl;

		// �G�b�W���o�ƕ�����
		cv::Laplacian(gray, laplacian, CV_8U, 3);
		cv::blur(gray, blur, cv::Size(3,3));

		// ���ꂼ��̕��@�őN�s���摜�𐶐�
		cv::Mat sharpening_lap = gray - laplacian * delta;
		cv::Mat sharpening_blur = gray + (gray - blur) * delta;

		cv::imshow("usinglap", sharpening_lap);
		cv::imshow("usingblur", sharpening_blur);

		int key = cv::waitKey();	//�L�[���͂̎�t
		
		switch (key)	// 'a'��������'d'�ȊO�̃L�[�������ꂽ��I��
		{
		case 'a':
			delta -= 0.1;
			break;
		case 'd':
			delta += 0.1;
			break;
		default:
			return;
		}
	}
}

// �c���E���k
void morphology()
{
	cv::Mat mat = cv::imread("sample_morphology.jpg");
	if (mat.empty())
	{
		cout << "�摜�̓ǂݍ��݂Ɏ��s���܂���" << endl;
		return;
	}

	/*
		��l�摜��p�ӂ��邽�߂ɁA
		�J���[�摜�@���@�O���[�X�P�[���摜�@���@��l�摜
		�֕ϊ�
	*/
	cv::cvtColor(mat, mat, CV_BGR2GRAY);
	cv::threshold(mat, mat, 0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);	// ��l���̂��܂��Ȃ�
	cv::imshow("sample_morphology", mat);

	cv::Mat dilate, erode, opening, closing, blackhat, tophat;
	cv::dilate(mat, dilate, cv::Mat());							// �c��
	cv::erode(mat, erode, cv::Mat());							// ���k
	cv::morphologyEx(mat, opening, cv::MORPH_OPEN, cv::Mat());	// �I�[�v�j���O
	cv::morphologyEx(mat, closing, cv::MORPH_CLOSE, cv::Mat());	// �N���[�W���O
	cv::imshow("dilate", dilate);
	cv::imshow("erode", erode);
	cv::imshow("opening", opening);
	cv::imshow("closing", closing);

	cv::waitKey();
}

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

	while (true)
	{
		/* �����ŉ摜�����E�\�� �{ �J�[�l���T�C�Y�̕ω� */

		if (cv::waitKey(oneframetime) >= 0)	// �L�[���͂���������break
			break;
	}
}

int main()
{
	getBlurImage();
	//getEdgeImage();
	//sharpening();
	//morphology();
	//OrientationLoop();

	return 0;
}