#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <iostream>
#include<fstream>
#include <time.h>

using namespace cv;
using namespace std;

const int MaxThreshold = 100;
const int ratio = 3;
const int KernelSize = 3;
const char* NameOfResultWin = "Edge Map";
static int lowThreshold;
cv::Mat result;
cv::Mat image;
static bool getCannyResults=false;
void CannyThreshold(int, void*);
clock_t start_time;
clock_t end_time;
ofstream Output;
std::string TimeCalcWithImWrite;
std::string TimeCalc;


void MyImRead(void) {
	image = imread("DSC_0016.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)                           
	{
		cout << "Could not open or find the image" << std::endl;
	}
	lowThreshold = 50;
	CannyThreshold;
	namedWindow("DisplayWindow", WINDOW_NORMAL);
	createTrackbar("My Test", "DisplayWindow", &lowThreshold, 100, CannyThreshold);
	imshow("DisplayWindow", image);
	waitKey(0);
}


void CannyThreshold(int, void* ) {
	cv::blur(image,result,cv::Size(3,3),cv::Point(-1,-1));
	cv::Canny(result, result, lowThreshold, lowThreshold*ratio, 3);
	namedWindow(NameOfResultWin, WINDOW_NORMAL);
	cv::imshow(NameOfResultWin,result);

	if (getCannyResults == false) {
		start_time = clock();;
		for (int i = 10; i <= 100; i = i + 10) {
			cv::blur(image, result, cv::Size(3, 3), cv::Point(-1, -1));
			cv::Canny(result, result, i, lowThreshold*ratio, 3);
			std::string resultName = "result_canny_";
			resultName = resultName + std::to_string(i) + ".jpg";
		}
		end_time = clock();
		Output.open("TimeResults.txt");
		TimeCalc = "Calculation for 10 pic with writing image time is " + to_string(end_time - start_time) + "ms";
		Output << TimeCalc << endl;
		//Output.close();
		start_time = clock();;
		for (int i = 10; i <= 100; i = i + 10) {
			cv::blur(image, result, cv::Size(3, 3), cv::Point(-1, -1));
			cv::Canny(result, result, i, lowThreshold*ratio, 3);
			std::string resultName = "result_canny_";
			resultName = resultName + std::to_string(i) + ".jpg";
			cv::imwrite(resultName, result);
		}
		end_time = clock();
		TimeCalcWithImWrite = "Calculation for 10 pic with writing image time is " + to_string(end_time - start_time) + "ms";
		Output << TimeCalcWithImWrite << endl;
		Output.close();
		getCannyResults = true;
	}
}

int main(void)
{
	MyImRead();
	cv::destroyAllWindows();

	return 0;
}