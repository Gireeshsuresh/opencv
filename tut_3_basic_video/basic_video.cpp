#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>

using namespace cv;

int main(int argc, char const * argv[])
{	
	cv::VideoCapture videoCap;
	cv::namedWindow("basic video",0);
	videoCap.open(argv[1]);
	
	cv::Mat input_frame;

	for (;;)
	{
		if (input_frame.empty())
		{
			printf("No input file was given..\n");
			break;
		}
		cv::imshow("Video Display",input_frame);
		if (cv::waitKey(33)>=0)		
		{	
			break;
		}
	}
	return 0;
}

