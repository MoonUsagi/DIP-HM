#include <opencv2/highgui/highgui.hpp>
#include <opencv2\core\core.hpp>
#include <iostream>
//template<class T>
//
//
//
//void bubble_sort(T arr[], int len)
//{
//	int i, j;
//	T temp;
//	for (i = 0; i < len - 1; i++)
//	for (j = 0; j < len - 1 - i; j++)
//	if (arr[j] > arr[j + 1]) {
//		temp = arr[j];
//		arr[j] = arr[j + 1];
//		arr[j + 1] = temp;
//	}
//}

void FinalBoxFilter(cv::Mat BoxFilter, int BoxMask[9][2], cv::Mat& Box)
{

	int Weight[9]={1,1,1,1,1,1,1,1,1};
	for (int r = 1; r <= BoxFilter.rows - 2; r++)
	{
		for (int c = 1; c <= BoxFilter.cols - 2; c++)
		{
			int sum = 0;
			for (int n = 0; n < 9; n++)
			{
				sum = sum + ((BoxFilter.at<unsigned char>(r + BoxMask[n][0], c + BoxMask[n][1])) / 9);
			}
			
			if (sum < 0) sum = 0;
			if (sum > 255) sum = 255;
			Box.at<unsigned char>(r, c) = sum;
		
		}

	}

}
void FinalMediaFilter(cv::Mat MediaFilter, int MediaMask[9][2], cv::Mat& Media)
{

	int Weight[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

	for (int r = 1; r <= MediaFilter.rows - 2; r++)
	{
		for (int c = 1; c <= MediaFilter.cols - 2; c++)
		{
			int sum[9] = {0};
			for (int n = 0; n < 9; n++)

			{
				sum[n] =  MediaFilter.at<unsigned char>(r + MediaMask[n][0], c + MediaMask[n][1]);
			}
			
				int i, j;
				int temp;
				int len = 9;

				for (i = 0; i < len - 1; i++)
				{
					for (j = 0; j < len - 1 - i; j++)
					{

						if (sum[j] > sum[j + 1])
						{
							temp = sum[j];
							sum[j] = sum[j + 1];
							sum[j + 1] = temp;
						}
					}
				}
				if (sum[5] < 0) sum[5] = 0;
				if (sum[5] > 255) sum[5] = 255;
				Media.at<unsigned char>(r, c) = sum[5];

		}

	}

}
void FinalLaplacianImageEnhancement(cv::Mat LaplacianFilter, int LaplacianMask[9][2], cv::Mat& Laplacian)
{

	int Weight[9] = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };
	for (int r = 1; r <= LaplacianFilter.rows - 2; r++)
	{
		for (int c = 1; c <= LaplacianFilter.cols - 2; c++)
		{
			int sum = 0;
			for (int n = 0; n < 9; n++)
			{
				sum = sum + (LaplacianFilter.at<unsigned char>(r + LaplacianMask[n][0], c + LaplacianMask[n][1]) * Weight[n]);
			}
			if (sum < 0) sum = 0;
			if (sum > 255) sum = 255;
			Laplacian.at<unsigned char>(r, c) = sum;

		}

	}

}
void FinalSobeledgedetectorinXdirection(cv::Mat SobelXFilter, int SobelXMask[9][2], cv::Mat& SobelX)
{

	int Weight[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	for (int r = 1; r <= SobelXFilter.rows - 2; r++)
	{
		for (int c = 1; c <= SobelXFilter.cols - 2; c++)
		{
			int sum = 0;
			for (int n = 0; n < 9; n++)
			{
				//sum = sum + ((Laplacian.at<unsigned char>(r + LaplacianMask[n][0], c + LaplacianMask[n][1])) / 9);
				sum = sum + (SobelXFilter.at<unsigned char>(r + SobelXMask[n][0], c + SobelXMask[n][1]) * Weight[n]);

			}
			if (sum < 0) sum = 0;
			if (sum > 255) sum = 255;
			SobelX.at<unsigned char>(r, c) = sum;

		}

	}

}
void FinalSobeledgedetectorinYdirection(cv::Mat SobelYFilter, int SobelYMask[9][2], cv::Mat& SobelY)
{

	int Weight[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	for (int r = 1; r <= SobelYFilter.rows - 2; r++)
	{
		for (int c = 1; c <= SobelYFilter.cols - 2; c++)
		{
			int sum = 0;
			for (int n = 0; n < 9; n++)
			{
				sum = sum + (SobelYFilter.at<unsigned char>(r + SobelYMask[n][0], c + SobelYMask[n][1]) * Weight[n]);
			}
			if (sum < 0) sum = 0;
			if (sum > 255) sum = 255;
			SobelY.at<unsigned char>(r, c) = sum;

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
    cv::Mat BoxFilter = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat Box = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	
	cv::Mat MediaFilter = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat Media = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);

	cv::Mat LaplacianFilter = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat Laplacian = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);

	cv::Mat SobelXFilter = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat SobelX = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);

	cv::Mat SobelYFilter = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat SobelY = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);

	
	//int cols = mImg.cols, rows = mImg.rows;
	
	//BoxMask
	int Mask[9][2] = 
	{ 
		{ -1,-1 }, { 0, -1 }, {+1,-1},
		{ -1, 0 }, { 0, 0 }, { +1, 0 },
		{ -1, +1 }, { -1, 0 }, {-1,+1}
	
	};

	// void
	FinalBoxFilter(mImg, Mask, Box);
	FinalMediaFilter(mImg, Mask, Media);
	FinalLaplacianImageEnhancement(mImg, Mask, Laplacian);
	FinalSobeledgedetectorinXdirection(mImg, Mask, SobelX);
	FinalSobeledgedetectorinYdirection(mImg, Mask, SobelY);
	
	// 叫圖

	cv::namedWindow("LenaOutputOne", cv::WINDOW_AUTOSIZE);
	cv::imshow("LenaOutputOne", mImg);
	
	cv::namedWindow("BoxFilterOut", cv::WINDOW_AUTOSIZE);
	cv::imshow("BoxFilterOut",Box);
	
	cv::namedWindow("MediaFilterOut", cv::WINDOW_AUTOSIZE);
	cv::imshow("MediaFilterOut", Media);
	
	cv::namedWindow("LaplacianOut", cv::WINDOW_AUTOSIZE);
	cv::imshow("LaplacianOut", Laplacian);
    
	cv::namedWindow("SobelXOut", cv::WINDOW_AUTOSIZE);
	cv::imshow("SobelXOut", SobelX);

	cv::namedWindow("SobelYOut", cv::WINDOW_AUTOSIZE);
	cv::imshow("SobelYOut", SobelY);
	
	
	cv::waitKey(0);
	return 0;
}