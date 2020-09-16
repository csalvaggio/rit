/** Interface file for computing a CDF from a histogram
 *
 *  \file ipcv/utils/HistogramToCdf.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 17 Mar 2018
 */

#pragma once

#include <opencv2/core.hpp>

namespace ipcv {

/** Compute the cumulative density function from a 3-channel image histogram
 *
 *  \param[in] h   the 3-channel image histogram
 *  \param[out] cdf the cumulative density for the supplied histogram
 */
void HistogramToCdf(const cv::Mat& h, cv::Mat& cdf);
}
