/** Interface file for CFA ddemosaic function using Laroche and Prescott
 *  interpolation
 *
 *  \file ipcv/demosaic/LarochePrescott.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 07 Jan 2019
 *
 *  \description
 *    This function will perform color filter array interpolation on a
 *    generic document mode (Bayer) image.  A gradient-based approach
 *    is taken to avoid interpolating across edges to minimize color
 *    artifacting.  The technique is an implementation of the following
 *    paper:
 *
 *      C.A. Laroche and M.A. Prescott, "Apparatus and method
 *      for adaptively interpolating a full color image utilizing
 *      chrominance gradients", U.S. Patent No. 5,373,322 (1994)
 */

#pragma once

#include <string>

#include <opencv2/core.hpp>

using namespace std;

namespace ipcv {

/** Interpolate CFA using Laroche and Prescott interpolation
 *
 *  \param[in] src         source cv::Mat of CV_16UC1 containing CFA
 *  \param[in] pattern     a string defining the CFA layout:
 *                           'GBRG'  -  G B  Raspberry Pi (OmniVision OV5647)
 *                                      R G
 *                           'GRBG'  -  G R
 *                                      B G
 *                           'BGGR'  -  B G
 *                                      G R
 *                           'RGGB'  -  R G
 *                                      G B
 *  \param[in] max_value   the maximum value the image may take on
 *
 *  \return                destination cv::Mat of CV_16UC3 for interpolated
 *                         3-channel (color) image
 */
cv::Mat LarochePrescott(const cv::Mat& src, string pattern = "GBRG",
                        int max_value = 65535);
}
