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

void inputKey()
{
	cv::Mat mat = cv::imread("lena.jpg");

	if (mat.empty())
	{
		cout << "�摜���������ǂݍ��܂�܂���ł���" << endl;
		return;
	}

	cv::imshow("original", mat);

	cout << "�ȉ��̃L�[����͂��Ă�������" << endl;
	cout << "b : ���ω��t�B���^�C g : �K�E�V�A���t�B���^�C m : ���f�B�A���t�B���^, q : �I��" << endl;

	int key = -1;
	int kernelsize = 7;
	do{
		//�L�[�{�[�h����̓���
		key = cv::waitKey();

		// b �������ꂽ��
		if (key == 'b')
		{
			cv::blur(mat, mat, cv::Size(kernelsize, kernelsize));
			cv::imshow("applied", mat);
			cout << "���ω��t�B���^���{����܂���" << endl;
		}

		// g �������ꂽ��
		else if (key == 'g')
		{
			cv::GaussianBlur(mat, mat, cv::Size(kernelsize, kernelsize), 1);
			cv::imshow("applied", mat);
			cout << "�K�E�V�A���t�B���^���{����܂���" << endl;
		}

		// m �������ꂽ��
		else if (key == 'm')
		{
			cv::medianBlur(mat, mat, kernelsize);
			cv::imshow("applied", mat);
			cout << "���f�B�A���t�B���^���{����܂���" << endl;
		}

		// q �������ꂽ�烋�[�v�O��
	} while (key != 'q');
}

void createMat()
{
	//�R���X�g���N�^�ō쐬�icv::Size(���C����)�C�^�j
	cv::Mat mat_con(cv::Size(600, 400), CV_8UC3);
	cv::imshow("constructor", mat_con);
	//�œh��Ԃ�
	mat_con = cv::Scalar(255, 0, 0);
	cv::imshow("constructor_Blue", mat_con);

	//create�֐��ō쐬�icv::Size(���C����)�C�^�j
	cv::Mat mat_create;
	mat_create.create(cv::Size(400, 600), CV_8UC3);
	mat_create = cv::Scalar(0, 0, 255);
	cv::imshow(".create()", mat_create);

	////������cv::Size���g��Ȃ����@�i�s���C�񐔁C�^�j
	//cv::Mat mat_con_nosize(400, 600, CV_8UC1);
	//mat_con_nosize = cv::Scalar(255);
	//cv::imshow("constructor_nosize", mat_con_nosize);

	////������cv::Size���g��Ȃ����@�i�s���C�񐔁C�^�j
	//cv::Mat mat_create_nosize;
	//mat_create_nosize.create(600, 400, CV_8UC1);
	//mat_create_nosize = cv::Scalar(0);
	//cv::imshow(".create()_nosize", mat_create_nosize);

	cv::waitKey();
}

void create1chImage()
{
	cv::Mat mat(500, 500, CV_8UC1);	// 500*500��1�`�����l���摜

	int rows = mat.rows, cols = mat.cols;
	for (int y = 0; y < rows; y++)
	{
		uchar *p = mat.ptr(y);	// y�s�ڂ̐擪��f�ւ̃|�C���^���擾
		for (int x = 0; x < cols; x++)
		{
			p[x] = 255;			// y�s�ڂ�x��ڂ� 255 ���i�[
		}
	}

	cv::imshow("GrayImage", mat);
	cv::waitKey();
}

