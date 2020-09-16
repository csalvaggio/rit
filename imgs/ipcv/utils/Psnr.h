/** Interface file for computing the PSNR between two images
 *
 *  \file imgs/ipcv/utils/Psnr.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 18 January 2020
 */

#pragma once

#include <vector>

#include <opencv2/core.hpp>

namespace ipcv {

/** Compute peak signal-to-noise ratio between the provided source images
 *
 *  \param[in] src1        source cv::Mat of CV_8UC3
 *  \param[in] src2        source cv::Mat of CV_8UC3
 *  \param[in] weights     weight map cv::Mat of any single-channel CV type
 *                         Used to weight the metric by location (if not
 *                         provided, all location weights will be set to unity)
 *  \param[in] max_value   maximum possible value data sources may take on
 *
 *  \param[out] channel_psnr
 *                         std::vector<double> containing the individual
 *                         channel PSNR between the source images
 *
 *  \return                double scalar containing ensemble PSNR between
 *                         the source images
 */
double Psnr(const cv::Mat& src1, const cv::Mat& src2, int max_value,
            const cv::Mat& weights, std::vector<double>& channel_psnr);

double Psnr(const cv::Mat& src1, const cv::Mat& src2, int max_value,
            const cv::Mat& weights);

double Psnr(const cv::Mat& src1, const cv::Mat& src2, int max_value,
            std::vector<double>& channel_psnr);

double Psnr(const cv::Mat& src1, const cv::Mat& src2, int max_value);
}
