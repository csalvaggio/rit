/** Interface file for image filtering
 *
 *  \file ipcv/spatial_filtering/Filter2D.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 20 Sep 2018
 */

#pragma once

#include <opencv2/core.hpp>

namespace ipcv {

// Available border modes
enum class BorderMode {
  CONSTANT,  // Use background color
  REPLICATE  // Replicate border pixels
};

/** Correlates an image with the provided kernel
 *
 *  \param[in] src          source cv::Mat of CV_8UC3
 *  \param[out] dst         destination cv::Mat of ddepth type
 *  \param[in] ddepth       desired depth of the destination image
 *  \param[in] kernel       convolution kernel (or rather a correlation
 *                          kernel), a single-channel floating point matrix
 *  \param[in] anchor       anchor of the kernel that indicates the relative
 *                          position of a filtered point within the kernel;
 *                          the anchor should lie within the kernel; default
 *                          value (-1,-1) means that the anchor is at the
 *                          kernel center
 *  \param[in] delta        optional value added to the filtered pixels
 *                          before storing them in dst
 *  \param[in] border_mode  pixel extrapolation method
 *  \param[in] border_value value to use for constant border mode
 */
bool Filter2D(const cv::Mat& src, cv::Mat& dst, const int ddepth,
              const cv::Mat& kernel, const cv::Point anchor = cv::Point(-1, -1),
              const int delta = 0,
              const BorderMode border_mode = BorderMode::REPLICATE,
              uint8_t border_value = 0);
}
