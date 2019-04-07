#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <iostream>
#include<fstream>
#include <time.h>

using namespace cv;
using namespace std;

cv::Mat image;
cv::Mat result;
cv::Mat result_norm;
cv::Mat result_norm_scaled;

static int Threshold = 200;
int Max_threshold = 255;
clock_t start_time;
clock_t end_time;
ofstream Output;
std::string TimeCalcWithImWrite;
std::string TimeCalc;

void RunHarris(int,void*) {
	cv::cornerHarris(image, result, 2, 3, 0.04);
	cv::normalize(result, result_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	cv::convertScaleAbs(result_norm, result_norm_scaled);
	cout << "this is threshold:" << Threshold << endl;
	for (int j = 0; j < result_norm_scaled.rows; j = j + 1) {
		for (int i = 0; i < result_norm_scaled.cols; i = i + 1) {
			if ((int)result_norm.at<float>(j, i) > Threshold) {
				cv::circle(result_norm_scaled, cv::Point(i,j), 5, cv::Scalar(0), 2, 8, 0);
			}
		}
	}
	cv::namedWindow("Cornner by harris", WINDOW_NORMAL);
	cv::imshow("Cornner by harris", result_norm_scaled);

}



int main(void)
{

	image=cv::imread("DSC_0016.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	if (image.empty()) {
		std::cout << "Your App cant load an image." << std::endl;
		return -1;
	}
	cv::namedWindow("Input Pic", cv::WINDOW_GUI_NORMAL);
	cv::createTrackbar("Threshold for Harris", "Input Pic", &Threshold, Max_threshold, RunHarris);
	cv::imshow("Input Pic", image);
	RunHarris(0, 0);
	

	cv::waitKey(0);

	cv::destroyAllWindows();

	return 0;
}