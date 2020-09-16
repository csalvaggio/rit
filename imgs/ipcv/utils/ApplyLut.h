/** Interface file for applying a 3-channel LUT
 *
 *  \file ipcv/utils/Histogram.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 3 Sep 2018
 */

#pragma once

#include <opencv2/core.hpp>

namespace ipcv {

/** Implementation file for applying a 3-channel LUT
 *  
 *  \param[in] src   source cv::Mat of CV_8UC3
 *  \param[in] lut   the look up table (cv:Mat) to apply to the source image
 *  \param[out] dst  destination cv:Mat of CV_8UC3
 */
bool ApplyLut(const cv::Mat& src, const cv::Mat &lut, cv::Mat& dst);
}
