/** Implementation file for finding Otsu's threshold
 *
 *  \file ipcv/otsus_threshold/OtsusThreshold.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 8 Sep 2018
 */

#include "OtsusThreshold.h"

#include <iostream>

#include "imgs/ipcv/utils/Utils.h"

using namespace std;

namespace ipcv {

/** Find Otsu's threshold for each channel of a 3-channel (color) image
 *
 *  \param[in] src          source cv::Mat of CV_8UC3
 *  \param[out] threshold   threshold values for each channel of a 3-channel
 *                          color image in cv::Vec3b
 */
bool OtsusThreshold(const cv::Mat& src, cv::Vec3b& threshold) {
  threshold = cv::Vec3b();

  // Insert your code here

  return true;
}
}
