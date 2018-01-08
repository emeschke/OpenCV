#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;

int main(int argc, char ** argv)
{
    // Load an image
cv::Mat inputImage = cv::imread(argv[argc-1], 0);

// Go float
cv::Mat fImage;
inputImage.convertTo(fImage, CV_32F);

// FFT
std::cout << "Direct transform...\n";
cv::Mat fourierTransform;
cv::dft(fImage, fourierTransform, cv::DFT_SCALE|cv::DFT_COMPLEX_OUTPUT);

// Some processing
//doSomethingWithTheSpectrum();

// IFFT
std::cout << "Inverse transform...\n";
cv::Mat inverseTransform;
cv::dft(fourierTransform, inverseTransform, cv::DFT_INVERSE|cv::DFT_REAL_OUTPUT);

// Back to 8-bits
cv::Mat finalImage;
inverseTransform.convertTo(finalImage, CV_8U);

cv::imshow("Input Image"       , fImage   );    // Show the result
cv::imshow("spectrum magnitude", inverseTransform);
cv::waitKey();

return 0;
}