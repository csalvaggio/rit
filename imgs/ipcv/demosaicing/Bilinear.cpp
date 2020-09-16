/** Implementation file for CFA demosaic function using bilinear interpolation
 *
 *  \file ipcv/demosaic/Bilinear.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 07 Jan 2019
 */

#include <iostream>

#include <opencv2/imgproc.hpp>

#include "Bilinear.h"

using namespace std;

namespace ipcv {

cv::Mat Bilinear(const cv::Mat& src, string pattern) {
  // Create blue (B) and red (R) filter location masks
  int b_row;
  int b_col;
  int r_row;
  int r_col;
  if (pattern == "GBRG") {
    b_row = 0;
    b_col = 1;
    r_row = 1;
    r_col = 0;
  } else if (pattern == "GRBG") {
    b_row = 1;
    b_col = 0;
    r_row = 0;
    r_col = 1;
  } else if (pattern == "BGGR") {
    b_row = 0;
    b_col = 0;
    r_row = 1;
    r_col = 1;
  } else if (pattern == "RGGB") {
    b_row = 1;
    b_col = 1;
    r_row = 0;
    r_col = 0;
  } else {
    cerr << "Invalid CFA pattern provided: " << pattern << endl;
    exit(EXIT_FAILURE);
  }
  cv::Mat b_mask = cv::Mat::zeros(src.size(), CV_16UC1);
  for (int r = b_row; r < src.rows; r += 2) {
    for (int c = b_col; c < src.cols; c += 2) {
      b_mask.at<uint16_t>(r, c) = 1;
    }
  }
  cv::Mat r_mask = cv::Mat::zeros(src.size(), CV_16UC1);
  for (int r = r_row; r < src.rows; r += 2) {
    for (int c = r_col; c < src.cols; c += 2) {
      r_mask.at<uint16_t>(r, c) = 1;
    }
  }

  // Create green (G) filter location mask
  cv::Mat g_mask = cv::Mat::ones(src.size(), CV_16UC1);
  cv::subtract(g_mask, b_mask, g_mask);
  cv::subtract(g_mask, r_mask, g_mask);

  // Initialize interpolated B, G, and R channels
  cv::Mat B;
  cv::multiply(src, b_mask, B);
  cv::Mat G;
  cv::multiply(src, g_mask, G);
  cv::Mat R;
  cv::multiply(src, r_mask, R);

  // Set bounds for the iterpolation domain
  int ul_row = 2;
  int ul_col = 2;
  int lr_row = src.rows - 2;
  int lr_col = src.cols - 2;

  // Interpolate green (G) channel
  for (int r = ul_row; r < lr_row; r++) {
    for (int c = ul_col; c < lr_col; c++) {
      if (g_mask.at<uint16_t>(r, c) == 0) {
        G.at<uint16_t>(r, c) =
            (G.at<uint16_t>(r - 1, c) + G.at<uint16_t>(r, c - 1) +
             G.at<uint16_t>(r + 1, c) + G.at<uint16_t>(r, c + 1)) /
            4;
      }
    }
  }

  // Interpolate missing red (R) values in red (R) rows (horizontal)
  for (int r = r_row; r < lr_row; r += 2) {
    for (int c = ul_col; c < lr_col; c++) {
      if (r_mask.at<uint16_t>(r, c) == 0) {
        R.at<uint16_t>(r, c) =
            (R.at<uint16_t>(r, c - 1) + R.at<uint16_t>(r, c + 1)) / 2;
      }
    }
  }

  // Interpolate values in missing red (R) rows (vertical)
  for (int r = r_row + 1; r < lr_row; r += 2) {
    for (int c = ul_col; c < lr_col; c++) {
      if (r_mask.at<uint16_t>(r, c) == 0) {
        R.at<uint16_t>(r, c) =
            (R.at<uint16_t>(r - 1, c) + R.at<uint16_t>(r + 1, c)) / 2;
      }
    }
  }

  // Interpolate missing blue (B) values in blue (B) rows (horizontal)
  for (int r = b_row; r < lr_row; r += 2) {
    for (int c = ul_col; c < lr_col; c++) {
      if (b_mask.at<uint16_t>(r, c) == 0) {
        B.at<uint16_t>(r, c) =
            (B.at<uint16_t>(r, c - 1) + B.at<uint16_t>(r, c + 1)) / 2;
      }
    }
  }

  // Interpolate values in missing blue (B) rows (vertical)
  for (int r = b_row + 1; r < lr_row; r += 2) {
    for (int c = ul_col; c < lr_col; c++) {
      if (b_mask.at<uint16_t>(r, c) == 0) {
        B.at<uint16_t>(r, c) =
            (B.at<uint16_t>(r - 1, c) + B.at<uint16_t>(r + 1, c)) / 2;
      }
    }
  }

  // Merge the interpolated B, G, and R channels into a 3-channel cv::Mat
  cv::Mat channels[3];
  channels[0] = B;
  channels[1] = G;
  channels[2] = R;
  cv::Mat dst;
  cv::merge(channels, 3, dst);

  return dst;
}
}
