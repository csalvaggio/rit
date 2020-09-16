/** Interface file for multiplying a spectrum by a mask/filter             
 *
 *  \file ipcv/utils/DftMultiply.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 04 Dec 2018
 */

#pragma once

#include <opencv2/core.hpp>

namespace ipcv {

/** Compute the product of a spectrum and a filter
 *
 *  \param[in] spectrum   Frequency spectrum cv::Mat (CV_64FC2)
 *  \param[in] filter     Filter/mask cv::Mat (CV_64FC1)
 *
 *  \return               cv::Mat (CV_64FC2) containing the product
 */
cv::Mat DftMultiply(const cv::Mat spectrum, const cv::Mat filter);
}
