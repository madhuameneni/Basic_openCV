#include "Basic_openCV.h" 
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;
Mat dst;
double max_binary_value = 255;
enum erosion_dilation1 { MORPH_RECT, MORPH_CROSS, MORPH_ELLIPSE, end };

void basicCV::myLine(Mat img, Point p1, Point p2) {
    int thickness = 2;
    int lineType = LINE_8;
    line(img,
        p1,
        p2,
        Scalar(0, 0, 0),
        thickness,
        lineType);
}

void basicCV::MyEllipse(Mat img, double angle, int w){
    int thickness = 2;
    int lineType = 8;
    ellipse(img,
        Point(w / 2, w / 2),
        Size(w / 4, w / 16),
        angle,
        0,
        360,
        Scalar(255, 0, 0),
        thickness,
        lineType);
}

void basicCV::myCircle(Mat img, Point center, int w)
{
    circle(img,
        center,
        w / 32,
        Scalar(0, 0, 255),
        FILLED,
        LINE_8);
}

void basicCV::myRectangle(Mat img, Point p1, Point p2, int w)
{
    rectangle(img,
        Point(0, 7 * w / 8),
        Point(w, w),
        Scalar(0, 255, 0),
        FILLED,
        LINE_8);
}

int basicCV::smoothening(Mat src, int size, char* window_name)
{
    if (display_caption("Original Image", src, window_name) != 0)
    {
        return 0;
    }
    dst = src.clone();
    if (display_dst(DELAY_CAPTION, window_name) != 0)
    {
        return 0;
    }
    if (display_caption("Homogeneous Blur", src, window_name) != 0)
    {
        return 0;
    }
    for (int i = 1; i < size; i = i + 2)
    {
        blur(src, dst, Size(i, i), Point(-1, -1));
        if (display_dst(DELAY_BLUR, window_name) != 0)
        {
            return 0;
        }
    }
    if (display_caption("Gaussian Blur", src, window_name) != 0)
    {
        return 0;
    }
    for (int i = 1; i < size; i = i + 2)
    {
        GaussianBlur(src, dst, Size(i, i), 0, 0);
        if (display_dst(DELAY_BLUR, window_name) != 0)
        {
            return 0;
        }
    }
    if (display_caption("Median Blur", src, window_name) != 0)
    {
        return 0;
    }
    for (int i = 1; i < size; i = i + 2)
    {
        medianBlur(src, dst, i);
        if (display_dst(DELAY_BLUR, window_name) != 0)
        {
            return 0;
        }
    }
    if (display_caption("Bilateral Blur", src, window_name) != 0)
    {
        return 0;
    }
    for (int i = 1; i < size; i = i + 2)
    {
        bilateralFilter(src, dst, i, i * 2, i / 2);
        if (display_dst(DELAY_BLUR, window_name) != 0)
        {
            return 0;
        }
    }
    display_caption("Done!", src, window_name);
    return 0;
}



//void basicCV::display_RandomFunction(Mat image, char* window_name, RNG rng)
//{
//    int lineType = 8;
//    Point pt1, pt2;
//    for (int i = 0; i < 50; i++)
//    {
//        pt1.x = rng.uniform(x_1, x_2);
//        pt1.y = rng.uniform(y_1, y_2);
//        pt2.x = rng.uniform(x_1, x_2);
//        pt2.y = rng.uniform(y_1, y_2);
//        int icolor = (unsigned)rng;
//        line(image, pt1, pt2, Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255), rng.uniform(1, 10), 8);
//        imshow(window_name, image);
//    }
//
//}

 /*Scalar basicCV::randomColor(RNG& rng)
{
    int icolor = (unsigned)rng;
    return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}*/


