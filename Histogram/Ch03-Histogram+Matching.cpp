// Ch03-Histogram Matching.cpp : Defines the entry point for the console application.
//



#include "myHist.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\core\core.hpp>




#define		FILE_INPUT	"lena.bmp"
#define		FILE_TARGET	"bean.tif"

cv::Mat		input;				// for input image
cv::Mat		target;				// for target histogram
cv::Mat		EqLena;
cv::Mat		output;				// for output image
cv::Mat		canvasInput;		// for drawing input image 
cv::Mat		canvasTarget;		// for drawing target image
cv::Mat		canvasOutput;		// for drawing output image

// method prototype
void		FormUniformMapFunc(cv::Mat&, int[256]);
void		InitField(int, int);

int main(void)

{
	// load the lena image and display it
	input = cv::imread("lena.bmp", cv::IMREAD_GRAYSCALE);

	// init fields
	InitField(input.cols, input.rows);
	int LenaHistogram[256] = { 0 };
	float LenaEqHistogram[256] = { 0 };


	//for (int z = 0; z < 256; z++)
	//{
	//	LenaEqHistogram[z] = 0;
	//	LenaHistogram[z] = 0;
	//}

	FormUniformMapFunc(input, LenaHistogram);

	for (int i = 0; i < 256; i++)
	{
		LenaEqHistogram[i] = ((float)LenaHistogram[i]) / (512 * 512);
	}

	for (int i = 1; i < 256; i++)
	{
		LenaEqHistogram[i] += LenaEqHistogram[i - 1];
	}

	for (int i = 0; i < 256; i++)
	{
		LenaEqHistogram[i] = LenaEqHistogram[i] * 255;
	}

	for (int x = 0; x < input.cols; x++)
	{
		for (int y = 0; y < input.rows; y++)
		{
			int d = input.at<unsigned char>(y, x);
			EqLena.at<unsigned char>(y, x) = LenaEqHistogram[d];
		}
	}


	// compute the transform T and G

	// compute the inverse function viInvG using average strategy

	// form the matching function

	// calculate the histogram of output

	// show the raw image
	cv::namedWindow("Gray", cv::WINDOW_AUTOSIZE);
	cv::imshow("Gray", input);

	// show the histogram of input and target images
	myHist* pHist = new myHist(myHist::Type::Image);

	// calculate the histogram of lena 
	pHist->CalcHist(input);
	canvasInput = cv::Scalar::all(0);
	pHist->Show(canvasInput);


	myHist* gHist = new myHist(myHist::Type::Image);
	gHist->CalcHist(EqLena);
	canvasOutput = cv::Scalar::all(0);
	gHist->Show(canvasOutput);
	cv::imshow("4456", EqLena);

	// show the raw image
	cv::namedWindow("output", cv::WINDOW_AUTOSIZE);
	cv::imshow("output", canvasInput);


	cv::namedWindow("output Hist", cv::WINDOW_AUTOSIZE);
	cv::imshow("output Hist", canvasOutput);

	cv::waitKey(0);

	return 0;
}// End of main

/* FormUniformMapFunc
*
* Description: form the uniform mapping fuction
*
* Programmer: poww
* Create Date:  2015.08.30
*/
void FormUniformMapFunc(cv::Mat& image, int viT[256]){

	for (int x = 0; x < image.cols; x++)
	{
		for (int y = 0; y < image.rows; y++)
		{
			int g = 0;
			g = image.at<unsigned char>(y, x);
			viT[g]++;

		}
	}

}
// End of FormUniformMapFunc

/* InitField
*
* Description: init all fields
*
* Programmer: poww
* Create Date:  2015.08.30
*/
void InitField(int width, int height){
	output.create(cv::Size(width, height), CV_8UC1);
	EqLena.create(cv::Size(width, height), CV_8UC1);
	canvasInput.create(cv::Size(512, 512), CV_8UC3);
	canvasTarget.create(cv::Size(512, 512), CV_8UC3);
	canvasOutput.create(cv::Size(512, 512), CV_8UC3);
}// End of InitField
