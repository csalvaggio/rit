/** Interface file for finding map coordinates for an RST transformation
 *
 *  \file ipcv/geometric_transformation/MapRST.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 15 Sep 2018
 */

#pragma once

#include <opencv2/core.hpp>

#include <Eigen/Dense>

namespace ipcv {

/** Find the map coordinates (map1, map2) for an RST transformation
 *
 *  \param[in] src           source cv::Mat of CV_8UC3
 *  \param[in] angle         rotation angle (CCW) [radians]
 *  \param[in] scale_x       horizontal scale
 *  \param[in] scale_y       vertical scale
 *  \param[in] translation_x horizontal translation [+ to the right]
 *  \param[in] translation_y vertical translation [+ iup]
 *  \param[out] map1         cv::Mat of CV_32FC1 (size of the destination map)
 *                           containing the horizontal (x) coordinates at
 *                           which to resample the source data
 *  \param[out] map2         cv::Mat of CV_32FC1 (size of the destination map)
 *                           containing the vertical (y) coordinates at
 *                           which to resample the source data
 */
bool MapRST(const cv::Mat src, const double angle, const double scale_x,
            const double scale_y, const double translation_x,
            const double translation_y, cv::Mat& map1, cv::Mat& map2);
}
