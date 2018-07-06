#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>

#include<iostream>
#include<string>

using namespace cv;

int main(int argc, char** argv)
{
	Mat image;
	String imageName("2.jpg");
	image = imread(imageName,IMREAD_COLOR);
	
	if (argc>1)
	{
		imageName = argv[1];
		return 0;
	}
	if (image.empty()) // If the file is not in the file path location mentioned above... 
	{
		printf("File is empty\n");
		return -1;	
	}
	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image);
	waitKey(0);
	return 0;
}

