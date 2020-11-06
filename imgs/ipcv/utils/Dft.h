/** Interface file for computing the DFT of a vector
 *
 *  \file ipcv/utils/Dft.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 05 November 2020
 */

#pragma once

#include <complex>

#include <opencv2/core.hpp>

namespace ipcv {

// Available DFT computation flags
enum DftFlags {
  DFT_INVERSE = 1,
  DFT_SCALE = 2
};

/** Compute the DFT of a complex vector (cv::Mat)
 *
 *  \param[in] f     function of type cv::Mat (N x 1)
 *  \param[in] flag  bitwise options flag (see enum above)
 *                     1 - inverse transform should occur
 *                     2 - scaling should occur
 *
 *  \return          cv::Mat containing the DFT of provided function
 *                   (CV_64FC2 - double-precision complex)
 */
cv::Mat Dft(cv::Mat f, const int flag = 0);
}
