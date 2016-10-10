// opencv-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main()
{
	Mat im = imread("C:/Users/Delanium/Documents/Seoul/Digital Image Processing/Project #1/circle.jpg");
	if (im.empty())
	{
		cout << "Cannot load image!" << endl;
		return -1;
	}

	cout << "Width : " << im.size().width << endl;
	cout << "Height: " << im.size().height << endl;

	// Clear the image
	for (int y = 0; y < im.size().height; y++) {
		for (int x = 0; x < im.size().width; x++) {
			if (im.at<cv::Vec3b>(y, x)[0] < 100 && im.at<cv::Vec3b>(y, x)[1] < 100 && im.at<cv::Vec3b>(y, x)[2] < 100) {
				im.at<cv::Vec3b>(y, x)[0] = 0;
				im.at<cv::Vec3b>(y, x)[1] = 0;
				im.at<cv::Vec3b>(y, x)[2] = 0;
			}
		}
	}

	for (int y = 0; y < im.size().height; y++) {
		for (int x = 0; x < im.size().width; x++) {
			if (im.at<cv::Vec3b>(y, x)[0] == 0 && im.at<cv::Vec3b>(y, x)[1] == 0 && im.at<cv::Vec3b>(y, x)[2] == 0) {
				im.at<cv::Vec3b>(y, x)[0] = 200;
				im.at<cv::Vec3b>(y, x)[1] = 100;
				im.at<cv::Vec3b>(y, x)[2] = 0;
/*				if (x < (im.size().width - 1) && x > 0 && y < (im.size().height - 1) && y > 0 &&
					(im.at<cv::Vec3b>(y - 1, x)[0] > 100 || im.at<cv::Vec3b>(y + 1, x)[0] > 0 ||
						im.at<cv::Vec3b>(y - 1, x - 1)[0] > 0 || im.at<cv::Vec3b>(y + 1, x - 1)[0] > 0 ||
						im.at<cv::Vec3b>(y - 1, x + 1)[0] > 0 || im.at<cv::Vec3b>(y + 1, x + 1)[0] > 0 ||
						im.at<cv::Vec3b>(y, x - 1)[0] > 0 || im.at<cv::Vec3b>(y, x - 1)[0] > 0))
				{
					im.at<cv::Vec3b>(y, x)[0] = 0;
					im.at<cv::Vec3b>(y, x)[1] = 0;
					im.at<cv::Vec3b>(y, x)[2] = 255;
				}*/
			}
		}
	}

	imshow("Image", im);
	waitKey(0);
	return 0;
}

