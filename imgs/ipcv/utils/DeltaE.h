/** Interface file for computing the delta E between two images
 *
 *  \file imgs/ipcv/utils/DeltaE.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 18 January 2020
 */

#pragma once

#include <string>
#include <vector>

#include <opencv2/core.hpp>

namespace ipcv {

/** Compute delta E between the provided source images
 *
 *  \param[in] src1         source cv::Mat of CV_8UC3
 *  \param[in] src2         source cv::Mat of CV_8UC3
 *  \param[in] max_value    maximum possible value data sources may take on
 *  \param[in] weights      weight map cv::Mat of any single-channel CV type
 *                          Used to weight the metric by location (if not
 *                          provided, all location weights will be set to unity)
 *
 *  \param[out] dE          destination cv::Mat of CV_32FC1 for delta E
 *
 *  \param[in] standard     Standard to use 1976 | 1994 | 2000
 *                          [default is 1976]
 *  \param[in] application  Application type to use if the delta E 1994
 *                          standard is selected graphic_arts | textiles
 *                          (ignored otherwise)
 *                          [default is graphic_arts]
 *
 *  \return                 double scalar containing the delta E between
 *                          the source images
 */
double DeltaE(const cv::Mat& src1, const cv::Mat& src2, int max_value,
              const cv::Mat& weights, cv::Mat& dE, int standard = 1976,
              std::string application = "graphic_arts");

double DeltaE(const cv::Mat& src1, const cv::Mat& src2, int max_value,
              const cv::Mat& weights, int standard = 1976,
              std::string application = "graphic_arts");

double DeltaE(const cv::Mat& src1, const cv::Mat& src2, int max_value,
              cv::Mat& dE, int standard = 1976,
              std::string application = "graphic_arts");

double DeltaE(const cv::Mat& src1, const cv::Mat& src2, int max_value,
              int standard = 1976, std::string application = "graphic_arts");
}
