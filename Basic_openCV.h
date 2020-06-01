#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
class basicCV {
public :
	void myLine(Mat img, Point p1, Point p2);
	void MyEllipse(Mat img, double angle, int w);
	void myCircle(Mat img, Point center, int w);
	void myRectangle(Mat img, Point p1, Point p2, int w);
	/*void display_RandomFunction(Mat image, char* window_name, RNG rng);
	Scalar randomColor(RNG& rng);*/
	int smoothening(Mat src, int size, char* window_name);
	int display_caption(const char* caption, Mat src, char* window_name);
	int display_dst(int delay, char* window_name);
	void myerosion_dilation(Mat src, int size, char* window_name);
	void morphology_Operations(Mat src, int size, char* window_name);
	void morphology_Operations_horizontal_vertical(Mat src, char* window_name);
	Mat check_gray(Mat src, char* window_name);
	void show_wait_destroy(const char* winname, cv::Mat img);
	void image_pyramid(Mat src, char* window_name);
	void threshold_image(Mat src, char* window_name, int threshold_value);
	int display_src(int delay, char* window_name, Mat src);
};
