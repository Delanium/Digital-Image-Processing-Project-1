// opencv-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cmath> 

# define M_PI           3.14159265358979323846  /* pi */

using namespace cv;
using namespace std;

typedef struct Point
{
	int x;
	int y;
}m_point;

bool checkIfInShape(int x, int y , Mat im) {
	cout << "x in check : " << x << endl;
	cout << "y in check : " << y << endl;
	cout << "check couleur : " << (int)im.at<cv::Vec3b>(y, x)[0] << endl;
	cout << "check couleur : " << (int)im.at<cv::Vec3b>(y, x)[1] << endl;
	cout << "check couleur : " << (int)im.at<cv::Vec3b>(y, x)[2] << endl;
	if (im.at<cv::Vec3b>(y, x)[0] == 0 && im.at<cv::Vec3b>(y, x)[1] == 0 && im.at<cv::Vec3b>(y, x)[2] == 0) {
		return true;
	}
	return false;
}

int calculatePointXOfCircle(float degree, float radius, float centerX) {
	return (centerX + radius * cos(degree * M_PI / 180));
}

int calculatePointYOfCircle(float degree, float radius, float centerY) {
	return (centerY + radius * sin(degree * M_PI / 180));
}

bool checkIfPointEqual(m_point a, m_point b, int turn) {
	if (a.x == b.x && a.y == b.y
		|| a.x + 1 == b.x && a.y == b.y
		|| a.x - 1 == b.x && a.y == b.y
		|| a.x == b.x && a.y + 1 == b.y
		|| a.x == b.x && a.y - 1 == b.y
		|| a.x + 1 == b.x && a.y + 1 == b.y
		|| a.x + 1 == b.x && a.y - 1 == b.y
		|| a.x - 1 == b.x && a.y - 1 == b.y
		|| a.x - 1 == b.x && a.y + 1 == b.y) {
		return true;
	}
	else if (turn > 0) {
		m_point temp = b;

		turn--;
		b.x = temp.x + 1;
		if (checkIfPointEqual(a, b, turn) == true)
			return true;
		b.x = temp.x - 1;
		if (checkIfPointEqual(a, b, turn) == true)
			return true;
		b.y = temp.y + 1;
		if (checkIfPointEqual(a, b, turn) == true)
			return true;
		b.y = temp.y - 1;
		if (checkIfPointEqual(a, b, turn) == true)
			return true;
		b.x = temp.x + 1;
		b.y = temp.y + 1;
		if (checkIfPointEqual(a, b, turn) == true)	
			return true;
		b.x = temp.x - 1;
		b.y = temp.y - 1;
		if (checkIfPointEqual(a, b, turn) == true)
			return true;
		b.x = temp.x + 1;
		b.y = temp.y - 1;
		if (checkIfPointEqual(a, b, turn) == true)
			return true;
		b.x = temp.x - 1;
		b.y = temp.y + 1;
		if (checkIfPointEqual(a, b, turn) == true)
			return true;
	}
	return false;
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
			radius = (maxX - minX) / 2;
		}
		else {
			radius = (maxY - minY) / 2;
		}
		centerX = minX + radius;
		centerY = minY + radius;

		radius *= 0.9;

		cout << "Radius : " << radius << endl;
		cout << "Center X : " << centerX << endl;
		cout << "Center Y : " << centerY << endl;

		cout << "Point x for 45 degre : " << calculatePointXOfCircle(45, radius, centerX) << endl;
		cout << "Point y for 45 degre : " << calculatePointYOfCircle(45, radius, centerY) << endl;

		cout << "Couleur = " << (int)im.at<cv::Vec3b>(0, 0)[0] << endl;

		cout << "Couleur = " << (int)im.at<cv::Vec3b>(calculatePointYOfCircle(45, radius, centerY), calculatePointXOfCircle(45, radius, centerX))[0] << endl;
		cout << "Couleur = " << (int)im.at<cv::Vec3b>(calculatePointYOfCircle(45, radius, centerY), calculatePointXOfCircle(45, radius, centerX))[1] << endl;
		cout << "Couleur = " << (int)im.at<cv::Vec3b>(calculatePointYOfCircle(45, radius, centerY), calculatePointXOfCircle(45, radius, centerX))[2] << endl;

		cout << (bool)checkIfInShape(calculatePointXOfCircle(45, radius, centerX), calculatePointYOfCircle(45, radius, centerY), im) << endl;

		//im.at<cv::Vec3b>(calculatePointYOfCircle(45, radius, centerY), calculatePointXOfCircle(45, radius, centerX))[0] = 246;
		//im.at<cv::Vec3b>(calculatePointYOfCircle(45, radius, centerY), calculatePointXOfCircle(45, radius, centerX))[1] = 21;
		//im.at<cv::Vec3b>(calculatePointYOfCircle(45, radius, centerY), calculatePointXOfCircle(45, radius, centerX))[2] = 89;

		cout << "Point x for 135 degre : " << calculatePointXOfCircle(135.0, radius, centerX) << endl;
		cout << "Point y for 135 degre : " << calculatePointYOfCircle(135.0, radius, centerY) << endl;

		cout << "Point x for 225 degre : " << calculatePointXOfCircle(225, radius, centerX) << endl;
		cout << "Point y for 225 degre : " << calculatePointYOfCircle(225, radius, centerY) << endl;

		cout << "Point x for 315 degre : " << calculatePointXOfCircle(315, radius, centerX) << endl;
		cout << "Point y for 315 degre : " << calculatePointYOfCircle(315, radius, centerY) << endl;


		if (checkIfInShape(calculatePointXOfCircle(45, radius, centerX), calculatePointYOfCircle(45, radius, centerY), im) == true &&
			checkIfInShape(calculatePointXOfCircle(135, radius, centerX), calculatePointYOfCircle(135, radius, centerY), im) == true &&
			checkIfInShape(calculatePointXOfCircle(225, radius, centerX), calculatePointYOfCircle(225, radius, centerY), im) == true &&
			checkIfInShape(calculatePointXOfCircle(315, radius, centerX), calculatePointYOfCircle(315, radius, centerY), im) == true) {
			cout << "Circle" << endl;
		}
	}
}

