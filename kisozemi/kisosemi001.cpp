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

//画像ファイルの表示
void readImage()
{
	cv::Mat image = cv::imread("sample.jpg");	//画像の読み込み

	if (image.empty())	//画像が正しく読み込めたのかを確認
	{
		cout << "画像ファイルを読み込めませんでした．" << endl;
		return;
	}

	cv::imshow("Output", image);	//画像の表示

	cv::waitKey();	//入力があるまで待機
}

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

		if (frame.data == NULL)	//動画からの画像を全て読み込んだら終了
			break;

		cv::imshow("Output", frame);

		cv::waitKey(33);	//引数の数値を変化させると…？
	}
}

//カメラ入力の表示
void readCamera()
{
	cv::VideoCapture cap(0);	//カメラ入力の読み込み

	if (cap.isOpened() == false)	//カメラ入力の読み込みに失敗したら終了
	{
		cout << "カメラ入力を読み込めませんでした．" << endl;
		return;
	}

	while (true)
	{
		cv::Mat frame;
		cap >> frame;	//カメラからの画像を取得

		if (frame.empty())	//画像が正しく読み込めたのかを確認
		{
			cout << "カメラ入力のために待機" << endl;
			continue;
		}

		cv::imshow("Output", frame);	//画像の表示

		if (cv::waitKey(33) >= 0)	//33ms待機後、入力があればbreak
			break;
	}
}

//画像ファイルの表示(プログラム実行時にファイル名を指定)
void readImage_cin()
{
	cout << "画像ファイル名を入力してください．" << endl;
	cout << "例：hoge.jpg" << endl;

	string name;
	cin >> name;	//コンソールへの入力をnameに代入

	cv::Mat image;
	image = cv::imread(name);	//画像の読み込み

	if (image.empty())	//画像の読み込みに失敗したら終了
	{
		cout << "画像ファイルを読み込めませんでした．" << endl;
		return;
	}

	cv::imshow(name, image);	//imageに格納された画像を表示する

	cv::waitKey();
}

//色空間の変換
void convertColorSpace()
{
	cv::Mat image = cv::imread("sample.jpg");

	if (image.empty())
	{
		cout << "画像ファイルを読み込めませんでした．" << endl;
		return;
	}

	cv::imshow("image", image);	//元画像の表示

	//BGR→Gray
	cv::Mat grayimage;
	cv::cvtColor(image, grayimage, CV_BGR2GRAY);
	cv::imshow("grayimage", grayimage);

	//BGR→HSV
	cv::Mat hsvimage;
	cv::cvtColor(image, hsvimage, CV_BGR2HSV);
	cv::imshow("hsvimage", hsvimage);

	cv::waitKey();
}

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

	cv::imshow("image", image);	//元画像の表示

	cv::waitKey();
}

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

//チャンネルの分割
void splitColorImage()
{
	cv::Mat image = cv::imread("sample_split.jpg");

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

	cv::waitKey();
}

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
	//readImage();//一個目　これ単体
	//readVideo();//二個目　これ単体
	readCamera();//3個目　これ単体
	//readImage_cin();
	//convertColorSpace();
	//extractROI();
	//negaPosi();
	//splitColorImage();
	//splitAndMergeColorImage();

	return 0;
}