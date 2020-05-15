#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;


void gamma(Mat src, Mat &dst,float gamma)
{
	vector<float> table;
	float d_g;
	int row = src.rows;
	int col = src.cols;
	for (int i = 0; i < 256; i++)
	{
		d_g = float(i);
		d_g /= 255.0;
		d_g = pow(d_g, gamma);
		d_g *= 255;
		table.push_back(d_g);
	}

	for (int j = 0; j < row; j++)
	{
		for (int k = 0; k < col; k++)
		{
			int res = src.at<uchar>(j, k);
			dst.at<uchar>(j, k) = uchar(table[res]);
		}
	}

}

void equalizeHistthree(Mat src, Mat &dst)
{
	vector<Mat> srcs;
	split(src, srcs);
	for (int i = 0; i < srcs.size(); i++)
	{
		equalizeHist(srcs[i], srcs[i]);
	}
	merge(srcs, dst);
}

int main()
{
	//练习1 gamma
	Mat src = imread("face.jpg",0);
	Mat dst;
	src.copyTo(dst);
	gamma(src, dst, 0.5);
	imwrite("src1.jpg", dst);
	imshow("res", dst);
	waitKey(0);
	//练习2 三通道直方图均衡
	Mat src2 = imread("etest.jpg");
	Mat dst2;
	equalizeHistthree(src2, dst2);
	imwrite("src2.jpg", dst2);
	imshow("dst2", dst2);
	waitKey(0);
	//练习3
	Mat src3 = imread("gtest.jpg",0);
	Mat dst3;
	src3.copyTo(dst3);
	gamma(src3, dst3, 0.45);
	imwrite("src3.jpg", dst3);
	imshow("dst3", dst3);
	waitKey(0);

	return 0;
}