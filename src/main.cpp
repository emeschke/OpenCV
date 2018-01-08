#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

//OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

double ccf(Mat& img1, Mat& img2);

int main( int argc, const char** argv)
{
	//Read image in color and in gray.  This reads in a zero-based matrix object (channels, height/rows x width/cols)
	Mat color = imread("./EMeschke.jpg");
	Mat gray = imread("./EMeschke.jpg", 0);
	
	//Get the size and channels of the two images; we will work with Gray since it is one channel
	cout << "Color: " << color.size << "; " << color.channels() << endl;
	cout << "Gray: " << gray.size << "; " << gray.channels() << endl;

	//Get the center of the photo and the width/height of a rectangle.
	Point center(gray.rows/2, gray.cols/2); 	
	cout << "Point " << center << " is the center." << endl;	
	
	//Cut a 1/6 x 1/6 square out of the image	
	int boxWidth = (gray.cols/6);
	int boxHeight = (gray.rows/6);
		
	//Rect rect(0,100, 200, 100);	
	Rect rect(center.x - boxWidth/2, center.y - boxHeight/2, boxWidth, boxHeight);
	Mat cropped = gray(rect);

	//Get the rotation
	Mat matRotation = getRotationMatrix2D( Point(center.x, center.y), -20, 1 ); 
	
	// Rotate the gray image 20 degrees clockwise
        Mat grayRotated;
        warpAffine(gray, grayRotated, matRotation, gray.size() );	

	//Crop the rotated image similarly to the original image
	Mat grayRotatedCropped = grayRotated(rect);
	//cout << grayRotatedCropped << endl;
	
	//Print some pictures
	//imshow( "Display window", gray );
	imshow("Second Window", cropped);
	//imshow("Third Window", grayRotated);
	imshow("Fourth Window", grayRotatedCropped);
	
	double corr1 = ccf(cropped, cropped);
	double corr2 = ccf(cropped, grayRotatedCropped);
	

	cout << "Correlation of same images is: " << corr1 << endl;
	cout << "Correlation of rotated and normal image is: " << corr2 << endl;
	
	//Wait for any key press
	waitKey(0);

	return 0;
}

//Create a function to get the correlation of the two images.
double ccf(Mat& img1, Mat& img2)
{
	
	//First check that image patches are the same size.
	//Both a good idea, and also I am being hacky with the iterator below so necessary.
	assert (img1.cols*img1.rows == img2.cols*img2.rows);	

	//Create and set to zero summary statistics
	double avg1 = 0, avg2 = 0;
	double cov = 0, var1 = 0, var2 = 0;	
	double corr;
	int n = img1.cols*img1.rows;

	//Create and initialize iterators to beginning and end of images.
	MatIterator_<uchar> it1, it2, end1, end2;
	it1 = img1.begin<uchar>(); 
	it2 = img2.begin<uchar>();
	end1 = img1.end<uchar>();
	end2 = img2.end<uchar>();

	//Our loop iterates through image1 and image2, calculating a rolling sum over each image.
	while (it1 != end1  && it2 != end2)
	{
		avg1 += *it1;
		avg2 += *it2;
		it1++;
		it2++;
	}

	//Divide sum by n (count of pixels) to get average.
	avg1 = avg1/(img1.cols*img1.rows);
	avg2 = avg2/(img2.cols*img2.rows);

	//Re-initialize iterators
	it1 = img1.begin<uchar>(); 
	it2 = img2.begin<uchar>();

	//Calculate sum of squares
	while (it1 != end1  && it2 != end2)
	{
		cov += (*it1 - avg1)*(*it2 - avg2);
		var1 += (*it1 - avg1)*(*it1 - avg1);
		var2 += (*it2 - avg2)*(*it2 - avg2);
		it1++;
		it2++;
	}

	//Divide sum of square by n to get cov/var
	cov = cov/n;
	var1 = var1/n;
	var2 = var2/n;
	
	//Normalize cov by stdevs to find correlation
	corr = cov/(sqrt(var1)*sqrt(var2));

	return corr;

}	
