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

void inputKey()
{
	cv::Mat mat = cv::imread("lena.jpg");

	if (mat.empty())
	{
		cout << "画像が正しく読み込まれませんでした" << endl;
		return;
	}

	cv::imshow("original", mat);

	cout << "以下のキーを入力してください" << endl;
	cout << "b : 平均化フィルタ， g : ガウシアンフィルタ， m : メディアンフィルタ, q : 終了" << endl;

	int key = -1;
	int kernelsize = 7;
	do{
		//キーボードからの入力
		key = cv::waitKey();

		// b が押されたら
		if (key == 'b')
		{
			cv::blur(mat, mat, cv::Size(kernelsize, kernelsize));
			cv::imshow("applied", mat);
			cout << "平均化フィルタが施されました" << endl;
		}

		// g が押されたら
		else if (key == 'g')
		{
			cv::GaussianBlur(mat, mat, cv::Size(kernelsize, kernelsize), 1);
			cv::imshow("applied", mat);
			cout << "ガウシアンフィルタが施されました" << endl;
		}

		// m が押されたら
		else if (key == 'm')
		{
			cv::medianBlur(mat, mat, kernelsize);
			cv::imshow("applied", mat);
			cout << "メディアンフィルタが施されました" << endl;
		}

		// q が押されたらループ外へ
	} while (key != 'q');
}

void createMat()
{
	//コンストラクタで作成（cv::Size(幅，高さ)，型）
	cv::Mat mat_con(cv::Size(600, 400), CV_8UC3);
	cv::imshow("constructor", mat_con);
	//青で塗りつぶす
	mat_con = cv::Scalar(255, 0, 0);
	cv::imshow("constructor_Blue", mat_con);

	//create関数で作成（cv::Size(幅，高さ)，型）
	cv::Mat mat_create;
	mat_create.create(cv::Size(400, 600), CV_8UC3);
	mat_create = cv::Scalar(0, 0, 255);
	cv::imshow(".create()", mat_create);

	////引数にcv::Sizeを使わない方法（行数，列数，型）
	//cv::Mat mat_con_nosize(400, 600, CV_8UC1);
	//mat_con_nosize = cv::Scalar(255);
	//cv::imshow("constructor_nosize", mat_con_nosize);

	////引数にcv::Sizeを使わない方法（行数，列数，型）
	//cv::Mat mat_create_nosize;
	//mat_create_nosize.create(600, 400, CV_8UC1);
	//mat_create_nosize = cv::Scalar(0);
	//cv::imshow(".create()_nosize", mat_create_nosize);

	cv::waitKey();
}

void create1chImage()
{
	cv::Mat mat(500, 500, CV_8UC1);	// 500*500の1チャンネル画像

	int rows = mat.rows, cols = mat.cols;
	for (int y = 0; y < rows; y++)
	{
		uchar *p = mat.ptr(y);	// y行目の先頭画素へのポインタを取得
		for (int x = 0; x < cols; x++)
		{
			p[x] = 255;			// y行目のx列目に 255 を格納
		}
	}

	cv::imshow("GrayImage", mat);
	cv::waitKey();
}

void createColorImage()
{
	cv::Mat mat(500, 500, CV_8UC3);	//500*500の3チャンネル画像

	int rows = mat.rows, cols = mat.cols;
	cout << cols << endl;
	for (int y = 0; y < rows; y++)
	{
		uchar* p = mat.ptr(y);
		for (int x = 0; x < cols; x++)
		{
			//ポインタを使って各画素のBGR値に書き込み
			p[x * 3] = 255;		// Blue
			p[x * 3 + 1] = 0;	// Green
			p[x * 3 + 2] = 0;	// Red
		}
	}

	cv::imshow("ColorImage", mat);
	cv::waitKey();
}

