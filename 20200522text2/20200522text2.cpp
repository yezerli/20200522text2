#include<iostream>
#include<opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	//----------------------��ȡ��Ƶ�ļ�--------------------------
	VideoCapture capVideo(0);
	//VideoCapture capVideo("../testImages\\vtest.avi");

	//�����Ƶ��ʧ��
	if (!capVideo.isOpened()) {
		std::cout << "Unable to open video!" << std::endl;
		return -1;
	}

	//�������㱳��ģ�͵�ͼ��
	std::vector<cv::Mat> srcMats;


	//��������
	int nBg = 200;		//������������ģ�͵�����
	float wVar = 1;		//����Ȩ��

	int cnt = 0;
	cv::Mat frame;
	cv::Mat meanMat;
	cv::Mat varMat;
	cv::Mat dstMat;

	while (true)
	{
		capVideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		//ǰ���nBg֡�����㱳��
		if (cnt < nBg) {

			srcMats.push_back(frame);

			if (cnt == 0) {
				std::cout << "reading frame " << std::endl;
			}

		}
		else if (cnt == nBg) {
			//����ģ��
			meanMat.create(frame.size(), CV_8UC1);
			varMat.create(frame.size(), CV_32FC1);
			std::cout << "calculating background models" << std::endl;
			calcGaussianBackground(srcMats, meanMat, varMat);
		}
		else {
			//�������
			dstMat.create(frame.size(), CV_8UC1);
			gaussianThreshold(frame, meanMat, varMat, wVar, dstMat);
			imshow("result", dstMat);
			imshow("frame", frame);
			waitKey(30);
		}

		cnt++;

	}

	return 0;
}
