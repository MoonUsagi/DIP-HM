#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\core\core.hpp>

/* Class Name: myHist
*
* Description: It implements operations for histogram
*
* Programmer: poww
* Create Date: 2014.0812
*/
class myHist{
	// public fields
	public:
		enum class Type{
			Custom = 1,		// customized histogram
			Image,			// histogram for an image 		
		};// End of algorithm class

	// private fields
	private:
		myHist::Type	m_iType;// type of histogram

		int		m_iBin;			// number of bin
		float	m_fStart;		// the start value
		float	m_fBinSize;		// size of bin
		float	m_fBinGap;		// gap between bins
		cv::Mat	m_Hist;			// histogram

	// public constructor
	public:
		myHist(myHist::Type);
		myHist(float, float, float, int);		// constructor 
		~myHist();

	// public operations
	public:
		void	Accumulate(int, float=1.0);		// accumulate with bin number
		void	Accumulate(float, float = 1.0);	// accumulate with bin value

		void	CalcHist(cv::Mat&);				// calculate the histogram

		void	Clear(void);						// clear histogram

		void	Normalize(void);					// normalize the histogram

		void	Show(cv::Mat&, cv::Scalar = cv::Scalar(255,255,255));					// show the histogram
};// End of myHist class

