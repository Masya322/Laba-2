#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#include <opencv2/imgproc.hpp>
#include <vector>

using namespace cv;
using namespace std;

void filter(const Mat& input_img, Mat& output_img, vector<double> kernel) {
	output_img = input_img;
	for (int i = 1; i < output_img.rows - 1; i++) {
		for (int j = 1; j < output_img.cols - 1; j++) {
			output_img.at<Vec3b>(i, j)[0] = input_img.at<Vec3b>(i - 1, j - 1)[0] * kernel[0] + input_img.at<Vec3b>(i, j - 1)[0] * kernel[1] + input_img.at<Vec3b>(i + 1, j - 1)[0] * kernel[2] + input_img.at<Vec3b>(i - 1, j)[0] * kernel[3] + input_img.at<Vec3b>(i, j)[0] * kernel[4] + input_img.at<Vec3b>(i + 1, j)[0] * kernel[5] + input_img.at<Vec3b>(i - 1, j + 1)[0] * kernel[6] + input_img.at<Vec3b>(i, j + 1)[0] * kernel[7] + input_img.at<Vec3b>(i + 1, j + 1)[0] * kernel[8];
			output_img.at<Vec3b>(i, j)[1] = input_img.at<Vec3b>(i - 1, j - 1)[1] * kernel[0] + input_img.at<Vec3b>(i, j - 1)[1] * kernel[1] + input_img.at<Vec3b>(i + 1, j - 1)[1] * kernel[2] + input_img.at<Vec3b>(i - 1, j)[1] * kernel[3] + input_img.at<Vec3b>(i, j)[1] * kernel[4] + input_img.at<Vec3b>(i + 1, j)[1] * kernel[5] + input_img.at<Vec3b>(i - 1, j + 1)[1] * kernel[6] + input_img.at<Vec3b>(i, j + 1)[1] * kernel[7] + input_img.at<Vec3b>(i + 1, j + 1)[1] * kernel[8];
			output_img.at<Vec3b>(i, j)[2] = input_img.at<Vec3b>(i - 1, j - 1)[2] * kernel[0] + input_img.at<Vec3b>(i, j - 1)[2] * kernel[1] + input_img.at<Vec3b>(i + 1, j - 1)[2] * kernel[2] + input_img.at<Vec3b>(i - 1, j)[2] * kernel[3] + input_img.at<Vec3b>(i, j)[2] * kernel[4] + input_img.at<Vec3b>(i + 1, j)[2] * kernel[5] + input_img.at<Vec3b>(i - 1, j + 1)[2] * kernel[6] + input_img.at<Vec3b>(i, j + 1)[2] * kernel[7] + input_img.at<Vec3b>(i + 1, j + 1)[2] * kernel[8];
		}
	}
}
void Blur(const Mat& input_img, Mat& output_img) {
	vector<double> kernel = { 0.1,0.1,0.1,   0.1,0.1,0.1,    0.1,0.1,0.1, };
	filter(input_img, output_img, kernel);
}


int Ujane(Mat img, int x, int y)
{
	return img.at<uchar>(y - 1, x - 1) + 2 * img.at<uchar>(y-1, x) + img.at<uchar>(y - 1, x + 1) - img.at<uchar>(y + 1, x - 1) - 2 * img.at<uchar>(y + 1, x) - img.at<uchar>(y + 1, x + 1);
}

void Sobel(const Mat& input_img, Mat& output_img) {
	output_img = input_img.clone();
	int newt;
	for (int y = 0; y < input_img.rows; y++)
		for (int x = 0; x < input_img.cols; x++)
			output_img.at<uchar>(y, x) = 0.0;
	for (int y = 1; y < input_img.rows - 1; y++) {
		for (int x = 1; x < input_img.cols - 1; x++) {
			newt = Ujane(input_img, x, y);
			output_img.at<uchar>(y, x) = newt;
		}
	}
}

int main(int argc, char** argv)
{
	// Read the image file
	Mat image = imread("pap.jpg");
	Mat image1;
	Mat image2;
	Mat image3;
	Mat image4;
	Mat image5 = imread("pap.jpg");

	
	GaussianBlur(image, image1, Size(-1, -1), 5);
	cvtColor(image, image2, COLOR_BGR2GRAY);
	Blur(image5, image3);
	Sobel(image2, image4);



	String windowName = "original"; 
	String windowName1 = "Vebka_papicha";
	String windowName2 = "Legkoe_razmitie";
	String windowName3 = "Toleranrnii_papich";



	namedWindow(windowName); 
	namedWindow(windowName1);
	namedWindow(windowName2);
	namedWindow(windowName3);



	imshow(windowName, image);
	imshow(windowName1, image1); 
	imshow(windowName2, image3);
	imshow(windowName3, image4);

	waitKey(0); 

	destroyWindow(windowName); 
	destroyWindow(windowName1);
	destroyWindow(windowName2);
	destroyWindow(windowName3);

	return 0;
}

