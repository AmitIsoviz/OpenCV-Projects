#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

VideoCapture cap(0);

Mat img, imgHSV, mask;

//initialize max and min HSV values
int huemin = 0, satmin = 0, valmin = 0;
int huemax = 179, satmax = 255, valmax = 255;

void main(){

	
	//creat trackbars to check the colors values 
	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &huemin, 179);
	createTrackbar("Hue Max", "Trackbars", &huemax, 179);
	createTrackbar("Sat Min", "Trackbars", &satmin, 255);
	createTrackbar("Sat Max", "Trackbars", &satmax, 255);
	createTrackbar("Val Min", "Trackbars", &valmin, 255);
	createTrackbar("Val Mac", "Trackbars", &valmax, 255);


	while (true) {

		cap.read(img);
		imshow("Image",img);

		cvtColor(img, imgHSV, COLOR_BGR2HSV);
		imshow("ImageHSV", imgHSV);

		Scalar lower(huemin, satmin, valmin);
		Scalar upper(huemax, satmax, valmax);
		inRange(imgHSV, lower, upper, mask);
		imshow("Mask", mask);

		cout << huemin << "," << satmin << "," << valmin << "," << huemax <<
				"," << satmax << "," << valmax << endl;

		waitKey(1);
	}
}
