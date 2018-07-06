#include "opencv2/opencv.hpp"
// void basic_smoothing()

// int main()
// {
// 	basic_smoothing();
	
// }

void basic_smoothing(const cv::Mat & image)
{	
	// Window to show input and output
	cv::namedWindow("Input",0);
	cv::namedWindow("Output",0);

	//Create a window to show obtained input
	cv::imshow("Obtained Input", image);

	// Create a window to show the smoothed output
	cv::Mat out;
	cv::GaussianBlur(image,out,cv::Size(5,5),3,3);
	cv::GaussianBlur(out,out,cv::Size(5,5),3,3);

	cv::imshow("smoothed output", out);
	cv::waitKey(0);

}