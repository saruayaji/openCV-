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

//�摜�t�@�C���̕\��(�v���O�������s���Ƀt�@�C�������w��)
void readImage_cin()
{
	cout << "�摜�t�@�C��������͂��Ă��������D" << endl;
	cout << "��Fhoge.jpg" << endl;

	string name;
	cin >> name;	//�R���\�[���ւ̓��͂�name�ɑ��

	cv::Mat image;
	image = cv::imread(name);	//�摜�̓ǂݍ���

	if (image.empty())	//�摜�̓ǂݍ��݂Ɏ��s������I��
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::imshow(name, image);	//image�Ɋi�[���ꂽ�摜��\������

	cv::waitKey();
}

int main(int argc, char** argv)
{
	readImage_cin();
	return 0;
}
