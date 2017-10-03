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

// 平滑化フィルタの比較
void getBlurImageWide()
{
	cv::Mat mat = cv::imread("lena.jpg");
	if (mat.empty())
	{
		cout << "画像を正しく読み込めませんでした" << endl;
		return;
	}

	int kernelsizeHeight = 15;	//カーネルサイズは奇数hight
	int kernelsizeWidth = 1;	//カーネルサイズは奇数wid

	cv::Mat blurred;
	cv::blur(mat, blurred, cv::Size(kernelsizeWidth, kernelsizeHeight));					// 平均化フィルタ
	
	cv::imshow("original", mat);
	cv::imshow("blurWide", blurred);
	cv::waitKey();
}

int main()
{
	getBlurImageWide();

	return 0;
}