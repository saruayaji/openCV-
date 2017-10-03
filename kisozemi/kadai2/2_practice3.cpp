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
void Practice3() {
	cv::Mat mat = cv::imread("lena.jpg");
	if (mat.empty())
	{
		cout << "画像が正しく読み込まれませんでした" << endl;
		return;
	}


	cv::Mat gray;
	cv::Mat RGBforHSV;
	cv::Mat HSVforRGB;


	cv::cvtColor(mat, gray, CV_BGR2GRAY);	//グレースケール化
	cv::cvtColor(mat, RGBforHSV, CV_BGR2HSV);  //BGR → HSV変換
											   /*以下チャンネル分割*/
	cv::Mat channels[3];
	cv::split(RGBforHSV, channels);
	cv::Mat mergeChannels[3];	//チャンネル並び替え用のMat配列
	mergeChannels[0] = channels[0];	//H=H
	mergeChannels[1] = channels[1];	//S=S
									//mergeChannels[2] = channels[2];	//V=V

									/*以下チャンネル平滑化*/
	int kernelsize = 7;	//カーネルサイズは奇数	
	cv::Mat blurred_V;  //Vを平滑化
	cv::blur(channels[2], blurred_V, cv::Size(kernelsize, kernelsize));
	mergeChannels[2] = blurred_V;

	/*チャンネル統合*/
	cv::Mat mergeImage;
	cv::merge(mergeChannels, 3, mergeImage);

	/*HSV → BGR変換*/
	cv::cvtColor(mergeImage, HSVforRGB, CV_HSV2BGR);  //HSV → BGR変換


	cv::imshow("original", mat);
	cv::imshow("cvtColor_for_HSV ", RGBforHSV);  //HSV変換画像
	cv::imshow("blur_V", HSVforRGB);  //平滑化

	cv::waitKey();


}

int main()
{
	Practice3();
	return 0;
}