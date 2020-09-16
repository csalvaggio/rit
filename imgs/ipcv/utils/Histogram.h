/** Interface file for computing an image histogram
 *
 *  \file ipcv/utils/Histogram.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 17 Mar 2018
 */

#pragma once

#include <opencv2/core.hpp>

namespace ipcv {

/** Compute the 3-channel image histogram of the provided source image
 *
 *  \param[in] src  source cv::Mat of CV_8UC3
 *  \param[out] h   the grey-level histogram for the source image
 */
void Histogram(const cv::Mat& src, cv::Mat& h);
}