void posterization_3Colors()
{
	cv::Mat mat = cv::imread("sample_fruit.jpg");
	if (mat.empty())
	{
		cout << "画像が正しく読み込まれませんでした" << endl;
		return;
	}

	cv::imshow("original", mat);

	int cols = mat.cols, rows = mat.rows;
	int channels = mat.channels();
	for (int y = 0; y < rows; y++){
		for (int x = 0; x < cols; x++){
			//座標(x, y)のピクセルへのポインタを取得
			uchar* ptr = mat.ptr(y) + channels * x;

			//R
			if (0 <= ptr[2] && ptr[2] < 85){
				ptr[2] = 42;
			}
			else if (85 <= ptr[2] && ptr[2] < 170){
				ptr[2] = 127;
			}
			else if (170 <= ptr[2] && ptr[2] < 256){
				ptr[2] = 212;
			}
			//G
			if (0 <= ptr[1] && ptr[1] < 85){
				ptr[1] = 42;
			}
			else if (85 <= ptr[1] && ptr[1] < 170){
				ptr[1] = 127;
			}
			else if (170 <= ptr[1] && ptr[1] < 256){
				ptr[1] = 212;
			}
			//B
			if (0 <= ptr[0] && ptr[0] < 85){
				ptr[0] = 42;
			}
			else if (85 <= ptr[0] && ptr[0] < 170){
				ptr[0] = 127;
			}
			else if (170 <= ptr[0] && ptr[0] < 256){
				ptr[0] = 212;
			}
		}
	}

	cv::imshow("posterization", mat);
	cv::waitKey();
}


//===============================================
//マウスイベントのお試しプログラム.
//クリックした2点を始点・終点とした
//ROIの切り出し画像を表示する.
//===============================================

// マウスでクリックした2点を基にROIを作成
cv::Point startp;		//矩形の始点
cv::Point endp;			//矩形の終点
bool roiflag = false;	//矩形切り出しフラグ
//マウスイベントで呼び出される関数
void onMouse(int event, int x, int y, int flag, void* param)
{
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:	//左ボタンが押されたら
		if (!roiflag)
		{
			cout << "始点：(" << x << " , " << y << ")" << endl;
			startp.x = x;
			startp.y = y;

			//ウィンドウ「roi」を閉じる
			cv::destroyWindow("roi");

			roiflag = true;
		}
		else
		{
			cout << "終点：(" << x << " , " << y << ")" << endl;
			endp.x = x;
			endp.y = y;

			//元画像のポインタを取得
			cv::Mat* matp = static_cast<cv::Mat*>(param);

			//ROIの生成
			if (startp.x - endp.x == 0 || startp.y - endp.y == 0)
				cout << "幅か高さが0となるROIは生成できません" << endl;
			else
			{
				cv::Mat roi(*matp, cv::Rect(startp, endp));
				cv::imshow("roi", roi);
			}
			roiflag = false;
		}
	}
}

void mouseEventTest()
{
	cv::Mat image = cv::imread("lena.jpg");
	if (image.empty())
	{
		cout << "画像が正しく読み込めませんでした" << endl;
		return;
	}

	//ウィンドウ作成
	cv::namedWindow("original");

	//マウスイベントが発生した時のコールバック関数を登録
	cv::setMouseCallback("original", onMouse, (void*)&image);	//画像をコールバック関数に渡す

	//画像の表示
	cv::imshow("original", image);

	//「q」が押されたら終了
	while (cv::waitKey() != 'q');
}

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


