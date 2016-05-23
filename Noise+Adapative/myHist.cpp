
#include <myHist.h>
#include <opencv2/highgui/highgui.hpp>


/* myHist Constructor
*
* Description: myHist constructor with the given type
*
* Programmer: poww
* Create Date: 2014.08.15
*/
myHist::myHist(myHist::Type type){
	switch (type){
		case myHist::Type::Image:
			// init histogram type
			m_iType = myHist::Type::Image;

			// init bin fields
			m_fStart = 0.;
			m_fBinSize = 0.;
			m_fBinGap = 1.;
			m_iBin = 256;

			// init histogram
			m_Hist.create(cv::Size(m_iBin,1 ), CV_32FC1);
			m_Hist = cv::Scalar::all(0);

			break;

		default:
			printf("myHist::myHist(): Invalid histogram type\n");
			break;
	}// End of switch
}// End of myHist constructor

/* myHist Constructor
*
* Description: myHist constructor
*
* Programmer: poww
* Create Date: 2014.08.15
*/
myHist::myHist(float fStart, float fBinSize, float fBinGap, int iBin){
	if (iBin <= 0){
		printf("myHist::Constructor(): Invalid bin number \n", iBin);
		return;
	}// End of if-condition

	// init histogram type
	m_iType = myHist::Type::Custom;

	// init bin fields
	m_fStart = fStart;
	m_fBinSize = fBinSize;
	m_fBinGap = fBinGap;
	m_iBin = iBin;

	// init histogram
	m_Hist.create(cv::Size(m_iBin,1), CV_32FC1);
	m_Hist = cv::Scalar::all(0);
}// End of myHist constructor


myHist::~myHist()
{
}

/* myHist::Accumulate
*
* Description: accumulate histogram by giving bin index
*
* Programmer: poww
* Create Date: 201
*/
void myHist::Accumulate(int iBinIndex, float fCount){
	// check the bin index
	if (iBinIndex < 0 || iBinIndex >= m_iBin){
		printf("myHist::Accmulate(): The bin index is incorrect\n");
		return;
	}// End of if-condition

	m_Hist.at<float>(0, iBinIndex) += fCount;
}// End of myHist::Accmulate


/* myHist::Accumulate
*
* Description: accumulate histogram by giving value
*
* Programmer: poww
* Create Date: 201
*/
void myHist::Accumulate(float fValue, float fCount){
	// check the bin index
	int iBinIndex = (int) ((fValue-m_fStart) / (m_fBinSize + m_fBinGap));

	// accmulate the histogram
	Accumulate(iBinIndex, fCount);
}// End of myHist::Accumulate

/* myHist::CalcHist
*
* Description: calculate the histogram given an image
*
* Programmer: poww
* Create Date: 2015.10.06
*/
void myHist::CalcHist(cv::Mat& image){
	if (m_iType != myHist::Type::Image){
		printf("myHist::CalcHist(): The histogram type should be Type::Image");
		return;
	}// End of if-condition

	for (int r = 0; r < image.rows; r++)
	for (int c = 0; c < image.cols; c++){
		int gray = image.at<uchar>(r, c);
		Accumulate(gray, 1.0);
	}// End of for-loop

	for (int i = 0; i < m_iBin; i++)
		printf("Bin %d: %f \n", i, m_Hist.at<float>(0, i));
}// End of myHist::CalcHist

/* myHist::Clear
*
* Description: clear the histogram
*
* Programmer: poww
* Create Date: 2015.08.07
*/
void myHist::Clear(void){
	m_Hist = cv::Scalar::all(0);
}// End of myHist::Clear


/* myHist::Normalize
*
* Description: normalize the histogram
*
* Programmer: poww
* Create Date: 2015.08.07
*/
void myHist::Normalize(void){
	// accmulate the sum
	float fSum = 0.0;
	for (int i = 0; i < m_Hist.cols; i++)
		fSum = fSum + m_Hist.at<float>(0, i);

	// check if the fSum == 0
	if (0.0 == fSum) return;

	for (int i = 0; i < m_Hist.cols; i++)
		m_Hist.at<float>(0, i) /= fSum;
}// End of myHist::Normalize

/* myHist::Show
*
* Description: Draw the histogram on the image
*
* Programmer: poww
* Create Date: 2011.08.27
*/  
void myHist::Show(cv::Mat& image, cv::Scalar color){
	// calcuate the bin width
	int binWidth = cvRound((double)image.cols / (double)m_iBin);

	// find the maximum and minimum values
	double min, max;
	cv::minMaxLoc(m_Hist, &min, &max);

	// draws bins
	for (int i = 0; i < m_iBin; i++){
		int binHeight = cvRound((double)m_Hist.at<float>(0, i) * (double)image.rows / max);
		printf("%d\n", binHeight);
		cv::rectangle(image,	cvPoint(i * binWidth,		image.rows - 1 - binHeight),
								cvPoint((i+1)*binWidth,	image.rows - 1),
					color, 1);
	}// End of for-loop
}// End of myHist::Show