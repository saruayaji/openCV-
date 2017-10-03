#include <opencv2/opencv.hpp>
#include <iostream>

#ifdef _DEBUG	//libファイルをリンク
#pragma comment(lib, "opencv_ts300d.lib")
#pragma comment(lib, "opencv_world300d.lib")
#else
#pragma comment(lib, "opencv_ts300.lib")
#pragma comment(lib, "opencv_world300.lib")
#endif

using namespace std;

//チャンネルの分割・統合
void splitAndMergeColorImage()
{
	cv::Mat image = cv::imread("sample.jpg");

	if (image.empty())
	{
		cout << "画像ファイルを読み込めませんでした．" << endl;
		return;
	}

	cv::imshow("image", image);

	cv::Mat channels[3];
	cv::split(image, channels);	//imageを3つのMatオブジェクトに分離

	cv::Mat mergeChannels[3];	//チャンネル並び替え用のMat配列
	mergeChannels[0] = channels[2];	//BlueをRedに
	mergeChannels[1] = channels[1];	//Greenはそのまま
	mergeChannels[2] = channels[0];	//RedをBlueに

	cv::Mat mergeImage;
	cv::merge(mergeChannels, 3, mergeImage);	//チャンネルを並び替えた画像を生成

	cv::imshow("mergeImage", mergeImage);

	cv::waitKey();
}

int main(int argc, char** argv)
{
	splitAndMergeColorImage();
	return 0;
}