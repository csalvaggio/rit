/** Implementation file for bilateral filtering
 *
 *  \file ipcv/bilateral_filtering/BilateralFilter.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 29 Sep 2018
 */

#include "BilateralFilter.h"

#include <iostream>

using namespace std;

namespace ipcv {

/** Bilateral filter an image
 *
 *  \param[in] src             source cv::Mat of CV_8UC3
 *  \param[out] dst            destination cv::Mat of ddepth type
 *  \param[in] sigma_distance  standard deviation of distance/closeness filter
 *  \param[in] sigma_range     standard deviation of range/similarity filter
 *  \param[in] radius          radius of the bilateral filter (if negative, use
 *                             twice the standard deviation of the distance/
 *                             closeness filter)
 *  \param[in] border_mode     pixel extrapolation method
 *  \param[in] border_value    value to use for constant border mode
 */
bool BilateralFilter(const cv::Mat& src, cv::Mat& dst,
                     const double sigma_distance, const double sigma_range,
                     const int radius, const BorderMode border_mode,
                     uint8_t border_value) {
  dst.create(src.size(), src.type());

  // Insert your code here

  return true;
}
}
