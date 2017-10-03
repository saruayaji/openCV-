#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
/*
#ifdef _DEBUG	//lib�t�@�C���������N
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

//�v���g�^�C�v�錾
void mozaikuPlay();
void mekakusiPlay();
void sounyuPlay();
void preparation();
void paste(cv::Mat dst, cv::Mat src, int x, int y, int width, int height);
void DrawTransPinP(cv::Mat &img_dst, const cv::Mat transImg, const cv::Mat baseImg, vector<cv::Point2f> tgtPt);

int mode;
cv::VideoCapture cap(0);

cv::Mat src;//�J�����ł�w�i�摜
cv::Mat transImg = cv::imread("snow1.png", cv::IMREAD_UNCHANGED);//�����摜
cv::Mat img_dst;//���߉摜��}�����ď�悹�����摜
cv::Mat gray;
cv::Mat smallimg;
double scale = 3.0;
//cv::Mat snow1 = cv::imread("snow1.png");
// use default camera as video source



// ���ފ�̓ǂݍ���
string cascadeName = "./haarcascade_frontalface_alt.xml"; // Haar-like
cv::CascadeClassifier cascade;



void selectMode()
{
	int key = -1;
	if (cap.isOpened() == false)	//�J�������͂̓ǂݍ��݂Ɏ��s������I��
	{
		cout << "�J�������͂�ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cout << "�ȉ��̍s�����������L�[����͂���ƎB�e���J�n����܂�" << endl;
	cout << "b : ���U�C�N�����C g : �ډB�������C m : �}������, q : �I��" << endl;

	while (true)
	{
		cv::Mat frame;
		cap >> frame;	//�J��������̉摜���擾

		if (frame.empty())	//�摜���������ǂݍ��߂��̂����m�F
		{
			cout << "�J�������͂̂��߂ɑҋ@" << endl;
			break;
		}
		cv::imshow("Output", frame);	//�摜�̕\��
		int key = cv::waitKey(1);

		if (key == 'b')
		{
			mode = Mozaiku;
			cout << "���U�C�N�����B�e���J�n���܂�" << endl;
			cout << key << endl;
			//cap.release();//�����I�ɊJ��
			cv::destroyAllWindows();// �E�B���h�E�����D
			return;
		}

		// g �������ꂽ��
		else if (key == 'g')
		{
			mode = Mekakusi;
			cout << "�ډB�������B�e���J�n���܂�" << endl;
			cout << key << endl;
			return;
		}
		// m �������ꂽ��
		else if (key == 'm')
		{
			mode = Imgsounyu;
			cout << "�}�������B�e���J�n���܂�" << endl;
			cout << key << endl;
			return;
		}
		else if (key == 'q')
		{
			mode = End;
			cout << "�I�����܂�" << endl;
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
		cout << "���ފ킪������܂���ł���" << endl;
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
			cout << "���U�C�N�v���C�^�撆" << endl;
		}


		if (mode == Mekakusi)
		{
			mekakusiPlay();
			cout << "�ډB���v���C�^�撆" << endl;
		}

		if (mode == Imgsounyu)
		{
			sounyuPlay();
			cout << "�}���v���C�^�撆" << endl;
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

	vector<cv::Rect> faces;	//�猟�o�̈���i�[����z��I�Ȃ���
	cascade.detectMultiScale(smallimg, faces);	// �����F�摜�C�o�͋�`�i���o���ꂽ����͂ށj

	for (int i = 0; i < faces.size(); i++) {	//���o������̐��������[�v
												// ���̉摜�T�C�Y�ɍ��킹�邽�߂ɁAscale��������
		int facex = faces[i].x * scale,
			facey = faces[i].y * scale,
			facew = faces[i].width * scale,
			faceh = faces[i].height * scale;
		
		// �����炭�炾�낤�ʒu��ROI�𒊏o
		cv::Rect roi(facex, facey, facew, faceh);
		cv::Mat face(src, roi);
		cv::blur(face, face, cv::Size(101, 101));

	}

}


void mekakusiPlay() {

	preparation();


	vector<cv::Rect> faces;	//�猟�o�̈���i�[����z��I�Ȃ���
	cascade.detectMultiScale(smallimg, faces);	// �����F�摜�C�o�͋�`�i���o���ꂽ����͂ށj

	// ���ʂ̕`��
	for (int i = 0; i < faces.size(); i++) {	//���o������̐��������[�v
												// ���̉摜�T�C�Y�ɍ��킹�邽�߂ɁAscale��������
		int facex = faces[i].x * scale,
			facey = faces[i].y * scale,
			facew = faces[i].width * scale,
			faceh = faces[i].height * scale;

		// �����炭�ڂ��낤�ʒu��ROI�𒊏o
		cv::Mat eye(src,
			cv::Rect(facex, facey + faceh * 0.25, facew, faceh * 0.25));
		eye = cv::Scalar(0, 0, 0);	// ���œh��Ԃ�
	}


}

void sounyuPlay() {
	preparation();


	vector<cv::Rect> faces;	//�猟�o�̈���i�[����z��I�Ȃ���
	cascade.detectMultiScale(smallimg, faces);	// �����F�摜�C�o�͋�`�i���o���ꂽ����͂ށj

												// ���ʂ̕`��
	for (int i = 0; i < faces.size(); i++) {	//���o������̐��������[�v
												// ���̉摜�T�C�Y�ɍ��킹�邽�߂ɁAscale��������
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


		//���W�w��(�w�i�摜�̒��S�ɕ\������j
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
		//cv::waitKey(0); //�L�[�{�[�h����

	

	}

}

void preparation() {

	// ������o���邽�߂̉����� �� ���Ȃ��Ă����o�͂ł���///////////////////
	cv::cvtColor(src, gray, CV_BGR2GRAY);	// equalizeHist()�̂��߂ɁA�O���[�X�P�[���摜�֕ϊ�
	cv::equalizeHist(gray, gray); 			// �q�X�g�O�����ψꉻ
	cv::resize(gray, smallimg, cv::Size(src.cols / scale, src.rows / scale));

}

// �摜���摜�ɓ\��t����֐�
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
// �A���t�@�摜���摜�ɓ\��t����֐�
void DrawTransPinP(cv::Mat &img_dst, const cv::Mat transImg, const cv::Mat baseImg, vector<cv::Point2f> tgtPt)
{
	cv::Mat img_rgb, img_aaa, img_1ma;
	vector<cv::Mat>planes_rgba, planes_rgb, planes_aaa, planes_1ma;
	int maxVal = pow(2, 8 * baseImg.elemSize1()) - 1;

	//���߉摜��RGBA, �w�i�摜��RGB�̂݋��e�B�r�b�g�[�x�������摜�̂݋��e
	if (transImg.data == NULL || baseImg.data == NULL || transImg.channels()<4 || baseImg.channels()<3 || (transImg.elemSize1() != baseImg.elemSize1()))
	{
		img_dst = cv::Mat(100, 100, CV_8UC3);
		img_dst = cv::Scalar::all(maxVal);
		return;
	}

	//�����o������W���w�肳��Ă��Ȃ��ꍇ�͔w�i�摜�̒����ɔz�u����
	if (tgtPt.size()<4)
	{
		//���W�w��(�w�i�摜�̒��S�ɕ\������j
		int ltx = (baseImg.cols - transImg.cols) / 2;
		int lty = (baseImg.rows - transImg.rows) / 2;
		int ww = transImg.cols;
		int hh = transImg.rows;

		tgtPt.push_back(cv::Point2f(ltx, lty));
		tgtPt.push_back(cv::Point2f(ltx + ww, lty));
		tgtPt.push_back(cv::Point2f(ltx + ww, lty + hh));
		tgtPt.push_back(cv::Point2f(ltx, lty + hh));
	}

	//�ό`�s����쐬
	vector<cv::Point2f>srcPt;
	srcPt.push_back(cv::Point2f(0, 0));
	srcPt.push_back(cv::Point2f(transImg.cols - 1, 0));
	srcPt.push_back(cv::Point2f(transImg.cols - 1, transImg.rows - 1));
	srcPt.push_back(cv::Point2f(0, transImg.rows - 1));
	cv::Mat mat = cv::getPerspectiveTransform(srcPt, tgtPt);

	//�o�͉摜�Ɠ������E�����̃A���t�@�t���摜���쐬
	cv::Mat alpha0(baseImg.rows, baseImg.cols, transImg.type());
	alpha0 = cv::Scalar::all(0);
	cv::warpPerspective(transImg, alpha0, mat, alpha0.size(), cv::INTER_CUBIC, cv::BORDER_TRANSPARENT);

	//�`�����l���ɕ���
	cv::split(alpha0, planes_rgba);

	//RGBA�摜��RGB�ɕϊ�   
	planes_rgb.push_back(planes_rgba[0]);
	planes_rgb.push_back(planes_rgba[1]);
	planes_rgb.push_back(planes_rgba[2]);
	merge(planes_rgb, img_rgb);

	//RGBA�摜����A���t�@�`�����l�����o   
	planes_aaa.push_back(planes_rgba[3]);
	planes_aaa.push_back(planes_rgba[3]);
	planes_aaa.push_back(planes_rgba[3]);
	merge(planes_aaa, img_aaa);

	//�w�i�p�A���t�@�`�����l��   
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
	
	//cout << "�J�������͂�ǂݍ��߂܂���ł����D" << endl;


	return 0;
}
