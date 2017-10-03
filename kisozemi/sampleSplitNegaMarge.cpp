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

//チャンネルの分割
void splitColorImage()
{
	cv::Mat image = cv::imread("sample_split.jpg");
	cv::Mat negaMarge;
	if (image.empty())
	{
		cout << "画像ファイルを読み込めませんでした．" << endl;
		return;
	}

	cv::imshow("image", image);

	cv::Mat channels[3];	//3枚の画像を格納する配列
	cv::split(image, channels);	//1枚の3チャンネル画像を3枚の1チャンネル画像に分割
	cv::imshow("Blue", channels[0]);
	cv::imshow("Green", channels[1]);
	cv::imshow("Red", channels[2]);

	channels[0] = ~channels[0];//buleだけメガポジ変換
	cv::merge(channels, 3, negaMarge);	//チャンネルを並び替えた画像を生成


	cv::imshow("image", image);
	cv::imshow("negaMergeImage", negaMarge);


	cv::waitKey();
}

int main(int argc, char** argv)
{
	splitColorImage();
	return 0;
}