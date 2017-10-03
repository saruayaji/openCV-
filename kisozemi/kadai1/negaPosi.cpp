#include <opencv2/opencv.hpp>
#include <iostream>
/*
#ifdef _DEBUG	//libファイルをリンク
#pragma comment(lib, "opencv_ts300d.lib")
#pragma comment(lib, "opencv_world300d.lib")
#else
#pragma comment(lib, "opencv_ts300.lib")
#pragma comment(lib, "opencv_world300.lib")
#endif
*/
using namespace std;

//ネガポジ反転
void negaPosi()
{
	cv::Mat image = cv::imread("sampleMono.jpg");

	if (image.empty())
	{
		cout << "画像ファイルを読み込めませんでした．" << endl;
		return;
	}

	cv::imshow("image", image);

	image = ~image;	//ネガポジ反転

	cv::imshow("invert", image);	//ネガポジ反転画像の表示

	cv::waitKey();
}

int main(int argc, char** argv)
{
	negaPosi();
	return 0;
}