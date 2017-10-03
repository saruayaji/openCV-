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




// 演習問題２の穴埋め
void blurToOrientationLoop()
{
	cv::Mat mat = cv::imread("lena.jpg");
	if (mat.empty())
	{
		cout << "画像が正しく読み込まれませんでした" << endl;
		return;
	}

	int one_msec = 1000;				// 1秒のミリ秒表現
	int fps = 30;						// 1秒間の画像枚数
	int oneframetime = one_msec / fps;	// 1枚の画像を表示する時間（ミリ秒）
	int kernelsize = 2;	//カーネルサイズは奇数
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
		cv::blur(mat, outputImage, cv::Size(kernelsize, kernelsize));					// 平均化フィルタ
		cv::imshow("Output", outputImage);
		if (cv::waitKey(oneframetime) >= 0)	// キー入力があったらbreak
			break;
	}
}

int main()
{

	blurToOrientationLoop();
	return 0;
}