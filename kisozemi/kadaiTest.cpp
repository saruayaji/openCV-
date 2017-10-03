#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
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

#define Mozaiku 1
#define Mekakusi 2
#define Imgsounyu 3
#define End 10

//プロトタイプ宣言
void mozaikuPlay();
void mekakusiPlay();
void sounyuPlay();
void preparation();
void paste(cv::Mat dst, cv::Mat src, int x, int y, int width, int height);
void DrawTransPinP(cv::Mat &img_dst, const cv::Mat transImg, const cv::Mat baseImg, vector<cv::Point2f> tgtPt);

int mode;
cv::VideoCapture cap(0);

cv::Mat src;//カメラでる背景画像
cv::Mat transImg = cv::imread("snow1.png", cv::IMREAD_UNCHANGED);//透明画像
cv::Mat img_dst;//透過画像を挿入して上乗せした画像
cv::Mat gray;
cv::Mat smallimg;
double scale = 3.0;
//cv::Mat snow1 = cv::imread("snow1.png");
// use default camera as video source



// 分類器の読み込み
string cascadeName = "./haarcascade_frontalface_alt.xml"; // Haar-like
cv::CascadeClassifier cascade;



void selectMode()
{
	int key = -1;
	if (cap.isOpened() == false)	//カメラ入力の読み込みに失敗したら終了
	{
		cout << "カメラ入力を読み込めませんでした．" << endl;
		return;
	}

	cout << "以下の行いたい処理キーを入力すると撮影が開始されます" << endl;
	cout << "b : モザイク処理， g : 目隠し処理， m : 挿入処理, q : 終了" << endl;

	while (true)
	{
		cv::Mat frame;
		cap >> frame;	//カメラからの画像を取得

		if (frame.empty())	//画像が正しく読み込めたのかを確認
		{
			cout << "カメラ入力のために待機" << endl;
			break;
		}
		cv::imshow("Output", frame);	//画像の表示
		int key = cv::waitKey(1);

		if (key == 'b')
		{
			mode = Mozaiku;
			cout << "モザイク処理撮影を開始します" << endl;
			cout << key << endl;
			//cap.release();//明示的に開放
			cv::destroyAllWindows();// ウィンドウを閉じる．
			return;
		}

		// g が押されたら
		else if (key == 'g')
		{
			mode = Mekakusi;
			cout << "目隠し処理撮影を開始します" << endl;
			cout << key << endl;
			return;
		}
		// m が押されたら
		else if (key == 'm')
		{
			mode = Imgsounyu;
			cout << "挿入処理撮影を開始します" << endl;
			cout << key << endl;
			return;
		}
		else if (key == 'q')
		{
			mode = End;
			cout << "終了します" << endl;
			cout << key << endl;
			return;
		}
	

	}


}

int processing()
{

	// check if we succeeded
	if (!cap.isOpened()) {
		cerr << "ERROR! Unable to open camera\n";
		//return -1;
	}
	// get one frame from camera to know frame size and type
	cap >> src;
	// check if we succeeded
	if (src.empty()) {
		cerr << "ERROR! blank frame grabbed\n";
		return -1;
	}



	bool isColor = (src.type() == CV_8UC3);
	//--- INITIALIZE VIDEOWRITER
	cv::VideoWriter writer;
	int codec = CV_FOURCC('M', 'J', 'P', 'G');  // select desired codec (must be available at runtime)
	double fps = 5.0;                          // framerate of the created video stream
	string filename = "./live.avi";             // name of the output video file
	writer.open(filename, codec, fps, src.size(), isColor);
	// check if we succeeded
	if (!writer.isOpened()) {
		cerr << "Could not open the output video file for write\n";
		return -1;
	}
	//--- GRAB AND WRITE LOOP
	cout << "Writing videofile: " << filename << endl
		<< "Press any key to terminate" << endl;




	if (!cascade.load(cascadeName))
	{
		cout << "分類器が見つかりませんでした" << endl;
		return -1;
	}



	for (;;)
	{
		// check if we succeeded
		if (!cap.read(src)) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		if (mode == Mozaiku)
		{
			mozaikuPlay();
			cout << "モザイクプレイ録画中" << endl;
		}


		if (mode == Mekakusi)
		{
			mekakusiPlay();
			cout << "目隠しプレイ録画中" << endl;
		}

		if (mode == Imgsounyu)
		{
			sounyuPlay();
			cout << "挿入プレイ録画中" << endl;
		}


		// encode the frame into the videofile stream
		writer.write(src);

		// show live and wait for a key with timeout long enough to show images
		imshow("Live", src);

		if (cv::waitKey(10) >= 0)
			break;
	}
	// the videofile will be closed and released automatically in VideoWriter destructor
	return 0;
}


