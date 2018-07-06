#include<stdio.h>
#include<opencv2/opencv.hpp>
using namespace cv;
int main(int argc, char** argv)
{

/*	if(argc <= 1)
	{
		printf("usage: DisplayImage.out <Image_Path>\n");
		return -1;
	}
*/
	Mat image;
	if (argc>1)
	{
		image = imread( argv[1],1);
	}
	if (image.empty())
	{
		printf(" Image is empty. No data found \n");
	}
	if (!image.data)
	{
	printf(" No image data found \n");
	return -1;
	}
	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image);
	waitKey(0);
	return 0;
}

