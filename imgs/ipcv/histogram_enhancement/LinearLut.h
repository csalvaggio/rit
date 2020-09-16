/** Interface file for image enhancement using linear histogram statistics
 *
 *  \file ipcv/histogram_enhancement/LinearLut.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 3 Sep 2018
 */

#pragma once

#include <opencv2/core.hpp>

namespace ipcv {

/** Create a 3-channel (color) LUT using linear histogram enhancement
 *
 *  \param[in] src          source cv::Mat of CV_8UC3
 *  \param[in] percentage   the total percentage to remove from the tails
 *                          of the histogram to find the extremes of the
 *                          linear enhancemnt function
 *  \param[out] lut         3-channel look up table in cv::Mat(3, 256)
 */
bool LinearLut(const cv::Mat& src, const int percentage, cv::Mat& lut);
}
