/** Implementation file for applying gamma correction to a source image
 *
 *  \file ipcv/utils/GammaCorrection.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 29 Dec 2018
 */

#include <iostream>

#include "GammaCorrection.h"

using namespace std;

namespace ipcv {

cv::Mat GammaCorrection(const cv::Mat& src, const double gamma,
                        const int max_value) {
  int type = src.type();
  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar channels = 1 + (type >> CV_CN_SHIFT);

  cv::Mat lut;
  lut.create(channels, max_value + 1, depth);
  switch (depth) {
    case CV_8U:
      for (int dc = 0; dc <= max_value; dc++) {
        uint8_t value = static_cast<uint8_t>(
            pow(dc / static_cast<double>(max_value), 1 / gamma) * max_value +
            0.5);
        for (int b = 0; b < channels; b++) {
          lut.at<uint8_t>(b, dc) = value;
        }
      }
      break;

    case CV_16U:
      for (int dc = 0; dc <= max_value; dc++) {
        uint16_t value = static_cast<uint16_t>(
            pow(dc / static_cast<double>(max_value), 1 / gamma) * max_value +
            0.5);
        for (int b = 0; b < channels; b++) {
          lut.at<uint16_t>(b, dc) = value;
        }
      }
      break;

    default:
      cerr << "Unsupported data type for gamma correction" << endl;
      exit(EXIT_FAILURE);
  }

  cv::Mat dst;
  dst.create(src.size(), type);
  switch (depth) {
    case CV_8U:
      if (channels == 3) {
        for (int r = 0; r < src.rows; r++) {
          for (int c = 0; c < src.cols; c++) {
            const auto& src_dc = src.at<cv::Vec3b>(r, c);
            auto& dst_dc = dst.at<cv::Vec3b>(r, c);
            dst_dc[0] = lut.at<uint8_t>(0, src_dc[0]);
            dst_dc[1] = lut.at<uint8_t>(1, src_dc[1]);
            dst_dc[2] = lut.at<uint8_t>(2, src_dc[2]);
          }
        }
      } else {
        for (int r = 0; r < src.rows; r++) {
          for (int c = 0; c < src.cols; c++) {
            const auto& src_dc = src.at<uint8_t>(r, c);
            auto& dst_dc = dst.at<uint8_t>(r, c);
            dst_dc = lut.at<uint8_t>(0, src_dc);
          }
        }
      }
      break;

    case CV_16U:
      if (channels == 3) {
        for (int r = 0; r < src.rows; r++) {
          for (int c = 0; c < src.cols; c++) {
            const auto& src_dc = src.at<cv::Vec<uint16_t, 3>>(r, c);
            auto& dst_dc = dst.at<cv::Vec<uint16_t, 3>>(r, c);
            dst_dc[0] = lut.at<uint16_t>(0, src_dc[0]);
            dst_dc[1] = lut.at<uint16_t>(1, src_dc[1]);
            dst_dc[2] = lut.at<uint16_t>(2, src_dc[2]);
          }
        }
      } else {
        for (int r = 0; r < src.rows; r++) {
          for (int c = 0; c < src.cols; c++) {
            const auto& src_dc = src.at<uint16_t>(r, c);
            auto& dst_dc = dst.at<uint16_t>(r, c);
            dst_dc = lut.at<uint16_t>(0, src_dc);
          }
        }
      }
      break;
  }

  return dst;
}
}
