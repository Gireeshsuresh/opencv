#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int edgeThresh = 1;
int lowThreshold = 10;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
const char *window_name = "Edge Map";

int ct = 0;
char userInput;
char filename[100]; // For filename
int c = 1;          // For filename

Mat source, destination, det_edges, grayImg;
int thresh = 100, max_thresh = 255;
RNG rng(12345);

void thresh_callback(int, void **);

static void CannyThreshold(int, void *)
{
    blur(grayImg, det_edges, Size(3, 3));
    Canny(det_edges, det_edges, lowThreshold, lowThreshold * ratio, kernel_size);
    destination = Scalar::all(0);
    source.copyTo(destination, det_edges);
    imshow(window_name, destination);
    imshow("window_name", det_edges);
}

int main(int, char **argv)
{

    Mat frame;

    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;           // open the default camera using default API
    cap.open(0);                // OR advance usage: select any API backend
    int deviceID = 0;           // 0 = open default camera
    int apiID = cv::CAP_ANY;    // 0 = autodetect default API
                                // open selected camera using selected API
    cap.open(deviceID + apiID); // check if we succeeded
    if (!cap.isOpened())
    {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    //--- GRAB AND WRITE LOOP
    cout << "Program Started.." << endl
         << "Press \"a\" to terminate" << endl
         << "Press \"q\" to grab an Image " << endl;
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);

        if (frame.empty())
        {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        imshow("Live Camera Feed ", frame); // Window name
        source = frame;
        destination.create(source.size(), source.type());
        cvtColor(source, grayImg, COLOR_BGR2GRAY);
        namedWindow(window_name, WINDOW_AUTOSIZE);
        createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
        CannyThreshold(0, 0);

        createTrackbar(" Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);
        thresh_callback(0, 0);

        userInput = cv::waitKey(5);
        if (userInput == 'q')
        {
            imwrite("SampleGrabImg.jpg", frame); // select your folder - filename is "Frame_n"
            cv::waitKey(5);

            imshow("Captured Image", frame);
            cout << " ----------- Image Captured --------" << endl;
            cout << " Press \"q\" to take a new pic , \"a\" to exit..." << endl;
            cout << " -----------------------------------\n"
                 << endl;
            waitKey(2);
        }
        if (userInput == 'a')
        {
            cout << "Terminating..." << endl;
            // Sleep(2000);
            break;
        }
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}


void thresh_callback(int, void*)
{
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    Canny(grayImg, canny_output, thresh, thresh * 2, 3);
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point());
    }
    namedWindow("Contours", WINDOW_AUTOSIZE);
    imshow("Contours", drawing);
}

// #include <opencv2/viz.hpp>
// #include <opencv2/calib3d.hpp>
// #include <iostream>
// using namespace cv;
// using namespace std;
// static void help()
// {
//     cout
//     << "--------------------------------------------------------------------------"   << endl
//     << "This program shows how to visualize a cube rotated around (1,1,1) and shifted "
//     << "using Rodrigues vector."                                                      << endl
//     << "Usage:"                                                                       << endl
//     << "./widget_pose"                                                                << endl
//     << endl;
// }
// int main()
// {
//     help();
//     viz::Viz3d myWindow("Coordinate Frame");
//     myWindow.showWidget("Coordinate Widget", viz::WCoordinateSystem());
//     viz::WLine axis(Point3f(-1.0f,-1.0f,-1.0f), Point3f(1.0f,1.0f,1.0f));
//     axis.setRenderingProperty(viz::LINE_WIDTH, 4.0);
//     myWindow.showWidget("Line Widget", axis);
//     viz::WCube cube_widget(Point3f(0.5,0.5,0.0), Point3f(0.0,0.0,-0.5), true, viz::Color::blue());
//     cube_widget.setRenderingProperty(viz::LINE_WIDTH, 4.0);
//     myWindow.showWidget("Cube Widget", cube_widget);
//     Mat rot_vec = Mat::zeros(1,3,CV_32F);
//     float translation_phase = 0.0, translation = 0.0;
//     while(!myWindow.wasStopped())
//     {
//         /* Rotation using rodrigues */
//         rot_vec.at<float>(0,0) += (float)CV_PI * 0.01f;
//         rot_vec.at<float>(0,1) += (float)CV_PI * 0.01f;
//         rot_vec.at<float>(0,2) += (float)CV_PI * 0.01f;
//         translation_phase += (float)CV_PI * 0.01f;
//         translation = sin(translation_phase);
//         Mat rot_mat;
//         Rodrigues(rot_vec, rot_mat);
//         Affine3f pose(rot_mat, Vec3f(translation, translation, translation));
//         myWindow.setWidgetPose("Cube Widget", pose);
//         myWindow.spinOnce(1, true);
//     }
//     return 0;
// }