void checkTriangle(Mat &im) {

	// Initialize point structure
	m_point minX;
	m_point maxX;
	m_point minY;
	m_point maxY;

	minX.x = im.size().width;
	minX.y = 0;

	maxX.x = 0;
	maxX.y = 0;

	minY.x = 0;
	minY.y = im.size().height;

	maxY.x = 0;
	maxY.y = 0;

	for (int y = 0; y < im.size().height; y++) {
		for (int x = 0; x < im.size().width; x++) {
			if (im.at<cv::Vec3b>(y, x)[0] == 0 && im.at<cv::Vec3b>(y, x)[1] == 0 && im.at<cv::Vec3b>(y, x)[2] == 0) {
				if (x < minX.x) {
					minX.x = x;
					minX.y = y;
				}
				if (x > maxX.x) {
					maxX.x = x;
					maxX.y = y;
				}
				if (y < minY.y) {
					minY.y = y;
					minY.x = x;
				}
				if (y > maxY.y) {
					maxY.y = y;
					maxY.x = x;
				}
			}
		}
	}

	cout << "minX = x : " << minX.x << " y : " << minX.y << endl;
	cout << "maxX = x : " << maxX.x << " y : " << maxX.y << endl;
	cout << "minY = x : " << minY.x << " y : " << minY.y << endl;
	cout << "maxY = x : " << maxY.x << " y : " << maxY.y << endl;

	if (checkIfPointEqual(minX, maxX, 2) == true
		|| checkIfPointEqual(minX, minY, 2) == true
		|| checkIfPointEqual(minX, maxY, 2) == true
		|| checkIfPointEqual(maxX, minY, 2) == true
		|| checkIfPointEqual(maxX, maxY, 2) == true
		|| checkIfPointEqual(minY, maxY, 2) == true) {
		cout << "triangle" << endl;
	}
}

int main()
{
	Mat im = imread("C:/Users/Delanium/Documents/Seoul/Digital Image Processing/Project #1/triangle5.jpg");
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

	// Check triangle
	checkTriangle(im);


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

