/** Implementation file for finding corner features using FAST
 *
 *  \file ipcv/corners/Fast.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 07 Nov 2018
 */

#include "Corners.h"

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"

using namespace std;

namespace ipcv {

/** Apply the FAST corner detector to a color image
 *
 *  \param[in] src     source cv::Mat of CV_8UC3
 *  \param[out] dst    destination cv:Mat of CV_8UC3
 *  \param[in] difference_threshold
 *                     brightness threshold to be used to determine whether
 *                     a surrounding pixels is brighter than or darker than
 *                     the candidate corner pixel
 *  \param[in] contiguous_threshold
 *                     number of contiguous pixels that must appear in
 *                     sequence in order for a candidate pixel to be
 *                     considered a corner pixel
 *  \param[in] nonmaximal_suppression
 *                     boolean parameter indicating whether non-maximal
 *                     suppression should be used to eliminate "clumping"
 *                     of identified corner points
 */
bool Fast(const cv::Mat& src, cv::Mat& dst, const int difference_threshold,
          const int contiguous_threshold, const bool nonmaximal_supression) {
  cv::Mat src_gray;
  cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);

  dst.create(src.size(), CV_8UC1);

  // Insert your code here

  return true;
}
}
