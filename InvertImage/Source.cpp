#include <opencv2/highgui/highgui.hpp>
#include <iostream>


int main(void)
{
	cv::Mat mImg = cv::imread("lena.bmp", cv::IMREAD_GRAYSCALE);
	if (mImg.empty())
	{
		std::cout << "Not Found!" << std::endl;
		exit(EXIT_FAILURE);
	}

	//cv::Mat row(int y);
	//cv::Mat mImg(int rows, int cols);
	//mImg.at<unsigned char>(int y, int x) = static_cast<unsigned char>(value);
	//cv::Mat row(int y) = mImg.at<unsigned char>(y, x);

	cv::Mat F = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat E = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	int cols = mImg.cols, rows = mImg.rows;



	for (int y = 0; y < E.rows; ++y)
	{
		for (int x = 0; x < E.cols; x++)
		{
			E.at<unsigned char>(y, x) = mImg.at<unsigned char>(y, cols - x - 1);
		}
	}

	for (int y = 0; y < F.rows; ++y)
	{
		for (int x = 0; x < F.cols; x++)
		{
			F.at<unsigned char>(y, x) = mImg.at<unsigned char>(rows - y - 1, x);
		}
	}




	/*
	for (int y = 0; y < mImg.rows; ++y)
	{
	for (int x = 0; x < mImg.cols; x++)
	{
	auto value = static_cast<float>(y) / mImg.rows * 255;
	mImg.at<unsigned char>(y, x) = static_cast<unsigned char>(value);
	}
	}


	int value = mImg.at<unsigned char>(54, 168);
	std::cout << "The Value is: " << value << std::endl;

	cv::namedWindow("Gray", cv::WINDOW_AUTOSIZE);
	cv::imshow("Gray", F);
	*/


	cv::namedWindow("Gray", cv::WINDOW_AUTOSIZE);
	cv::imshow("Gray", F);
	cv::namedWindow("FREE", cv::WINDOW_AUTOSIZE);
	cv::imshow("FREE", E);
	cv::waitKey(0);

	return 0;

}
