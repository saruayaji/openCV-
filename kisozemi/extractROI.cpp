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

//画像内のある領域を抽出
void extractROI()
{
	cv::Mat image = cv::imread("sample.jpg");
	if (image.empty())
	{
		cout << "画像ファイルを読み込めませんでした．" << endl;
		return;
	}

	cv::Mat roi(image, cv::Rect(200, 150, 250, 150));	//領域の切り抜き
	cv::imshow("ROI", roi);	//ROIの表示
	image = ~image;
	roi = ~roi;
	cv::imshow("image", image);	//編集後の画像の表示
	
	cv::waitKey();
}

int main(int argc, char** argv)
{
	extractROI();
	return 0;
}