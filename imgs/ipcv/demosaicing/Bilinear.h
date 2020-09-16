/** Interface file for CFA demosaic function using bilinear interpolation
 *
 *  \file ipcv/demosaic/Bilinear.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 07 Jan 2019
 *
 *  \description
 *    This function will perform color filter array interpolation on a
 *    generic document mode (Bayer) image.  A simple neighbor averaging
 *    approach will be taken for each of the three patterned color
 *    channels.
 *
 *    The green channel interpolation will be performed, at each "x"
 *    location,
 *
 *       G x G x G
 *       x G x G x
 *       G x G x G
 *       x G x G x
 *       G x G x G
 *
 *    as the average of the surrounding four G values.
 *
 *    For the red channel
 *
 *       x R x R x
 *       y y y y y
 *       x R x R x
 *       y y y y y
 *       x R x R x
 *
 *    the interpolation at each "x" location will be the average of the
 *    horizontal neighbors.  Subsequently, the interpolation at each
 *    "y" location will be the average of the vertical neighbors (half
 *    of which are original red values and half of which are interpolated
 *    red values).
 *
 *    Similarly for the blue channel
 *
 *       y y y y y
 *       B x B x B
 *       y y y y y
 *       B x B x B
 *       y y y y y
 *
 *    the interpolation at each "x" location will be the average of the
 *    horizontal neighbors.  Subsequently, the interpolation at each
 *    "y" location will be the average of the vertical neighbors (half
 *    of which are original blue values and half of which are interpolated
 *    blue values).
 */

#pragma once

#include <string>

#include <opencv2/core.hpp>

using namespace std;

namespace ipcv {

/** Interpolate CFA using bilinear interpolation
 *
 *  \param[in] src       source cv::Mat of CV_16UC1 containing CFA
 *  \param[in] pattern   a string defining the CFA layout:
 *                         'GBRG'  -  G B  Raspberry Pi (OmniVision OV5647)
 *                                    R G
 *                         'GRBG'  -  G R
 *                                    B G
 *                         'BGGR'  -  B G
 *                                    G R
 *                         'RGGB'  -  R G
 *                                    G B
 *
 *  \return              destination cv::Mat of CV_16UC3 for interpolated
 *                       3-channel (color) image
 */
cv::Mat Bilinear(const cv::Mat& src, string pattern = "GBRG");
}