void practice1(){
	//webカメラ
	cv::VideoCapture cap(0); 

	if (cap.isOpened() == false)	//カメラ入力の読み込みに失敗したら終了
	{
		cout << "カメラ入力を読み込めませんでした．" << endl;
		return;
	}

	while (true){

		cv::Mat frame;
		cap >> frame;  //カメラから画像を取得
		
		if (frame.empty())
		{
			cout << "カメラ入力待機" << endl;
			continue;
		}

		cv::imshow("PC_Camera", frame);	//画像の表示

		if (cv::waitKey() == 's'){	//sキー入力でそのフレームを保存
			cv::imwrite("Cut_Frame.jpg", frame);
		}
		else if (cv::waitKey() == 'q'){
			break;
		}

	}
}
void practice2(){
	cv::Mat image = cv::imread("lena.jpg");
	//cv::Mat blur;
	if (image.empty())
	{
		cout << "画像が正しく読み込めませんでした" << endl;
		return;
	}
	cv::imshow("original", image);


	int key = -1;;
	//int n = 1;
	//int m = 1;
	int kernelsizeX = 7; //2 * n + 1;
	int kernelsizeY = 7;//2 * m + 1;


	//cmdでのコメント
	cout << "以下のキーを入力してください" << endl;
	cout << "w:縦方向のカーネルサイズ +1, s:縦方向のカーネルサイズ -1, d:横方向のカーネルサイズを +1, a:横方向のカーネルサイズを -1, q : 終了" << endl;
	cout << "カーネルサイズ　(kernelsizeX,kernelsizeY)" << endl;

	while (true)
	{
		//キーボードからの入力
		key = cv::waitKey();

	


		// w が押されたら
		if (key == 'w')
		{
		kernelsizeX = kernelsizeX+ 2;
			//cv::blur(image, blur, cv::Size(kernelsizeX, kernelsizeY));
			/*cv::imshow("filter", blur);
			cout << "カーネルサイズ　(" << kernelsizeX << "," << kernelsizeY << ")" << endl;*/
		}
		// s が押されたら
		else if (key == 's')
		{
			if (kernelsizeX != 1)kernelsizeX = kernelsizeX - 2;
			//cv::blur(image, blur, cv::Size(kernelsizeX, kernelsizeY));
			
			
		}
		// d が押されたら
		else if (key == 'd')
		{
			kernelsizeY = kernelsizeY + 2;
			/*cv::blur(image, blur, cv::Size(kernelsizeX, kernelsizeY));
			cv::imshow("filter", blur);
			cout << "カーネルサイズ　(" << kernelsizeX << "," << kernelsizeY << ")" << endl;*/
		}
		//a が押されたら
		else if (key == 'a')
		{
			if(kernelsizeY != 1 )kernelsizeY = kernelsizeY - 2;
			//cv::blur(image, blur, cv::Size(kernelsizeX, kernelsizeY));
			//cv::imshow("filter", blur);
			//cout << "カーネルサイズ　(" << kernelsizeX << "," << kernelsizeY << ")" << endl;
		}
		else if (cv::waitKey() == 'q' || cv::waitKey() == 'e'){  //Qキーで終了
			break;
		}
		cv::Mat blur;
		cv::blur(image, blur, cv::Size(kernelsizeX, kernelsizeY));
		cv::imshow("filter", blur);
		cout << "カーネルサイズ　(" << kernelsizeX << "," << kernelsizeY << ")" << endl;
	}
}

void practice3(){
	cv::Mat mat(256, 256, CV_8UC1);	 //256*256の1チャンネル画像を生成

	int rows = mat.rows;
	int cols = mat.cols;

	for (int y = 0; y < rows; y++){
		uchar * p = mat.ptr(y);
		for (int  x = 0; x < cols; x++){
			p[x] = x;
		}
	}

	cv::imshow("LeftToRight", mat);
	cv::waitKey();


}


void practice4(){
	cv::Mat mat(256, 256, CV_8UC1);	 //256*256の1チャンネル画像を生成

	int rows = mat.rows;
	int cols = mat.cols;

	for (int y = 0; y < rows; y++){
		uchar * p = mat.ptr(y);
		for (int x = 0; x < cols; x++){
			p[x] = (y+x)/2;
		}
	}

	cv::imshow("UpperLeftToRight", mat);
	cv::waitKey();


}

void practice5(){
	cv::Mat mat(256, 256, CV_8UC1);	 //256*256の1チャンネル画像を生成


	int rows = mat.rows;
	int cols = mat.cols;

	for (int y = 0; y < rows; y++){
		uchar * p = mat.ptr(y);
		for (int x = 0; x < cols; x++){
			p[x] = 255;
			if (x%5 == 0)
			{
				p[x] = 0;
			}
		}
	}

	cv::imshow("BlobImage", mat);
	cv::waitKey();



}

void practice6() {
	cv::Mat mat = cv::imread("sample_split.jpg");
	cv::imshow("ColorImage", mat);

	int cols = mat.cols, rows = mat.rows;
	cv::Mat grayscale(cols, rows, CV_8UC1);
	for (int y = 0; y < rows; y++) {
		uchar *colorp = mat.ptr(y);
		uchar *grayp = grayscale.ptr(y);
		for (int x = 0; x < cols; x++) {
			grayp[x] = (colorp[x * 3] + colorp[x * 3 + 1] + colorp[x * 3 + 2]) / 3;
		}
	}

	cv::imshow("GrayScaleImage", grayscale);
	cv::waitKey();


}

int main(int argc, char** argv)
{
	//inputKey();
	//createMat();
	//create1chImage();
	//createColorImage();
	//posterization_3Colors();
	//mouseEventTest();
	//readCamera();
	practice1();
	//practice2();
	//practice3();
	//practice4();
	//practice5();
	//practice6();
	
	return 0;
}
