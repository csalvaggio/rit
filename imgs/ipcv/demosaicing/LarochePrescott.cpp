/** Implementation file for CFA demosaic function using Laroche and Prescott
 *  interpolation
 *
 *  \file ipcv/demosaic/LarochePrescott.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 07 Jan 2019
 */

#include <iostream>

#include <opencv2/imgproc.hpp>

#include "Bilinear.h"

using namespace std;

namespace ipcv {

cv::Mat LarochePrescott(const cv::Mat& src, string pattern, int max_value) {
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
  cv::multiply(src, b_mask, B, 1, CV_32F);
  cv::Mat G;
  cv::multiply(src, g_mask, G, 1, CV_32F);
  cv::Mat R;
  cv::multiply(src, r_mask, R, 1, CV_32F);

  // Set bounds for the iterpolation domain
  int ul_row = 2;
  int ul_col = 2;
  int lr_row = src.rows - 2;
  int lr_col = src.cols - 2;

  // Compute vertical (alpha) and horizontal (beta) edge classifiers
  // (compute for all locations here and use appropriate ones later)
  cv::Mat alpha = cv::Mat::zeros(src.size(), CV_32F);
  cv::Mat beta = cv::Mat::zeros(src.size(), CV_32F);
  for (int r = ul_row; r < lr_row; r++) {
    for (int c = ul_col; c < lr_col; c++) {
      alpha.at<float>(r, c) =
          abs((static_cast<float>(src.at<uint16_t>(r, c - 2)) +
               static_cast<float>(src.at<uint16_t>(r, c + 2))) /
                  2 -
              static_cast<float>(src.at<uint16_t>(r, c)));
      beta.at<float>(r, c) =
          abs((static_cast<float>(src.at<uint16_t>(r - 2, c)) +
               static_cast<float>(src.at<uint16_t>(r - 2, c))) /
                  2 -
              static_cast<float>(src.at<uint16_t>(r, c)));
    }
  }

  // Interpolate green (G) channel according to gradient rules
  for (int r = ul_row; r < lr_row; r++) {
    for (int c = ul_col; c < lr_col; c++) {
      if (g_mask.at<uint16_t>(r, c) == 0) {
        float equality_tolerance = 8.0;
        if (abs(alpha.at<float>(r, c) - beta.at<float>(r, c)) <
            equality_tolerance) {
          G.at<float>(r, c) =
              (G.at<float>(r - 1, c) + 
               G.at<float>(r, c - 1) +
               G.at<float>(r + 1, c) + 
               G.at<float>(r, c + 1)) / 4;
        } else if (alpha.at<float>(r, c) < beta.at<float>(r, c)) {
          G.at<float>(r, c) =
              (G.at<float>(r, c - 1) + G.at<float>(r, c + 1)) / 2;
        } else if (alpha.at<float>(r, c) > beta.at<float>(r, c)) {
          G.at<float>(r, c) =
              (G.at<float>(r - 1, c) + G.at<float>(r + 1, c)) / 2;
        }
      }
    }
  }

  // Interpolate missing red (R) values in red (R) rows (horizontal)
  for (int r = r_row; r < lr_row; r += 2) {
    for (int c = ul_col; c < lr_col; c++) {
      if (g_mask.at<uint16_t>(r, c) == 1) {
        R.at<float>(r, c) =
            ((R.at<float>(r, c - 1) - G.at<float>(r, c - 1)) +
             (R.at<float>(r, c + 1) - G.at<float>(r, c + 1))) / 2 +
            G.at<float>(r, c);
      }
    }
  }

  // Interpolate missing red (R) values in blue (B) rows (vertical)
  for (int r = b_row; r < lr_row; r += 2) {
    for (int c = ul_col; c < lr_col; c++) {
      if (g_mask.at<uint16_t>(r, c) == 1) {
        R.at<float>(r, c) =
            ((R.at<float>(r - 1, c) - G.at<float>(r - 1, c)) +
             (R.at<float>(r + 1, c) - G.at<float>(r + 1, c))) / 2 +
            G.at<float>(r, c);
      } else {
        R.at<float>(r, c) =
            ((R.at<float>(r - 1, c - 1) - G.at<float>(r - 1, c - 1)) +
             (R.at<float>(r - 1, c + 1) - G.at<float>(r - 1, c + 1)) +
             (R.at<float>(r + 1, c - 1) - G.at<float>(r + 1, c - 1)) +
             (R.at<float>(r + 1, c + 1) - G.at<float>(r + 1, c + 1))) / 4 +
            G.at<float>(r, c);
      }
    }
  }

  // Interpolate missing blue (B) values in blue (B) rows (horizontal)
  for (int r = b_row; r < lr_row; r += 2) {
    for (int c = ul_col; c < lr_col; c++) {
      if (g_mask.at<uint16_t>(r, c) == 1) {
        B.at<float>(r, c) =
            ((B.at<float>(r, c - 1) - G.at<float>(r, c - 1)) +
             (B.at<float>(r, c + 1) - G.at<float>(r, c + 1))) / 2 +
            G.at<float>(r, c);
      }
    }
  }

  // Interpolate missing blue (B) values in red (R) rows (vertical)
  for (int r = r_row; r < lr_row; r += 2) {
    for (int c = ul_col; c < lr_col; c++) {
      if (g_mask.at<uint16_t>(r, c) == 1) {
        B.at<float>(r, c) =
            ((B.at<float>(r - 1, c) - G.at<float>(r - 1, c)) +
             (B.at<float>(r + 1, c) - G.at<float>(r + 1, c))) / 2 +
            G.at<float>(r, c);
      } else {
        B.at<float>(r, c) =
            ((B.at<float>(r - 1, c - 1) - G.at<float>(r - 1, c - 1)) +
             (B.at<float>(r - 1, c + 1) - G.at<float>(r - 1, c + 1)) +
             (B.at<float>(r + 1, c - 1) - G.at<float>(r + 1, c - 1)) +
             (B.at<float>(r + 1, c + 1) - G.at<float>(r + 1, c + 1))) / 4 +
            G.at<float>(r, c);
      }
    }
  }

  // Clamp values into the user-specified dynamic range
  float min_dc = 0.0;
  float max_dc = static_cast<float>(max_value);
  for (int r = 0; r < src.rows; r++) {
    for (int c = 0; c < src.cols; c++) {
      B.at<float>(r, c) = clamp(B.at<float>(r, c), min_dc, max_dc);
      G.at<float>(r, c) = clamp(G.at<float>(r, c), min_dc, max_dc);
      R.at<float>(r, c) = clamp(R.at<float>(r, c), min_dc, max_dc);
    }
  }

  // Merge the interpolated B, G, and R channels into a 3-channel cv::Mat
  cv::Mat channels[3];
  B.convertTo(channels[0], CV_16U);
  G.convertTo(channels[1], CV_16U);
  R.convertTo(channels[2], CV_16U);
  cv::Mat dst;
  cv::merge(channels, 3, dst);

  return dst;
}
}
