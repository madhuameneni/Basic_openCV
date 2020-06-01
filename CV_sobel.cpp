#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "Basic_openCV.h"

#define w 400
Mat img;

using namespace cv;
class basicCV basic;
void shapes();
void smoothening();
Mat captureImage();
void erosion_dilation();
void morphology_Operations();
void morphology_Operations_horizontal_vertical();
void imag_pyramid();
void basic_threshold();

//void random();


int main (void) {
	//shapes(); // contains basic shapes like cirlce, eclipse, rectangle etc.
	//random();
	//smoothening();
	//erosion_dilation();
	//morphology_Operations();
	//morphology_Operations_horizontal_vertical();
	//imag_pyramid();
	basic_threshold();
	waitKey(0);
	return(0);
}

void shapes() {
	char atom_window[] = "Drawing an satelite rotation around Mars";
	Mat atom_image = Mat::zeros(w, w, CV_8UC3);
	basic.MyEllipse(atom_image, 90, w);
	basic.MyEllipse(atom_image, 0, w);
	basic.MyEllipse(atom_image, 45, w);
	basic.MyEllipse(atom_image, -45, w);
	basic.myCircle(atom_image, Point(w / 2, w / 2), w);
	basic.myRectangle(atom_image, Point(0, 7 * w / 8), Point(w, w), w);
	basic.myLine(atom_image, Point(w / 4, 7 * w / 8), Point(3 * w / 4, 7 * w / 8));
	basic.myLine(atom_image, Point(w / 4, 7 * w / 8), Point(w / 4, w));
	basic.myLine(atom_image, Point(w / 2, 7 * w / 8), Point(w / 2, w));
	basic.myLine(atom_image, Point(3 * w / 4, 7 * w / 8), Point(3 * w / 4, w));
	imshow(atom_window, atom_image);
	moveWindow(atom_window, 0, 200);
}

void smoothening()
{
	char window[] = "smoothing the captured image based on the kernal size";
	basic.smoothening(captureImage(), 20, window);
}

Mat captureImage()
{
	VideoCapture cap(0);
	cap.open(0);
	cap >> img;
	resize(img, img, Size(500, 500));
	return img;
}

void erosion_dilation()
{
	char window_erosion_dilation[] = "ërrosion and dilation of a captured image";
	basic.myerosion_dilation(captureImage(), 1, window_erosion_dilation);
}

void morphology_Operations()
{
	char window_morphology_Operations[] = "morphology Operations of a captured image";
	basic.morphology_Operations(captureImage(), 1, window_morphology_Operations);
}

void morphology_Operations_horizontal_vertical()
{
	char window_morphology_Operations_horizontal_vertical[] = "morphology Operations of a captured image extracting horizontal and vertical data in a image";
	basic.morphology_Operations_horizontal_vertical(captureImage(), window_morphology_Operations_horizontal_vertical);
}

void imag_pyramid()
{
	char window_imag_pyramid[] = "morphology Operations of a captured image extracting horizontal and vertical data in a image";
	basic.image_pyramid(captureImage(), window_imag_pyramid);
}

void basic_threshold()
{
	char window_threshold[] = "Basic thresholding operations";
	basic.threshold_image(captureImage(), window_threshold, 95);
}

//void random()
//{
//	char random_window[] = "Drawing a random shapes ";
//	Mat image = Mat::zeros(w, w, CV_8UC3);
//	imshow(random_window, image);
//	basic.display_RandomFunction(image, random_window, rng);
//}
