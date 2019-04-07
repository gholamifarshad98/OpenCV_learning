#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
	
	Mat image;
	image = imread("DSC_0016.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file

	if (!image.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	//namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", image);                   // Show our image inside it.
	waitKey(5000);                                          // Wait for a keystroke in the window
	cv::destroyAllWindows();
	std::cout << "hello" << std::endl;
	std::cout << "hello1" << std::endl;


	return 0;
}