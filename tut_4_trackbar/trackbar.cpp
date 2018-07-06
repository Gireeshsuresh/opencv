#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>

using namespace std;
 int g_slider_position=0;
 int g_run=1;
 int g_dontset=0;

 cv::VideoCapture g_cap;

void onTrackbarSlide(int pos, void *)
{
	g_cap.set(cv::CAP_PROP_POS_FRAMES,pos);
		if (!g_dontset)
		{
			g_run = 1;
		}
	g_dontset=0;
}

int main(int argc, char** argv)
{
	cv::namedWindow("Example_trackbar", cv::WINDOW_AUTOSIZE );
	g_cap.open(argv[1]);

	int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT);
	int tmp_w = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int tmp_h = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);

	cout << "Video has " << frames << " frames" << ". The Frames have the dimension = ("<< tmp_w << " x " << tmp_h <<")." << endl;

	cv::createTrackbar("Position","Example_trackbar",&g_slider_position,frames,onTrackbarSlide);

	cv::Mat frame;
	for(;;)
	{
		if(g_run!=0)
		{
			g_cap >>frame ;
			if (frame.empty())break;
			int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
			g_dontset = 1;

			cv::setTrackbarPos("Position","Example_trackbar",current_pos);
			cv::imshow("Example_trackbar",frame);

			g_run -= 1;
		}
		char c = (char) cv::waitKey(10);
		if (c=='s')
		{
			g_run = 1;cout << "Single Step,run = " << g_run << endl;
		}
		if (c=='r')
		{
			g_run = -1; cout<<"Run mode, run = " << g_run << endl;
		}
		if (c==27)
		{
			break;
		}
	}
	return(0);
}