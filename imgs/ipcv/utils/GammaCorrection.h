/** Interface file for computing the PSNR between two images
 *
 *  \file ipcv/utils/Psnr.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 28 Dec 2018
 */

#pragma once

#include <opencv2/core.hpp>

namespace ipcv {

/** Compute the 3-channel image histogram of the provided source image
 *
 *  \param[in] src         source cv::Mat of CV_8UC3 or CV_16UC3
 *  \param[in] gamma       gamma to be applied
 *  \param[in] max_value   maximum possible value data sources may take on
 *
 *  \return                gamma corrected source image
 */
cv::Mat GammaCorrection(const cv::Mat& src, const double gamma = 2.2,
                        const int max_value = 255);
}
