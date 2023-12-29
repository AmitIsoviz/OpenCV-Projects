#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;



void main() {


	VideoCapture cap(1);
	Mat img;

	CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

	vector<Rect> plates;
	
	while (true) {
		cap.read(img);
		plateCascade.detectMultiScale(img, plates, 1.1, 10);
	

		for (int i = 0; i < plates.size(); i++)
		{
			Mat imgCrop = img(plates[i]);
			imwrite("Resources/plates/" + to_string(i)+".png",imgCrop);
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
		}

	imshow("Image", img);
	waitKey(1);

	}

}
