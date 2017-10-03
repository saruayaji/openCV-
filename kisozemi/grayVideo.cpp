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

//動画ファイルの表示
void readVideo()
{
	cv::VideoCapture cap("sora.avi");	//動画ファイルの読み込み

	if (cap.isOpened() == false)	//動画ファイルを正しく読み込めたか
	{
		cout << "動画ファイルを読み込めませんでした．" << endl;
		return;
	}

	while (true)
	{
		cv::Mat frame;
		cap >> frame;	//動画からの画像を取得
		frame = ~frame;
		if (frame.data == NULL)	//動画からの画像を全て読み込んだら終了
			break;

		cv::imshow("Output", frame);

		cv::waitKey(33);	//引数の数値を変化させると…？
	}
}

int main(int argc, char** argv)
{
	readVideo();
	return 0;
}