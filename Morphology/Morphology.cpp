#include <opencv2/highgui/highgui.hpp>
#include <opencv2\core\core.hpp>
#include <iostream>


void Binarization(cv::Mat binar, cv::Mat& binarout)
{
	for (int r = 1; r < binar.rows - 1; r++)
	{
		for (int c = 1; c < binar.cols - 1; c++)
		{
			if (binar.at<unsigned char>(r, c) >= 127)
			{
				binarout.at<unsigned char>(r, c) = 255;
			}
			else if (binar.at<unsigned char>(r, c)<127)
			{
				binarout.at<unsigned char>(r, c) = 0;
			} 
		}
	}
}
void Dilation(cv::Mat dilation, cv::Mat& dilaout)
{
	int kernel[5][2] = { { 0, 0 }, { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
	int x, y;
	for (int r = 1; r < dilation.rows - 1; r++)
	{
		for (int c = 1; c < dilation.cols - 1; c++)
		{
			if (dilation.at<unsigned char>(r, c) == 255)
			{

				for (int i = 0; i < 5; i++)
				{
					x = r + kernel[i][0];
					y = c + kernel[i][1];
					dilaout.at<unsigned char>(x, y) = 255;
				}
			}
		}
	}
}

void Erosion(cv::Mat erosion, cv::Mat& erosionout)
{
	int kernel[5][2] = { { 0, 0 }, { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
	int x, y;
	bool flag ;
	for (int r = 1; r < erosion.rows - 1; r++)
	{
		for (int c = 1; c < erosion.cols - 1; c++)
		{
			flag = true;
			
			for (int i = 0; i < 5; i++)
			{
					x = r + kernel[i][0];
					y = c + kernel[i][1];

					if (erosion.at<unsigned char>(x, y) != 255)
					{
						flag = false;
					}
			}
			if (flag)
			{
				erosionout.at<unsigned char>(r, c) = 255;
			}

		}
	}
}






int main(void)
{


	// 讀圖
	cv::Mat mImg = cv::imread("lena.bmp", cv::IMREAD_GRAYSCALE);

	// 防止找不到圖
	if (mImg.empty())
	{
		std::cout << "Not Found!" << std::endl;
		exit(EXIT_FAILURE);
	}

	// 宣告空間
	cv::Mat binar = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat binarout = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat dilation = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat dilaout = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat erosion = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat erosionout = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat Openingout = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat Closingout = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);

	//使用
	Binarization(mImg, binarout);
	Dilation(binarout, dilaout);
	Erosion(binarout, erosionout);
	Dilation(dilaout, Closingout);
	Erosion(erosionout, Openingout);


	// 叫圖
	cv::namedWindow("LenaOutputOne", cv::WINDOW_AUTOSIZE);
	cv::imshow("LenaOutputOne", mImg);

	cv::namedWindow("Binarization", cv::WINDOW_AUTOSIZE);
	cv::imshow("Binarization", binarout);

	cv::namedWindow("Dilation", cv::WINDOW_AUTOSIZE);
	cv::imshow("Dilation", dilaout);

	cv::namedWindow("Erosion", cv::WINDOW_AUTOSIZE);
	cv::imshow("Erosion", erosionout);

	cv::namedWindow("Opening", cv::WINDOW_AUTOSIZE);
	cv::imshow("Opening", Openingout);

	cv::namedWindow("Closing", cv::WINDOW_AUTOSIZE);
	cv::imshow("Closing", Closingout);


	cv::waitKey(0);
	return 0;
}