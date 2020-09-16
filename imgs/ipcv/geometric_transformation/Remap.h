/** Interface file for remapping source values to map locations
 *
 *  \file ipcv/geometric_transformation/Remap.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 15 Sep 2018
 */

#pragma once

#include <opencv2/core.hpp>

#include <Eigen/Dense>

namespace ipcv {

// Available interpolation types
enum class Interpolation {
  NEAREST,  // Nearest neighbor interpolation
  LINEAR  // Bilinear interpolation
};

// Available border modes
enum class BorderMode {
  CONSTANT,  // Use background color
  REPLICATE  // Replicate border pixels
};

/** Remap source values to the destination array at map1, map2 locations
 *
 *  \param[in] src            source cv::Mat of CV_8UC3
 *  \param[out] dst           destination cv::Mat of CV_8UC3 for remapped values
 *  \param[in] map1           cv::Mat of CV_32FC1 (size of the destination map)
 *                            containing the horizontal (x) coordinates at
 *                            which to resample the source data
 *  \param[in] map2           cv::Mat of CV_32FC1 (size of the destination map)
 *                            containing the vertical (y) coordinates at
 *                            which to resample the source data
 *  \param[in] interpolation  interpolation to be used for resampling
 *  \param[in] border_mode    border mode to be used for out of bounds pixels
 *  \param[in] border_value   border value to be used when constant border mode
 *                            is to be used
 */
bool Remap(const cv::Mat& src, cv::Mat& dst, const cv::Mat& map1,
           const cv::Mat& map2,
           const Interpolation interpolation = Interpolation::NEAREST,
           const BorderMode border_mode = BorderMode::CONSTANT,
           const uint8_t border_value = 0);
}
