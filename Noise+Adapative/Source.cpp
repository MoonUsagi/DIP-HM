#include <opencv2/highgui/highgui.hpp>
#include <opencv2\core\core.hpp>
#include <iostream>



//void AdaptivefFilter(cv::Mat AFilter, cv::Mat& Adaptive, int hisA[])
//{
//	bool can5, can7 = false;
//	int pixels3[9] = { 0 };
//	int pixels5[25] = { 0 };
//	int pixels7[49] = { 0 };
//	int x, y, temp = 0;
//
//	int Mask3[9][2] = 
//	{
//		{ -1, -1 }, { 0, -1 }, { +1, -1 },
//		{ -1, 0 }, { 0, 0 }, { +1, 0 },
//		{ -1, +1 }, { 0, +1 }, { +1, +1 } 
//	};
//
//	int Mask5[25][2] = 
//	{
//		{ -2, -2 }, { -1, -2 }, { 0, -2 }, { 1, -2 }, { 2, 2 },
//		{ -2, -1 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 2, -1 },
//		{ -2, 0 }, { -1, 0 }, { 0, 0 }, { 1, 0 }, { 2, 0 },
//		{ -2, +1 }, { -1, +1 }, { 0, +1 }, { 1, +1 }, { 2, +1 },
//		{ -2, +2 }, { -1, +2 }, { 0, +2 }, { 1, +2 }, { 2, +2 } 
//	};
//
//	int Mask7[49][2] = 
//	{
//		{ -3, -3 }, { -2, -3 }, { -1, -3 }, { 0, -3 }, { 1, -3 }, { 2, -3 }, { 3, -3 },
//		{ -3, -2 }, { -2, -2 }, { -1, -2 }, { 0, -2 }, { 1, -2 }, { 2, -2 }, { 3, -2 },
//		{ -3, -1 }, { -2, -1 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 2, -1 }, { 3, -1 },
//		{ -3, 0 }, { -2, 0 }, { -1, 0 }, { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 },
//		{ -3, +1 }, { -2, +1 }, { -1, +1 }, { 0, +1 }, { 1, +1 }, { 2, +1 }, { 3, +1 },
//		{ -3, +2 }, { -2, +2 }, { -1, +2 }, { 0, +2 }, { 1, +2 }, { 2, +2 }, { 3, +2 },
//		{ -3, +3 }, { -2, +3 }, { -1, +3 }, { 0, +3 }, { 1, +3 }, { 2, +3 }, { 3, +3 } 
//	};
//
//	for (int r = 1; r <= AFilter.rows - 1; r++)
//	{
//		for (int c = 1; c <= AFilter.cols - 1; c++)
//		{
//			
//			can5 = can7 = false;
//			//
//			for (int i = 0; i < 9; i++)
//			{
//				x = r + Mask3[i][0];
//				y = c + Mask3[i][1];
//				pixels3[i] = AFilter.at<unsigned char>(x, y);
//			}
//			//
//
//
//			//
//			if (r - 2>0 && c - 2>0 && r + 2 < 512 && c + 2 < 512)
//			{
//				for (int i = 0; i < 25; i++)
//				{
//					x = r + Mask5[i][0];
//					y = c + Mask5[i][1];
//					pixels5[i] = AFilter.at<unsigned char>(x, y);
//				}
//				for (int i = 0; i < 25; i++) 
//				{
//					for (int j = i; j < 25; j++) 
//					{
//						if (pixels5[j] < pixels5[i]) 
//						{
//							temp = pixels5[j];
//							pixels5[j] = pixels5[i];
//							pixels5[i] = temp;
//						}
//					}
//				}
//				can5 = true;
//			}
//			//
//
//
//            //
//			else if (r - 3>0 && c - 3 > 0 && r + 3 < 512 && c + 3 < 512)
//			{
//				for (int i = 0; i < 49; i++)
//				{
//					x = r + Mask7[i][0];
//					y = c + Mask7[i][1];
//					pixels7[i] = AFilter.at<unsigned char>(x, y);
//				}
//				for (int i = 0; i < 9; i++) 
//				{
//					for (int j = i; j < 9; j++)
//					{
//						if (pixels7[j] < pixels7[i])
//						{
//							temp = pixels7[j];
//							pixels7[j] = pixels7[i];
//							pixels7[i] = temp;
//						}
//					}
//				}
//				can7 = true;
//			}
//
//
//			//
//			for (int i = 0; i < 9; i++) 
//			{
//				for (int j = i; j < 9; j++) 
//				{
//					if (pixels3[j] < pixels3[i]) 
//					{
//						temp = pixels3[j];
//						pixels3[j] = pixels3[i];
//						pixels3[i] = temp;
//					}
//				}
//			}
//			//
//
//
//			//
//			if ((pixels3[5] - pixels3[0])>0 && (pixels3[5] - pixels3[8])<0)
//			{
//				if ((AFilter.at<unsigned char>(x, y) - pixels3[0])>0 && (AFilter.at<unsigned char>(x, y) - pixels3[8]) < 0)
//				{
//					Adaptive.at<unsigned char>(r, c) = AFilter.at<unsigned char>(x, y);
//				}
//				else
//				{
//					Adaptive.at<unsigned char>(r, c) = pixels3[5];
//				}
//			}
//			else if (can5)
//			{
//				if ((pixels5[5] - pixels5[0])>0 && (pixels5[5] - pixels5[8])<0)
//				{
//					if ((AFilter.at<unsigned char>(x, y) - pixels5[0])>0 && (AFilter.at<unsigned char>(x, y) - pixels5[8]) < 0)
//					{
//						Adaptive.at<unsigned char>(r, c) = AFilter.at<unsigned char>(x, y);
//					}
//					else
//					{
//						Adaptive.at<unsigned char>(r, c) = pixels5[13];
//					}
//				}
//			}
//			else if (can7)
//			{
//				if ((pixels7[5] - pixels7[0])>0 && (pixels7[5] - pixels7[8])<0)
//				{
//					if ((AFilter.at<unsigned char>(x, y) - pixels7[0])>0 && (AFilter.at<unsigned char>(x, y) - pixels7[8]) < 0)
//					{
//						Adaptive.at<unsigned char>(r, c) = AFilter.at<unsigned char>(x, y);
//					}
//					else
//					{
//						Adaptive.at<unsigned char>(r, c) = pixels7[25];
//					}
//				}
//			}
//			else
//			{
//				Adaptive.at<unsigned char>(r, c) = AFilter.at<unsigned char>(x, y);
//			}
//			//
//
//
//
//			//
//			for (int i = 0; i < 256; i++)
//			{
//				hisA[i] = 0;
//			}
//
//
//			for (int y = 0; y < Adaptive.rows; y++)
//			{
//				for (int x = 0; x < Adaptive.cols; x++)
//				{
//					hisA[(int)Adaptive.at<uchar>(y, x)]++;
//
//				}
//			}
//			//
//
//		}
//	}
//
//}

