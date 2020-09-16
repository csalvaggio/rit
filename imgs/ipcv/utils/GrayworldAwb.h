/** Interface file for performing AWB on image using gray world assumptions
 *
 *  \file ipcv/utils/GrayworldAwb.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 04 Jan 2019
 */

#pragma once

#include <opencv2/core.hpp>

namespace ipcv {

/** Automatic white balance source image using grayworld assumptions
 *
 *  \param[in] src         source cv::Mat of CV_8UC3 or CV_16UC3
 *  \param[in] scale       the chrominance (a* and b*) shift multiplier 
 *                         used to modify the effect of luminance-level 
 *                         scaling
 *  \param[in] max_value   maximum possible value data sources may take on
 *
 *  \return                automatic white balanced source image
 */
cv::Mat GrayworldAwb(const cv::Mat& src, const double scale = 1.1,
                     const int max_value = 255);
}
