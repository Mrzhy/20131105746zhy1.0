#include "stdafx.h"
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\video\background_segm.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
using namespace cv;

void detectAndDisplay(Mat frame);
String face_cascade_name = "D:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;
string window_name = "Face detection";

int main(void)
{
//-- 1. Load the cascade

	if (!face_cascade.load(face_cascade_name))
	{
		printf("--(!)Error loading\n");
		return -1;
	};
//-- 2. Read the image
	IplImage* img = cvLoadImage("D:\\≤‚ ‘\\test4\\face.jpg", CV_LOAD_IMAGE_COLOR);
	Mat frame(img);
//-- 3. Apply the classifier to the frame
	if (!frame.empty())
	{
		detectAndDisplay(frame);
 
	}
	else
	{
 
		printf("--(!)Error!\n");
 
	}
	waitKey(0);
	cvDestroyWindow(window_name.c_str());
	cvReleaseImage(&img); 
	return 0;
 
}

void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;
 
	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
//-- Detect faces
	double t = (double)cvGetTickCount();
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	t = (double)cvGetTickCount() - t;
	printf("%gms\n", t / ((double)cvGetTickFrequency()*1000.0));
 
	for (size_t i = 0; i < faces.size(); i++)
	{
 
	Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
	printf("Found a face at (%d, %d)\n", center.x, center.y);
	ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 255, 255), 2, 8, 0);
 
	}
//-- Show what you got
	imshow(window_name, frame);
 
}