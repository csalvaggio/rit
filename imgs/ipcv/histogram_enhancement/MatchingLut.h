/** Interface file for image enhancement using histogram matching
 *
 *  \file ipcv/histogram_enhancement/MatchingLut.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 3 Sep 2018
 */

#pragma once

#include <opencv2/core.hpp>

namespace ipcv {

/** Create a 3-channel (color) LUT using histogram matching
 *
 *  \param[in] src   source cv::Mat of CV_8UC3
 *  \param[in] h     the histogram in cv:Mat(3, 256) that the
 *                   source is to be matched to
 *  \param[out] lut  3-channel look up table in cv::Mat(3, 256)
 */
bool MatchingLut(const cv::Mat& src, const cv::Mat& h, cv::Mat& lut);
}
