/** Interface file for computing the 2D DFT of a matrix
 *
 *  \file ipcv/utils/Dft2.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 05 November 2020
 */

#pragma once

#include <complex>

#include <opencv2/core.hpp>

#include "Dft.h"

namespace ipcv {

/** Compute the 2D DFT of a cv::Mat
 *
 *  \param[in] f     function of type cv::Mat (M x N)
 *  \param[in] flag  bitwise options flag (see enum in Dft.h)
 *                     1 - inverse transform should occur
 *                     2 - scaling should occur
 *
 *  \return          cv::Mat containing the 2D DFT of provided function
 *                   (CV_64FC2 - double-precision complex)
 */
cv::Mat Dft2(cv::Mat f, const int flag = 0);
}