void sort(int arr[], int len)
{
	int i, j, temp;
	for (i = 0; i < len - 1; i++)
	{
		for (j = 0; j < len - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void AdaptivefFilter(cv::Mat AFilter, cv::Mat& Adaptive, int hisA[])
{
	for (int r = 0; r < AFilter.rows ; r++)
	{
		for (int c = 0; c < AFilter.cols ; c++)
		{
			int temporarily = AFilter.at<unsigned char>(r, c);

			for (int lenghth = 3; lenghth <= 9; lenghth += 2)
			{
				int hold = lenghth / 2;
				if ((r - hold < 0) || (c - hold < 0) || (r + hold  > AFilter.rows - 1) || (c + hold  > AFilter.cols - 1)) break;

				int* array = new int[lenghth * lenghth];
				int index = 0;
				for (int x = r - hold; x <= r + hold; x++)
				{
					for (int y = c - hold; y <= c + hold; y++)
					{
						array[index++] = AFilter.at<unsigned char>(x, y);
					}
				}
				sort(array, lenghth * lenghth);
				
				int mid = array[lenghth * lenghth / 2], min = array[0], max = array[lenghth * lenghth - 1];
				int a1 = mid - min, a2 = mid - max;
				if (a1 > 0 && a2 < 0)
				{
					int xy = AFilter.at<unsigned char>(r ,c);

					int b1 = xy - min, b2 = xy - max;
					if (b1 > 0 && b2 < 0) temporarily = xy;
					else temporarily = mid;
				}
				delete[] array;
			}

			Adaptive.at<unsigned char>(r, c) = temporarily;
		}
	}

	for (int i = 0; i < 256; i++)
	{
		hisA[i] = 0;
	}


	for (int y = 0; y < Adaptive.rows; y++)
	{
		for (int x = 0; x < Adaptive.cols; x++)
		{
			hisA[(int)Adaptive.at<unsigned char>(y, x)]++;

		}
	}

}

void histDisplay(int histogram[], const char* name)
{
	int hist[256];
	for (int i = 0; i < 256; i++)
	{
		hist[i] = histogram[i];
	}
	// draw the histograms
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);

	cv::Mat histImage(hist_h, hist_w, CV_8UC1, cv::Scalar(255, 255, 255));

	// find the maximum intensity element from histogram
	int max = hist[0];
	for (int i = 1; i < 256; i++){
		if (max < hist[i]){
			max = hist[i];
		}
	}

	// normalize the histogram between 0 and histImage.rows

	for (int i = 0; i < 256; i++){
		hist[i] = ((double)hist[i] / max)*histImage.rows;
	}


	// draw the intensity line for histogram
	for (int i = 0; i < 256; i++)
	{
		line(histImage, cv::Point(bin_w*(i), hist_h),
			cv::Point(bin_w*(i), hist_h - hist[i]),
			cv::Scalar(0, 0, 0), 1, 8, 0);
	}

	// display histogram
	cv::namedWindow(name, CV_WINDOW_AUTOSIZE);
	imshow(name, histImage);
}

void gaussianNoise(cv::Mat Gaussian, cv::Mat& GaussianNoise, int hisGaussian[])
{
	for (int r = 1; r <= Gaussian.rows - 1; r++)
	{
		for (int c = 1; c <= Gaussian.cols - 1; c++)
		{
			int Noise;
			Noise = (rand() % 101);

			if (Noise <= 3)
			{
				GaussianNoise.at<unsigned char>(r, c) = (Gaussian.at<unsigned char>(r, c) - 5);
			}

			else if (Noise > 3, Noise <= 8)
			{
				GaussianNoise.at<unsigned char>(r, c) = (Gaussian.at<unsigned char>(r, c) - 4);
			}
			else if (Noise > 8, Noise <=16 )
			{
				GaussianNoise.at<unsigned char>(r, c) = (Gaussian.at<unsigned char>(r, c) - 3);
			}
			else if (Noise > 16, Noise <= 26)
			{
				GaussianNoise.at<unsigned char>(r, c) = (Gaussian.at<unsigned char>(r, c) - 2);
			}
			else if (Noise > 26, Noise <= 38)
			{
				GaussianNoise.at<unsigned char>(r, c) = (Gaussian.at<unsigned char>(r, c) - 1);
			}
			else if (Noise > 38, Noise <=51)
			{
				GaussianNoise.at<unsigned char>(r, c) = (Gaussian.at<unsigned char>(r, c) + 0);
			}
			else if (Noise > 51, Noise <= 63)
			{
				GaussianNoise.at<unsigned char>(r, c) = (Gaussian.at<unsigned char>(r, c) + 1);
			}
			else if (Noise > 63, Noise <= 73)
			{
				GaussianNoise.at<unsigned char>(r, c) = (Gaussian.at<unsigned char>(r, c) + 2);
			}
			else if (Noise > 73, Noise <=81)
			{
				GaussianNoise.at<unsigned char>(r, c) = (Gaussian.at<unsigned char>(r, c) + 3);
			}
			else if (Noise > 81, Noise <= 89)
			{
				GaussianNoise.at<unsigned char>(r, c) = (Gaussian.at<unsigned char>(r, c) + 4);
			}
			else if (Noise > 88, Noise <= 91)
			{
				GaussianNoise.at<unsigned char>(r, c) = (Gaussian.at<unsigned char>(r, c) + 5);
			}
			else
			{
				GaussianNoise.at<unsigned char>(r, c) = Gaussian.at<unsigned char>(r, c);
			}
		}
	}
	for (int i = 0; i < 256; i++)
	{
		hisGaussian[i] = 0;
	}


	for (int y = 0; y < GaussianNoise.rows; y++)
	{
		for (int x = 0; x < GaussianNoise.cols; x++)
		{
			hisGaussian[(int)GaussianNoise.at<uchar>(y, x)]++;

		}
	}


}

void spNoise(cv::Mat SP, cv::Mat& SPNoise, int hisSP[])
{
	for (int r = 1; r <= SP.rows - 1; r++)
	{
		for (int c = 1; c <= SP.cols - 1; c++)
		{
			int Noise;
			Noise = (rand() % 101) ;
			if (Noise <= 10)
			{
				SPNoise.at<unsigned char>(r, c) = 0;
			}
			else if (Noise >= 90)
			{
				SPNoise.at<unsigned char>(r, c) = 255;
			}
			else{
				SPNoise.at<unsigned char>(r, c) = SP.at<unsigned char>(r, c);
			}
			
		
		}
	}
	for (int i = 0; i < 256; i++)
	{
		hisSP[i] = 0;
	}


	for (int y = 0; y < SPNoise.rows; y++)
	{
		for (int x = 0; x < SPNoise.cols; x++)
		{
			hisSP[(int)SPNoise.at<uchar>(y, x)]++;

		}
	}

}

void uniformNoise(cv::Mat Uniform, cv::Mat& UniformNoise, int hisUniform[])
{
	for (int r = 1; r <= Uniform.rows - 1; r++)
	{
		for (int c = 1; c <= Uniform.cols - 1; c++)
		{
			int Noise;
			Noise = (rand() % 21) - 10;
			UniformNoise.at<unsigned char>(r,c) = (Uniform.at<unsigned char>(r,c) + Noise);

		}
	}

	for (int i = 0; i < 256; i++)
	{
		hisUniform[i] = 0;
	}


	for (int y = 0; y < UniformNoise.rows; y++)
	{
		for (int x = 0; x < UniformNoise.cols; x++)
		{
			hisUniform[(int)UniformNoise.at<uchar>(y, x)]++;

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
	cv::Mat oriImg = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat gauImg = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);

	cv::Mat Gaussian = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat GaussianNoise = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);

	cv::Mat SP = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat SPNoise = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);

	cv::Mat Uniform = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat UniformNoise = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);

	cv::Mat AFilter = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat Adaptive = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	
	cv::Mat SAdaptive = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat UAdaptive = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);
	cv::Mat Gdaptive = cv::Mat::zeros(mImg.rows, mImg.cols, CV_8UC1);


	int histogram[256] = { 0 };
	int hisGaussian[256] = { 0 };
	int hisSP[256] = { 0 };
	int hisUniform[256] = { 0 };
	int hisA[256] = { 0 };
	int hisB[256] = { 0 };
	int hisC[256] = { 0 };
	char windowname[] = { 0 };


	// gaussianNoise(oriImg, gauImg, amp);
	// gaussianNoise(mImg, GaussianNoise);
	spNoise(mImg, SPNoise, hisSP);
	uniformNoise(mImg, UniformNoise, hisUniform);
	gaussianNoise(mImg, GaussianNoise, hisGaussian);
	//AdaptivefFilter(mImg, Adaptive, hisA);
	AdaptivefFilter(SPNoise, SAdaptive, hisB);
	AdaptivefFilter(UniformNoise, UAdaptive, hisC);
	AdaptivefFilter(GaussianNoise, Gdaptive, hisA);



	
	// 叫圖

	histDisplay(hisUniform, "hisUniform");
	histDisplay(hisSP, "hisSP");
	histDisplay(hisGaussian, "hisGaussian");
	//histDisplay(histogram, "histogram");
	histDisplay(hisA, "hisA");

	
	cv::namedWindow("LenaOutputOne", cv::WINDOW_AUTOSIZE);
	cv::imshow("LenaOutputOne", mImg);

	cv::namedWindow("GaussianOut", cv::WINDOW_AUTOSIZE);
	cv::imshow("GaussianOut", GaussianNoise);

	cv::namedWindow("SPOut", cv::WINDOW_AUTOSIZE);
	cv::imshow("SPOut", SPNoise);

	cv::namedWindow("UniformOut", cv::WINDOW_AUTOSIZE);
	cv::imshow("UniformOut", UniformNoise);

	cv::namedWindow("UniformOut", cv::WINDOW_AUTOSIZE);
	cv::imshow("UniformOut", UniformNoise);

	cv::namedWindow("SAdaptiveOut", cv::WINDOW_AUTOSIZE);
	cv::imshow("SAdaptiveOut", SAdaptive);

	cv::namedWindow("UAdaptiveOut", cv::WINDOW_AUTOSIZE);
	cv::imshow("UAdaptiveOut", UAdaptive);

	cv::namedWindow("GAdaptiveOut", cv::WINDOW_AUTOSIZE);
	cv::imshow("GAdaptiveOut", Gdaptive);

	




	cv::waitKey(0);
	return 0;
}