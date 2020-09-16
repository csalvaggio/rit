#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "imgs/ipcv/utils/Utils.h"

using namespace std;

int main() {
  int rows = 512;
  int cols = 512;
  bool shift = false;

  cv::Mat distance = ipcv::Dist(rows, cols, shift);

  cv::Mat display;
  cv::normalize(distance, display, 0, 1, cv::NORM_MINMAX);

  double sigma = 30;
  cv::Mat exponent;
  cv::multiply(distance, distance, exponent);
  exponent = -0.5 * exponent / sigma / sigma;
  cv::Mat gaussian;
  cv::exp(exponent, gaussian);

  cv::imshow("Distance", display);
  cv::imshow("Gaussian", gaussian);
  cv::waitKey(0);

  return EXIT_SUCCESS;
}
