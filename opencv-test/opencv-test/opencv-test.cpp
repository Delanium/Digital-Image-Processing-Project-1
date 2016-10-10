// opencv-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cmath> 


using namespace cv;
using namespace std;

bool checkIfInShape(int x, int y , Mat im) {
	if (im.at<cv::Vec3b>(y, x)[0] == 0 && im.at<cv::Vec3b>(y, x)[1] == 0 && im.at<cv::Vec3b>(y, x)[2] == 0) {
		return true;
	}
	return false;
}

int calculatePointXOfCircle(int degree, int radius, int centerX) {
	return (centerX + radius * cos(degree));
}

int calculatePointYOfCircle(int degree, int radius, int centerY) {
	return (centerY - radius * sin(degree));
}


void checkCircle(Mat &im) {
	int minX = im.size().width;
	int maxX = 0;
	int minY = im.size().height;
	int maxY = 0;

	for (int y = 0; y < im.size().height; y++) {
		for (int x = 0; x < im.size().width; x++) {
			if (im.at<cv::Vec3b>(y, x)[0] == 0 && im.at<cv::Vec3b>(y, x)[1] == 0 && im.at<cv::Vec3b>(y, x)[2] == 0) {
				if (x < minX) {
					minX = x;
				}
				if (x > maxX) {
					maxX = x;
				}
				if (y < minY) {
					minY = y;
				}
				if (y > minY) {
					maxY = y;
				}
			}
		}
	}

	if ((maxX - minX) * 0.9 < (maxY - minY) && (maxX - minX) * 1.1 > (maxY - minY)) {
		cout << "MinX : " << minX << endl;
		cout << "MaxX : " << maxX << endl;
		cout << "MinY : " << minY << endl;
		cout << "MaxY : " << maxY << endl;

		cout << "X : " << (maxX - minX) << endl;
		cout << "Y : " << (maxY - minY) << endl;

		int radius;
		int centerX;
		int centerY;
		if ((maxX - minX) < (maxY - minY)) {
			radius = (maxX - minX) / 2 * 0.9;
		}
		else {
			radius = (maxY - minY) / 2 * 0.9;
		}
		centerX = minX + radius;
		centerY = minY + radius;

		cout << "Radius : " << radius << endl;
		cout << "Center X : " << centerX << endl;
		cout << "Center Y : " << centerY << endl;

		cout << calculatePointXOfCircle(45, radius, centerX) << endl;
		cout << calculatePointYOfCircle(45, radius, centerY) << endl;

		cout << calculatePointXOfCircle(135, radius, centerX) << endl;
		cout << calculatePointYOfCircle(135, radius, centerY) << endl;


		if (checkIfInShape(calculatePointXOfCircle(45, radius, centerX), calculatePointYOfCircle(45, radius, centerY), im) == true &&
			checkIfInShape(calculatePointXOfCircle(135, radius, centerX), calculatePointYOfCircle(135, radius, centerY), im) == true) {
			cout << "Circle" << endl;
		}
	}
}

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


	// Check circle
	checkCircle(im);


	imshow("Image", im);
	waitKey(0);
	return 0;


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

