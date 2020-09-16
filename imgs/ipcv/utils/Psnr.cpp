/** Implementation file for computing the PSNR between two images
 *
 *  \file imgs/ipcv/utils/Psnr.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 18 January 2020
 */

#include <iostream>

#include <opencv2/imgproc.hpp>

#include "imgs/ipcv/utils/Psnr.h"

using namespace std;

namespace ipcv {

double Psnr(const cv::Mat& src1, const cv::Mat& src2, int max_value,
            const cv::Mat& weights, std::vector<double>& channel_psnr) {
  // Confirm that the two source images have the same area and the same
  // number of channels
  if ((src1.rows != src2.rows) || (src1.cols != src2.cols) ||
      (src1.channels() != src2.channels())) {
    cerr << "Dimensions of source images must match exactly for PSNR "
            "computation"
         << endl;
    exit(EXIT_FAILURE);
  }

  // Confirm that the weight map and the two source images have the same area
  if ((weights.rows != src1.rows) || (weights.cols != src1.cols)) {
    cerr << "Area dimensions of weight map and source images must match "
            "exactly for PSNR computation"
         << endl;
    exit(EXIT_FAILURE);
  }

  // Confirm that the weight map has one channel
  if (weights.channels() > 1) {
    cerr << "Weight map must be single channel for PSNR computation" << endl;
    exit(EXIT_FAILURE);
  }

  // Compute the squared errors
  cv::Mat se;
  cv::absdiff(src1, src2, se);
  se.convertTo(se, CV_32F);
  cv::multiply(se, se, se);

  // Weight the squared errors
  // (weight map must be three channel to multiply properly)
  std::vector<cv::Mat> weight_map_vector;
  weight_map_vector.push_back(weights);
  weight_map_vector.push_back(weights);
  weight_map_vector.push_back(weights);

  cv::Mat weight_map;
  cv::merge(weight_map_vector, weight_map);
  weight_map.convertTo(weight_map, CV_32F);

  cv::multiply(se, weight_map, se);

  // Compute the sum of the weighted squared errors for each channel
  cv::Scalar channel_sse = cv::sum(se);

  // Compute the mean weighted squared error for the ensemble and each channel
  double sse = channel_sse.val[0] + channel_sse.val[1] + channel_sse.val[2];
  double mse = sse / cv::sum(weights).val[0] / 3;

  double mse0 = channel_sse.val[0] / cv::sum(weights).val[0];
  double mse1 = channel_sse.val[1] / cv::sum(weights).val[0];
  double mse2 = channel_sse.val[2] / cv::sum(weights).val[0];

  // Compute the peak signal-to-noise ratio for the ensemble and each
  // channel
  double psnr = 10.0 * log10(max_value * max_value / mse);

  channel_psnr.push_back(10.0 * log10(max_value * max_value / mse0));
  channel_psnr.push_back(10.0 * log10(max_value * max_value / mse1));
  channel_psnr.push_back(10.0 * log10(max_value * max_value / mse2));

  return psnr;
}

double Psnr(const cv::Mat& src1, const cv::Mat& src2, int max_value,
            const cv::Mat& weights) {
  std::vector<double> channel_psnr;

  cv::Mat weight_map;
  weights.convertTo(weight_map, CV_32F);

  return Psnr(src1, src2, max_value, weight_map, channel_psnr);
}

double Psnr(const cv::Mat& src1, const cv::Mat& src2, int max_value,
            std::vector<double>& channel_psnr) {
  cv::Mat weights;
  weights.create(src1.rows, src1.cols, CV_32FC1);
  weights.setTo(cv::Scalar(1));

  return Psnr(src1, src2, max_value, weights, channel_psnr);
}

double Psnr(const cv::Mat& src1, const cv::Mat& src2, int max_value) {
  cv::Mat weights;
  weights.create(src1.rows, src1.cols, CV_32FC1);
  weights.setTo(cv::Scalar(1));

  std::vector<double> channel_psnr;

  return Psnr(src1, src2, max_value, weights, channel_psnr);
}
}
