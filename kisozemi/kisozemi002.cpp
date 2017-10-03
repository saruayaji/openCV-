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
void getBlurImage()
{
	cv::Mat mat = cv::imread("lena.jpg");
	if (mat.empty())
	{
		cout << "画像を正しく読み込めませんでした" << endl;
		return;
	}

	int kernelsize = 7;	//カーネルサイズは奇数
	cv::Mat blurred, gaussian, median;
	cv::blur(mat, blurred, cv::Size(kernelsize, kernelsize));					// 平均化フィルタ
	cv::GaussianBlur(mat, gaussian, cv::Size(kernelsize, kernelsize), 2, 0);	// ガウシアンフィルタ
	cv::medianBlur(mat, median, kernelsize);									// メディアンフィルタ

	cv::imshow("original", mat);
	cv::imshow("blur", blurred);
	cv::imshow("gaussian blur", gaussian);
	cv::imshow("median blur", median);
	cv::waitKey();
}

// エッジ抽出フィルタの比較
void getEdgeImage()
{
	cv::Mat mat = cv::imread("lena.jpg");
	if (mat.empty())
	{
		cout << "画像を正しく読み込めませんでした" << endl;
		return;
	}

	cv::Mat gray;
	cv::cvtColor(mat, gray, CV_BGR2GRAY);

	cv::Mat laplacian, sobel, canny;
	cv::Laplacian(gray, laplacian, CV_8U, 3);	//ラプラシアンフィルタ
	cv::Sobel(gray, sobel, CV_8U, 1, 0);		//ソーベルフィルタ
	cv::Canny(gray, canny, 100, 200);			//キャニーフィルタ

	cv::imshow("original", mat);
	cv::imshow("laplacian", laplacian);
	cv::imshow("sobel", sobel);
	cv::imshow("canny", canny);
	cv::waitKey();
}

// 鮮鋭化
void sharpening()
{
	cv::Mat mat = cv::imread("lena.jpg");
	if (mat.empty())
	{
		cout << "画像が正しく読み込まれませんでした" << endl;
		return;
	}

	cv::Mat gray,laplacian,blur;
	cv::cvtColor(mat, gray, CV_BGR2GRAY);	//グレースケール化

	double delta = 1.0;
	while (true)
	{
		cout << "delta=" << delta << endl;

		// エッジ抽出と平滑化
		cv::Laplacian(gray, laplacian, CV_8U, 3);
		cv::blur(gray, blur, cv::Size(3,3));

		// それぞれの方法で鮮鋭化画像を生成
		cv::Mat sharpening_lap = gray - laplacian * delta;
		cv::Mat sharpening_blur = gray + (gray - blur) * delta;

		cv::imshow("usinglap", sharpening_lap);
		cv::imshow("usingblur", sharpening_blur);

		int key = cv::waitKey();	//キー入力の受付
		
		switch (key)	// 'a'もしくは'd'以外のキーが押されたら終了
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

// 膨張・収縮
void morphology()
{
	cv::Mat mat = cv::imread("sample_morphology.jpg");
	if (mat.empty())
	{
		cout << "画像の読み込みに失敗しました" << endl;
		return;
	}

	/*
		二値画像を用意するために、
		カラー画像　→　グレースケール画像　→　二値画像
		へ変換
	*/
	cv::cvtColor(mat, mat, CV_BGR2GRAY);
	cv::threshold(mat, mat, 0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);	// 二値化のおまじない
	cv::imshow("sample_morphology", mat);

	cv::Mat dilate, erode, opening, closing, blackhat, tophat;
	cv::dilate(mat, dilate, cv::Mat());							// 膨張
	cv::erode(mat, erode, cv::Mat());							// 収縮
	cv::morphologyEx(mat, opening, cv::MORPH_OPEN, cv::Mat());	// オープニング
	cv::morphologyEx(mat, closing, cv::MORPH_CLOSE, cv::Mat());	// クロージング
	cv::imshow("dilate", dilate);
	cv::imshow("erode", erode);
	cv::imshow("opening", opening);
	cv::imshow("closing", closing);

	cv::waitKey();
}

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

	while (true)
	{
		/* ここで画像処理・表示 ＋ カーネルサイズの変化 */

		if (cv::waitKey(oneframetime) >= 0)	// キー入力があったらbreak
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