int basicCV::display_caption(const char* caption, Mat src, char* window_name)
{
    dst = Mat::zeros(src.size(), src.type());
    putText(dst, caption,
    Point(src.cols / 4, src.rows / 2),
    FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
    return display_dst(DELAY_CAPTION, window_name);
}

int basicCV::display_dst(int delay, char* window_name)
{
    imshow(window_name, dst);
    int c = waitKey(delay);
    if (c >= 0) { return -1; }
    return 0;
}

void basicCV::myerosion_dilation(Mat src, int size, char* window_name)
{
    int type = 0;
    for (int i = ::MORPH_RECT; i != erosion_dilation1::end; i++)
    {
        display_src(DELAY_CAPTION, window_name, src);
        erosion_dilation1 foo = static_cast<erosion_dilation1>(i);
        Mat element = getStructuringElement(type = foo,
            Size(2 * size + 1, 2 * size + 1),
            Point(size, size));
        erode(src, dst, element);
        imshow("Erosion Demo", dst);
    }
    for (int i = erosion_dilation1::MORPH_RECT; i != erosion_dilation1::end; i++)
    {
        display_src(DELAY_CAPTION, window_name, src);
        erosion_dilation1 foo = static_cast<erosion_dilation1>(i);
        Mat element = getStructuringElement(type = foo,
            Size(2 * size + 1, 2 * size + 1),
            Point(size, size));
        dilate(src, dst, element);
        imshow("Dilation Demo", dst);
    }
}

void basicCV::morphology_Operations(Mat src, int size, char* window_name)
{
    enum morphology_Operations1 { MORPH_OPEN, MORPH_CLOSE , MORPH_GRADIENT , MORPH_TOPHAT , MORPH_BLACKHAT , end};
    for (int morph_type = MORPH_OPEN; morph_type != end; morph_type++)
    {
        for (int i = erosion_dilation1::MORPH_RECT; i != erosion_dilation1::end; i++)
        {
            display_src(DELAY_CAPTION, window_name, src);
            erosion_dilation1 foo = static_cast<erosion_dilation1>(i);
            int operation = morph_type + 2;
            Mat element = getStructuringElement(foo, Size(2 * size + 1, 2 * size + 1), Point(size, size));
            morphologyEx(src, dst, operation, element);
            imshow(window_name, dst);
        }
    }
}

void basicCV::morphology_Operations_horizontal_vertical(Mat src, char* window_name)
{
   src =  check_gray(src, window_name);
   show_wait_destroy("binary", src);
   Mat horizontal = src.clone();
   Mat vertical = src.clone();
   int horizontal_size = horizontal.cols / 30;
   Mat horizontalStructure = getStructuringElement(0, Size(horizontal_size, 1));
   erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
   dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));
   show_wait_destroy("horizontal", horizontal);
   int vertical_size = vertical.rows / 30;
   Mat verticalStructure = getStructuringElement(0, Size(1, vertical_size));
   erode(vertical, vertical, verticalStructure, Point(-1, -1));
   dilate(vertical, vertical, verticalStructure, Point(-1, -1));
   show_wait_destroy("vertical", vertical);
   bitwise_not(vertical, vertical);
   show_wait_destroy("vertical_bit", vertical);
   Mat edges;
   adaptiveThreshold(vertical, edges, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, -2);
   show_wait_destroy("edges", edges);
   Mat kernel = Mat::ones(2, 2, CV_8UC1);
   dilate(edges, edges, kernel);
   show_wait_destroy("dilate", edges);
   Mat smooth;
   vertical.copyTo(smooth);
   blur(smooth, smooth, Size(2, 2));
   smooth.copyTo(vertical, edges);
   show_wait_destroy("smooth - final", vertical);
}

Mat basicCV::check_gray(Mat src, char* window_name)
{
    if (src.channels() == 3)
    {
        cvtColor(src, src, COLOR_BGR2GRAY);
        //show_wait_destroy(window_name, src);
        return src;
    }
    else
    {
        return src;
    }
}

void basicCV::show_wait_destroy(const char* winname, cv::Mat img)
{
    imshow(winname, img);
    moveWindow(winname, 500, 0);
    waitKey(0);
    destroyWindow(winname);
}

void basicCV::image_pyramid(Mat src, char* window_name)
{
   // display_dst(DELAY_CAPTION, window_name);
    imshow(window_name, src);
    pyrUp(src, src, Size(src.cols * 2, src.rows * 2));
    imshow(window_name, src);
    pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
    imshow(window_name, src);
}

void basicCV::threshold_image(Mat src, char* window_name, int threshold_value)
{
    src = check_gray(src, window_name);
    for (int i = 0; i < 5; i++) {
        threshold(src, dst, threshold_value, max_binary_value, i);
        display_src(DELAY_CAPTION, window_name, src);
    }
}

int basicCV::display_src(int delay, char* window_name, Mat src)
{
    imshow(window_name, src);
    int c = waitKey(delay);
    if (c >= 0) { return -1; }
    return 0;
}




