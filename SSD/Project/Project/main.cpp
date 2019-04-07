#include <iostream>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
Mat MySSD(Mat &, Mat &, int, int, int, int);
int main() {
	Mat leftImage = imread("view0.png", 0);
	Mat rightImage = imread("view1.png", 0);
	if (leftImage.empty() || rightImage.empty()) {
		cout << "Error in reading Left or right image" << endl;
	}
	int ro;
	int co;
	co = leftImage.cols;
	ro = leftImage.rows;
	Mat Disparity;
	leftImage.at<uchar>(ro - 5, co - 9) = 255;


	Disparity = MySSD(leftImage, rightImage, 6, 30, ro, co);
	imshow("left Image", leftImage);
	imshow("right Image", rightImage);
	imshow("Disparity Image", Disparity);
	cout << "Width is ===>" << co << " and Hight is ====> " << ro << endl;
	waitKey(0);

	return 0;
}


Mat MySSD(Mat &left, Mat &right, int win, int MaxOffset, int ro, int co) {
	int halfWin = int(win / 2);

	Mat result(ro, co, CV_8UC1, Scalar(255));

	for (int i = halfWin; i < ro - halfWin; ++i) {
		for (int j = halfWin; j < co - halfWin; ++j) {
			int ssd_reserved = 9999635;
			int bestOffset = 0;
			double offset_adjust = 255 / MaxOffset;
			for (int offset = 0; offset <= MaxOffset; ++offset) {
				int ssd = 0;
				int ssdTemp = 0;
				for (int u = -halfWin; u <= halfWin; u++) {
					for (int v = -halfWin; v <= halfWin; v++) {
						ssdTemp = (left.at<uchar>((i + u), (j + v)) - right.at<uchar>((i + u), (j + v - offset)));
						ssdTemp = ssdTemp*ssdTemp;
						ssd = ssd + ssdTemp;
					}
				}
				if (ssd < ssd_reserved) {
					bestOffset = offset;
					ssd_reserved = ssd;

				}
			}
			result.at<uchar>(i, j) = bestOffset* offset_adjust;
		}
	}
	return result;
}