/** Interface file for computing the RMSE between two images
 *
 *  \file imgs/ipcv/utils/Rmse.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 18 January 2020
 */

#pragma once

#include <vector>

#include <opencv2/core.hpp>

namespace ipcv {

/** Compute root mean squared error between the provided source images
 *
 *  \param[in] src1      source cv::Mat of CV_8UC3
 *  \param[in] src2      source cv::Mat of CV_8UC3
 *  \param[in] weights   weight map cv::Mat of any single-channel CV type
 *                       Used to weight the metric by location (if not
 *                       provided, all location weights will be set to unity)
 *
 *  \param[out] channel_rmse
 *                       std::vector<double> containing the individual channel
 *                       RMSE between the source images
 *
 *  \return              double scalar containing the ensemble RMSE between
 *                       the source images
 */
double Rmse(const cv::Mat& src1, const cv::Mat& src2, const cv::Mat& weights,
            std::vector<double>& channel_rmse);

double Rmse(const cv::Mat& src1, const cv::Mat& src2, const cv::Mat& weights);

double Rmse(const cv::Mat& src1, const cv::Mat& src2,
            std::vector<double>& channel_rmse);

double Rmse(const cv::Mat& src1, const cv::Mat& src2);
}
