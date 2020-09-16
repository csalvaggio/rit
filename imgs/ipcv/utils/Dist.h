/** Interface file for the creation of a distance surface/function
 *
 *  \file ipcv/utils/Dist.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 18 Nov 2018
 */

#pragma once

#include <opencv2/core.hpp>

namespace ipcv {

/** Compute a distance surface/function
 *
 *  \param[in] rows   number of rows
 *  \param[in] cols   number of columns
 *  \param[in] shift  bool indicating whether to shift to upper left
 *
 *  \return           cv::Mat containing the computed distances
 */
cv::Mat Dist(const int rows, const int cols, bool shift = false);
}
