/** Interface file for finding corner features using Harris
 *
 *  \file ipcv/corners/Harris.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 07 Nov 2018
 */

#pragma once

#include <opencv2/core.hpp>

using namespace std;

namespace ipcv {

/** Apply the Harris corner detector to a color image
 *
 *  \param[in] src     source cv::Mat of CV_8UC3
 *  \param[out] dst    destination cv:Mat of CV_32FC1
 *  \param[in] sigma   standard deviation of the Gaussian blur kernel
 *  \param[in] k       free parameter in the equation
 *                        dst = (lambda1)(lambda2) - k(lambda1 + lambda2)^2
 */
bool Harris(const cv::Mat& src, cv::Mat& dst, const float sigma, const float k);
}
