// opencv-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cmath> 
#include <limits>

# define M_PI           3.14159265358979323846  /* pi */

using namespace cv;
using namespace std;

typedef struct Point
{
	int x;
	int y;
}m_point;

bool checkIfInShape(int x, int y , Mat im) {
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


bool checkCircle(Mat &im) {
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

		if (checkIfInShape(calculatePointXOfCircle(45, radius, centerX), calculatePointYOfCircle(45, radius, centerY), im) == true &&
			checkIfInShape(calculatePointXOfCircle(135, radius, centerX), calculatePointYOfCircle(135, radius, centerY), im) == true &&
			checkIfInShape(calculatePointXOfCircle(225, radius, centerX), calculatePointYOfCircle(225, radius, centerY), im) == true &&
			checkIfInShape(calculatePointXOfCircle(315, radius, centerX), calculatePointYOfCircle(315, radius, centerY), im) == true) {
			cout << "Circle" << endl;
			return true;
		}
	}
	return false;
}

bool checkTriangle(Mat &im) {

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

	if (checkIfPointEqual(minX, maxX, 2) == true
		|| checkIfPointEqual(minX, minY, 2) == true
		|| checkIfPointEqual(minX, maxY, 2) == true
		|| checkIfPointEqual(maxX, minY, 2) == true
		|| checkIfPointEqual(maxX, maxY, 2) == true
		|| checkIfPointEqual(minY, maxY, 2) == true) {
		cout << "Triangle" << endl;
		return true;
	}
	return false;
}

void checkImage(Mat im) {

	bool check_circle;
	bool check_triangle;

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
	check_circle = checkCircle(im);

	// Check triangle
	check_triangle = checkTriangle(im);

	if (check_circle == false && check_triangle == false) {
		cout << "No form recognised !" << endl;
	}
}

int main()
{
	cout << "Results :" << endl;

	Mat im = imread("C:/a.jpg");
	cout << "a : ";
	if (im.empty())
	{
		cout << "Cannot load image!" << endl;
	}
	else {
		checkImage(im);
	}

	Mat im2 = imread("C:/b.jpg");
	cout << "b : ";
	if (im2.empty())
	{
		cout << "Cannot load image!" << endl;
	}
	else {
		checkImage(im2);
	}

	Mat im3 = imread("C:/c.jpg");
	cout << "c : ";
	if (im3.empty())
	{
		cout << "Cannot load image!" << endl;
	}
	else {
		checkImage(im3);
	}

	Mat im4 = imread("C:/d.jpg");
	cout << "d : ";
	if (im4.empty())
	{
		cout << "Cannot load image!" << endl;
	}
	else {
		checkImage(im4);
	}

	cout << "Press Enter to Continue";
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
	return 0;
}