void mozaikuPlay() {
	preparation();

	vector<cv::Rect> faces;	//顔検出領域を格納する配列的なもの
	cascade.detectMultiScale(smallimg, faces);	// 引数：画像，出力矩形（検出された顔を囲む）

	for (int i = 0; i < faces.size(); i++) {	//検出した顔の数だけループ
												// 元の画像サイズに合わせるために、scaleをかける
		int facex = faces[i].x * scale,
			facey = faces[i].y * scale,
			facew = faces[i].width * scale,
			faceh = faces[i].height * scale;
		
		// おそらく顔だろう位置のROIを抽出
		cv::Rect roi(facex, facey, facew, faceh);
		cv::Mat face(src, roi);
		cv::blur(face, face, cv::Size(101, 101));

	}

}


void mekakusiPlay() {

	preparation();


	vector<cv::Rect> faces;	//顔検出領域を格納する配列的なもの
	cascade.detectMultiScale(smallimg, faces);	// 引数：画像，出力矩形（検出された顔を囲む）

	// 結果の描画
	for (int i = 0; i < faces.size(); i++) {	//検出した顔の数だけループ
												// 元の画像サイズに合わせるために、scaleをかける
		int facex = faces[i].x * scale,
			facey = faces[i].y * scale,
			facew = faces[i].width * scale,
			faceh = faces[i].height * scale;

		// おそらく目だろう位置のROIを抽出
		cv::Mat eye(src,
			cv::Rect(facex, facey + faceh * 0.25, facew, faceh * 0.25));
		eye = cv::Scalar(0, 0, 0);	// 黒で塗りつぶす
	}


}

void sounyuPlay() {
	preparation();


	vector<cv::Rect> faces;	//顔検出領域を格納する配列的なもの
	cascade.detectMultiScale(smallimg, faces);	// 引数：画像，出力矩形（検出された顔を囲む）

												// 結果の描画
	for (int i = 0; i < faces.size(); i++) {	//検出した顔の数だけループ
												// 元の画像サイズに合わせるために、scaleをかける
		int facex = faces[i].x * scale,
			facey = faces[i].y * scale,
			facew = faces[i].width * scale,
			faceh = faces[i].height * scale;



		if ((transImg.data == NULL) || (src.data == NULL))
		{
			printf("------------------------------\n");
			printf("image not exist\n");
			printf("------------------------------\n");
			return;
		}
		else
		{
			printf("------------------------------\n");
			printf("Press ANY key to quit\n");
			printf("------------------------------\n");
		}


		//座標指定(背景画像の中心に表示する）
		int ltx = (src.cols - transImg.cols) / 2;
		int lty = (src.rows - transImg.rows) / 2;
		int ww = transImg.cols;
		int hh = transImg.rows;
		vector<cv::Point2f>tgtPt;
		/*
		tgtPt.push_back(cv::Point2f(ltx, lty));
		tgtPt.push_back(cv::Point2f(ltx + ww, lty));
		tgtPt.push_back(cv::Point2f(ltx + ww, lty + hh));
		tgtPt.push_back(cv::Point2f(ltx, lty + hh));
		*/
		facey -= 50;
		tgtPt.push_back(cv::Point2f(facex, facey));
		tgtPt.push_back(cv::Point2f(facex + facew, facey));
		tgtPt.push_back(cv::Point2f(facex + facew, facey + faceh));
		tgtPt.push_back(cv::Point2f(facex, facey + faceh));


		DrawTransPinP(img_dst, transImg, src, tgtPt);
		src = img_dst;
		//cv::imshow(winName, img_dst);
		//cv::waitKey(0); //キーボード処理

	

	}

}

void preparation() {

	// 顔を検出するための下準備 → やらなくても検出はできる///////////////////
	cv::cvtColor(src, gray, CV_BGR2GRAY);	// equalizeHist()のために、グレースケール画像へ変換
	cv::equalizeHist(gray, gray); 			// ヒストグラム均一化
	cv::resize(gray, smallimg, cv::Size(src.cols / scale, src.rows / scale));

}

