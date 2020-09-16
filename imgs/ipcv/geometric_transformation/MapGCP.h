/** Interface file for finding source image coordinates for a source-to-map
 *  remapping using ground control points
 *
 *  \file ipcv/geometric_transformation/MapGCP.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 15 Sep 2018
 */

#pragma once

#include <iostream>

#include <opencv2/core.hpp>

using namespace std;

namespace ipcv {

/** Find the source coordinates (map1, map2) for a ground control point
 *  derived mapping polynomial transformation
 *
 *  \param[in] src   source cv::Mat of CV_8UC3
 *  \param[in] map   map (target) cv::Mat of CV_8UC3
 *  \param[in] src_points
 *                   vector of cv::Points representing the ground control
 *                   points from the source image
 *  \param[in] map_points
 *                   vector of cv::Points representing the ground control
 *                   points from the map image
 *  \param[in] order  mapping polynomial order
 *                      EXAMPLES:
 *                        order = 1
 *                          a0*x^0*y^0 + a1*x^1*y^0 +
 *                          a2*x^0*y^1
 *                        order = 2
 *                          a0*x^0*y^0 + a1*x^1*y^0 + a2*x^2*y^0 +
 *                          a3*x^0*y^1 + a4*x^1*y^1 +
 *                          a5*x^0*y^2
 *                        order = 3
 *                          a0*x^0*y^0 + a1*x^1*y^0 + a2*x^2*y^0 + a3*x^3*y^0 +
 *                          a4*x^0*y^1 + a5*x^1*y^1 + a6*x^2*y^1 +
 *                          a7*x^0*y^2 + a8*x^1*y^2 +
 *                          a9*x^0*y^3
 *  \param[out] map1  cv::Mat of CV_32FC1 (size of the destination map)
 *                    containing the horizontal (x) coordinates at which to
 *                    resample the source data
 *  \param[out] map2  cv::Mat of CV_32FC1 (size of the destination map)
 *                    containing the vertical (y) coordinates at which to
 *                    resample the source data
 */
bool MapGCP(const cv::Mat src, const cv::Mat map,
            const vector<cv::Point> src_points,
            const vector<cv::Point> map_points, const int order,
            cv::Mat& map1, cv::Mat& map2);
}
