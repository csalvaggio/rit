/** Interface file for shifting/quadrant exchange of a frequency spectrum
 *
 *  \file ipcv/utils/DftShift.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 03 Dec 2018
 */

#pragma once

#include <opencv2/core.hpp>

namespace ipcv {

/** Shift/quadrant exchange a complex-valued frequency spectrum
 *
 *  \param[in] spectrum   Frequency spectrum cv::Mat (CV_64FC2)
 *
 *  \return               cv::Mat (CV_64FC2) containing the shifted spectrum
 */
cv::Mat DftShift(const cv::Mat spectrum);
}
