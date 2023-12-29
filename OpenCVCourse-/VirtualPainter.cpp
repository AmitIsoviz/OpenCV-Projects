#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat img;

// define camera
VideoCapture cap(1);

vector<vector<int>> newPoints; //{{x,y,0\1},{},...} while 0 is purple and 1 for pink 

vector<vector<int>> myColors{ {160,135,0,179,255,255}  //pink trackbars values
							,{111,51,0,158,255,255} }; //purple trackbars values

vector<Scalar> myColorValues{ {255,0,255}		//pink values to show 
							 ,{128,0,128} };	//purple HSV values to show 


Point getContours(Mat imgMask) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy; //for syntax we dont use the hierarchy

	findContours(imgMask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
	
	
	//--------------
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	Point myPoint(0, 0);


	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		//cout << area << endl;
		///string objectType;

		//fillter small shaps
		if (area > 1000)
		{
			float peri = arcLength(contours[i], true); 
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); //use peri to accurte
			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);

			//middle greed rect
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;


			//drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			
		}
	}
	return myPoint;
}


vector<vector<int>> findColor(Mat img) {
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	//find the range values and creat mask. then for each color and find the tip point
	for(int i = 0; i<myColors.size();i++)
	{

		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]); //(hmin, smin, vmin)
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]); //(hmax, smax, vmax)
		Mat mask;
		inRange(imgHSV, lower, upper, mask);

		//imshow("color number " +to_string(i), mask);
		
		//find the tip Point
		Point myPoint = getContours(mask);

		if (myPoint.x != 0 && myPoint.y != 0) {
			newPoints.push_back({ myPoint.x,myPoint.y,i });
		}
	}
	return newPoints;
}

void drawOnPic(vector<vector<int>> newPoints, vector<Scalar> myColorValues) {
	for (int i = 0; i < newPoints.size() ; i++)
	{
		circle(img, Point(newPoints[i][0],newPoints[i][1]), 10,myColorValues[newPoints[i][2]], FILLED);
	}
}

void main() {


	while (true) {
		cap.read(img);
		newPoints = findColor(img);
		drawOnPic(newPoints,myColorValues);
		imshow("Image", img);
		waitKey(1);

	}


}