void createColorImage()
{
	cv::Mat mat(500, 500, CV_8UC3);	//500*500��3�`�����l���摜

	int rows = mat.rows, cols = mat.cols;
	cout << cols << endl;
	for (int y = 0; y < rows; y++)
	{
		uchar* p = mat.ptr(y);
		for (int x = 0; x < cols; x++)
		{
			//�|�C���^���g���Ċe��f��BGR�l�ɏ�������
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
		cout << "�摜���������ǂݍ��܂�܂���ł���" << endl;
		return;
	}

	cv::imshow("original", mat);

	int cols = mat.cols, rows = mat.rows;
	int channels = mat.channels();
	for (int y = 0; y < rows; y++){
		for (int x = 0; x < cols; x++){
			//���W(x, y)�̃s�N�Z���ւ̃|�C���^���擾
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
//�}�E�X�C�x���g�̂������v���O����.
//�N���b�N����2�_���n�_�E�I�_�Ƃ���
//ROI�̐؂�o���摜��\������.
//===============================================

// �}�E�X�ŃN���b�N����2�_�����ROI���쐬
cv::Point startp;		//��`�̎n�_
cv::Point endp;			//��`�̏I�_
bool roiflag = false;	//��`�؂�o���t���O
//�}�E�X�C�x���g�ŌĂяo�����֐�
void onMouse(int event, int x, int y, int flag, void* param)
{
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:	//���{�^���������ꂽ��
		if (!roiflag)
		{
			cout << "�n�_�F(" << x << " , " << y << ")" << endl;
			startp.x = x;
			startp.y = y;

			//�E�B���h�E�uroi�v�����
			cv::destroyWindow("roi");

			roiflag = true;
		}
		else
		{
			cout << "�I�_�F(" << x << " , " << y << ")" << endl;
			endp.x = x;
			endp.y = y;

			//���摜�̃|�C���^���擾
			cv::Mat* matp = static_cast<cv::Mat*>(param);

			//ROI�̐���
			if (startp.x - endp.x == 0 || startp.y - endp.y == 0)
				cout << "����������0�ƂȂ�ROI�͐����ł��܂���" << endl;
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
		cout << "�摜���������ǂݍ��߂܂���ł���" << endl;
		return;
	}

	//�E�B���h�E�쐬
	cv::namedWindow("original");

	//�}�E�X�C�x���g�������������̃R�[���o�b�N�֐���o�^
	cv::setMouseCallback("original", onMouse, (void*)&image);	//�摜���R�[���o�b�N�֐��ɓn��

	//�摜�̕\��
	cv::imshow("original", image);

	//�uq�v�������ꂽ��I��
	while (cv::waitKey() != 'q');
}

void readCamera()
{
	cv::VideoCapture cap(0);	//�J�������͂̓ǂݍ���

	if (cap.isOpened() == false)	//�J�������͂̓ǂݍ��݂Ɏ��s������I��
	{
		cout << "�J�������͂�ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	while (true)
	{
		cv::Mat frame;
		cap >> frame;	//�J��������̉摜���擾

		if (frame.empty())	//�摜���������ǂݍ��߂��̂����m�F
		{
			cout << "�J�������͂̂��߂ɑҋ@" << endl;
			continue;
		}

		cv::imshow("Output", frame);	//�摜�̕\��

		if (cv::waitKey(33) >= 0)	//33ms�ҋ@��A���͂������break
			break;
	}
}


void practice1(){
	//web�J����
	cv::VideoCapture cap(0); 

	if (cap.isOpened() == false)	//�J�������͂̓ǂݍ��݂Ɏ��s������I��
	{
		cout << "�J�������͂�ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	while (true){

		cv::Mat frame;
		cap >> frame;  //�J��������摜���擾
		
		if (frame.empty())
		{
			cout << "�J�������͑ҋ@" << endl;
			continue;
		}

		cv::imshow("PC_Camera", frame);	//�摜�̕\��

		if (cv::waitKey() == 's'){	//s�L�[���͂ł��̃t���[����ۑ�
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
		cout << "�摜���������ǂݍ��߂܂���ł���" << endl;
		return;
	}
	cv::imshow("original", image);


	int key = -1;;
	//int n = 1;
	//int m = 1;
	int kernelsizeX = 7; //2 * n + 1;
	int kernelsizeY = 7;//2 * m + 1;


	//cmd�ł̃R�����g
	cout << "�ȉ��̃L�[����͂��Ă�������" << endl;
	cout << "w:�c�����̃J�[�l���T�C�Y +1, s:�c�����̃J�[�l���T�C�Y -1, d:�������̃J�[�l���T�C�Y�� +1, a:�������̃J�[�l���T�C�Y�� -1, q : �I��" << endl;
	cout << "�J�[�l���T�C�Y�@(kernelsizeX,kernelsizeY)" << endl;

	while (true)
	{
		//�L�[�{�[�h����̓���
		key = cv::waitKey();

	


		// w �������ꂽ��
		if (key == 'w')
		{
		kernelsizeX = kernelsizeX+ 2;
			//cv::blur(image, blur, cv::Size(kernelsizeX, kernelsizeY));
			/*cv::imshow("filter", blur);
			cout << "�J�[�l���T�C�Y�@(" << kernelsizeX << "," << kernelsizeY << ")" << endl;*/
		}
		// s �������ꂽ��
		else if (key == 's')
		{
			if (kernelsizeX != 1)kernelsizeX = kernelsizeX - 2;
			//cv::blur(image, blur, cv::Size(kernelsizeX, kernelsizeY));
			
			
		}
		// d �������ꂽ��
		else if (key == 'd')
		{
			kernelsizeY = kernelsizeY + 2;
			/*cv::blur(image, blur, cv::Size(kernelsizeX, kernelsizeY));
			cv::imshow("filter", blur);
			cout << "�J�[�l���T�C�Y�@(" << kernelsizeX << "," << kernelsizeY << ")" << endl;*/
		}
		//a �������ꂽ��
		else if (key == 'a')
		{
			if(kernelsizeY != 1 )kernelsizeY = kernelsizeY - 2;
			//cv::blur(image, blur, cv::Size(kernelsizeX, kernelsizeY));
			//cv::imshow("filter", blur);
			//cout << "�J�[�l���T�C�Y�@(" << kernelsizeX << "," << kernelsizeY << ")" << endl;
		}
		else if (cv::waitKey() == 'q' || cv::waitKey() == 'e'){  //Q�L�[�ŏI��
			break;
		}
		cv::Mat blur;
		cv::blur(image, blur, cv::Size(kernelsizeX, kernelsizeY));
		cv::imshow("filter", blur);
		cout << "�J�[�l���T�C�Y�@(" << kernelsizeX << "," << kernelsizeY << ")" << endl;
	}
}

void practice3(){
	cv::Mat mat(256, 256, CV_8UC1);	 //256*256��1�`�����l���摜�𐶐�

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
	cv::Mat mat(256, 256, CV_8UC1);	 //256*256��1�`�����l���摜�𐶐�

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
	cv::Mat mat(256, 256, CV_8UC1);	 //256*256��1�`�����l���摜�𐶐�


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
	//practice1();
	//practice2();
	//practice3();
	//practice4();
	//practice5();
	practice6();
	
	return 0;
}
