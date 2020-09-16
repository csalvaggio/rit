/** Implementation file for computing the RMSE between two images
 *
 *  \file imgs/ipcv/utils/Rmse.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 18 January 2020
 */

#include <iostream>

#include <opencv2/imgproc.hpp>

#include "imgs/ipcv/utils/Rmse.h"

using namespace std;

namespace ipcv {

double Rmse(const cv::Mat& src1, const cv::Mat& src2, const cv::Mat& weights,
            std::vector<double>& channel_rmse) {
  // Confirm that the two source images have the same area and the same
  // number of channels
  if ((src1.rows != src2.rows) || (src1.cols != src2.cols) ||
      (src1.channels() != src2.channels())) {
    cerr << "Dimensions of source images must match exactly for RMSE "
            "computation"
         << endl;
    exit(EXIT_FAILURE);
  }

  // Confirm that the weight map and the two source images have the same area
  if ((weights.rows != src1.rows) || (weights.cols != src1.cols)) {
    cerr << "Area dimensions of weight map and source images must match "
            "exactly for RMSE computation"
         << endl;
    exit(EXIT_FAILURE);
  }

  // Confirm that the weight map has one channel
  if (weights.channels() > 1) {
    cerr << "Weight map must be single channel for RMSE computation" << endl;
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

  // Compute the root mean weighted squared error for the ensemble and each
  // channel
  double rmse = sqrt(mse);

  channel_rmse.push_back(sqrt(mse0));
  channel_rmse.push_back(sqrt(mse1));
  channel_rmse.push_back(sqrt(mse2));

  return rmse;
}

double Rmse(const cv::Mat& src1, const cv::Mat& src2, const cv::Mat& weights) {
  std::vector<double> channel_rmse;

  cv::Mat weight_map;
  weights.convertTo(weight_map, CV_32F);

  return Rmse(src1, src2, weight_map, channel_rmse);
}

double Rmse(const cv::Mat& src1, const cv::Mat& src2,
            std::vector<double>& channel_rmse) {
  cv::Mat weights;
  weights.create(src1.rows, src1.cols, CV_32FC1);
  weights.setTo(cv::Scalar(1));

  return Rmse(src1, src2, weights, channel_rmse);
}

double Rmse(const cv::Mat& src1, const cv::Mat& src2) {
  cv::Mat weights;
  weights.create(src1.rows, src1.cols, CV_32FC1);
  weights.setTo(cv::Scalar(1));

  std::vector<double> channel_rmse;

  return Rmse(src1, src2, weights, channel_rmse);
}
}
