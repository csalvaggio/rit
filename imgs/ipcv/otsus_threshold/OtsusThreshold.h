/** Interface file for finding Otsu's threshold
 *
 *  \file ipcv/otsus_threshold/OtsusThreshold.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 8 Sep 2018
 */

#pragma once

#include <opencv2/core.hpp>

namespace ipcv {

/** Find Otsu's threshold for each channel of a 3-channel (color) image
 *
 *  \param[in] src          source cv::Mat of CV_8UC3
 *  \param[out] threshold   threshold values for each channel of a 3-channel
 *                          color image in cv::Vec3b
 */
bool OtsusThreshold(const cv::Mat& src, cv::Vec3b& threshold);
}
