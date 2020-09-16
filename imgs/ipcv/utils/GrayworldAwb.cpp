/** Implementation file for performing AWB on image using gray world assumptions
 *
 *  \file ipcv/utils/GrayworldAwb.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 04 Jan 2019
 */

#include <iostream>

#include <opencv2/imgproc.hpp>

#include "GrayworldAwb.h"

using namespace std;

namespace ipcv {

cv::Mat GrayworldAwb(const cv::Mat& src, const double scale,
                     const int max_value) {  
  // Be certain that the source image is 3-channel
  if (src.channels() != 3) {
    cerr << "Automatic white balancing can only occur on color images" << endl;
    exit(EXIT_FAILURE);
  }

  // Be certain that the source image is either unsigned 8- or 16-bit
  int type = src.type();
  uchar depth = type & CV_MAT_DEPTH_MASK;
  if ((depth != CV_8U) && (depth != CV_16U)) {
    cerr << "Source image must be of either type CV_8U or CV_16U" << endl;
    exit(EXIT_FAILURE);
  }

  // Scale the input image to the range [0,1] and convert to a 32-bit
  // floating point type to be compatible with the OpenCV color conversion
  // routine
  cv::Mat src_normalized;
  src.convertTo(src_normalized, CV_32F, 1.0 / static_cast<float>(max_value));

  // Convert the BGR image to L*a*b*
  cv::Mat lab;
  cv::cvtColor(src_normalized, lab, cv::COLOR_BGR2Lab);

  // Split the L*a*b* channels
  cv::Mat channels[3];
  cv::split(lab, channels);

  // Compute the average a* and b* values
  cv::Scalar temp;
  temp = mean(channels[1]);
  float average_a = static_cast<float>(temp.val[0]);
  temp = mean(channels[2]);
  float average_b = static_cast<float>(temp.val[0]);

  // Compute the luminance-scaled shift values to force the average
  // a* and b* values to be 0 (neutral)
  cv::Mat delta_a = average_a * (channels[0] / 100.0) * scale;
  cv::Mat delta_b = average_b * (channels[0] / 100.0) * scale;

  // Shift the a* and b* values to the neutral position
  cv::Mat balanced_a = channels[1] - delta_a;
  cv::Mat balanced_b = channels[2] - delta_b;

  // Replace the original a* and b* values with their nuetral shifted
  // equivalents
  channels[1] = balanced_a;
  channels[2] = balanced_b;

  // Merge the modified L*a*b* channels
  cv::merge(channels, 3, lab);

  // Convert the balanced L*a*b* values back to BGR, this represents the
  // automatically white balanced image
  cv::Mat balanced;
  cv::cvtColor(lab, balanced, cv::COLOR_Lab2BGR);

  // Scale the balanced image back to the original dynamic range [0,max_value]
  balanced *= max_value;

  // Return the balanced image using the same data type as the original
  // input image
  cv::Mat dst;
  balanced.convertTo(dst, src.type());

  return dst;
}
}