// 画像を画像に貼り付ける関数
void paste(cv::Mat dst, cv::Mat src, int x, int y, int width, int height){ 
	cv::Mat resized_img;
	cv::resize(src, resized_img, cv::Size(width, height));

	if (x >= dst.cols || y >= dst.rows) return;
	int w = (x >= 0) ? std::min(dst.cols - x, resized_img.cols) : std::min(std::max(resized_img.cols + x, 0), dst.cols);
	int h = (y >= 0) ? std::min(dst.rows - y, resized_img.rows) : std::min(std::max(resized_img.rows + y, 0), dst.rows);
	int u = (x >= 0) ? 0 : std::min(-x, resized_img.cols - 1);
	int v = (y >= 0) ? 0 : std::min(-y, resized_img.rows - 1);
	int px = std::max(x, 0);
	int py = std::max(y, 0);

	cv::Mat roi_dst = dst(cv::Rect(px, py, w, h));
	cv::Mat roi_resized = resized_img(cv::Rect(u, v, w, h));
	roi_resized.copyTo(roi_dst);
}
// アルファ画像を画像に貼り付ける関数
void DrawTransPinP(cv::Mat &img_dst, const cv::Mat transImg, const cv::Mat baseImg, vector<cv::Point2f> tgtPt)
{
	cv::Mat img_rgb, img_aaa, img_1ma;
	vector<cv::Mat>planes_rgba, planes_rgb, planes_aaa, planes_1ma;
	int maxVal = pow(2, 8 * baseImg.elemSize1()) - 1;

	//透過画像はRGBA, 背景画像はRGBのみ許容。ビット深度が同じ画像のみ許容
	if (transImg.data == NULL || baseImg.data == NULL || transImg.channels()<4 || baseImg.channels()<3 || (transImg.elemSize1() != baseImg.elemSize1()))
	{
		img_dst = cv::Mat(100, 100, CV_8UC3);
		img_dst = cv::Scalar::all(maxVal);
		return;
	}

	//書き出し先座標が指定されていない場合は背景画像の中央に配置する
	if (tgtPt.size()<4)
	{
		//座標指定(背景画像の中心に表示する）
		int ltx = (baseImg.cols - transImg.cols) / 2;
		int lty = (baseImg.rows - transImg.rows) / 2;
		int ww = transImg.cols;
		int hh = transImg.rows;

		tgtPt.push_back(cv::Point2f(ltx, lty));
		tgtPt.push_back(cv::Point2f(ltx + ww, lty));
		tgtPt.push_back(cv::Point2f(ltx + ww, lty + hh));
		tgtPt.push_back(cv::Point2f(ltx, lty + hh));
	}

	//変形行列を作成
	vector<cv::Point2f>srcPt;
	srcPt.push_back(cv::Point2f(0, 0));
	srcPt.push_back(cv::Point2f(transImg.cols - 1, 0));
	srcPt.push_back(cv::Point2f(transImg.cols - 1, transImg.rows - 1));
	srcPt.push_back(cv::Point2f(0, transImg.rows - 1));
	cv::Mat mat = cv::getPerspectiveTransform(srcPt, tgtPt);

	//出力画像と同じ幅・高さのアルファ付き画像を作成
	cv::Mat alpha0(baseImg.rows, baseImg.cols, transImg.type());
	alpha0 = cv::Scalar::all(0);
	cv::warpPerspective(transImg, alpha0, mat, alpha0.size(), cv::INTER_CUBIC, cv::BORDER_TRANSPARENT);

	//チャンネルに分解
	cv::split(alpha0, planes_rgba);

	//RGBA画像をRGBに変換   
	planes_rgb.push_back(planes_rgba[0]);
	planes_rgb.push_back(planes_rgba[1]);
	planes_rgb.push_back(planes_rgba[2]);
	merge(planes_rgb, img_rgb);

	//RGBA画像からアルファチャンネル抽出   
	planes_aaa.push_back(planes_rgba[3]);
	planes_aaa.push_back(planes_rgba[3]);
	planes_aaa.push_back(planes_rgba[3]);
	merge(planes_aaa, img_aaa);

	//背景用アルファチャンネル   
	planes_1ma.push_back(maxVal - planes_rgba[3]);
	planes_1ma.push_back(maxVal - planes_rgba[3]);
	planes_1ma.push_back(maxVal - planes_rgba[3]);
	merge(planes_1ma, img_1ma);

	img_dst = img_rgb.mul(img_aaa, 1.0 / (double)maxVal) + baseImg.mul(img_1ma, 1.0 / (double)maxVal);
}


int main(int argc, char** argv)
{

	selectMode();
	processing();
	
	//cout << "カメラ入力を読み込めませんでした．" << endl;


	return 0;
}
