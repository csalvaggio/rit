/** Implementation file for the creation of a distance surface/function
 *
 *  \file ipcv/utils/Dist.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 18 Nov 2018
 */

#include "Dist.h"

namespace ipcv {

cv::Mat Dist(const int rows, const int cols, const bool shift) {
  cv::Mat distance(rows, cols, CV_64FC1);

  int cr = rows / 2;
  int cc = cols / 2;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      int y = r - cr;
      int x = c - cc;
      distance.at<double>(r, c) = sqrt(pow(y, 2) + pow(x, 2));
    }
  }

  if (shift) {
    cv::Mat q0(distance, cv::Rect(0, 0, cc, cr));
    cv::Mat q1(distance, cv::Rect(cc, 0, cc, cr));
    cv::Mat q2(distance, cv::Rect(0, cr, cc, cr));
    cv::Mat q3(distance, cv::Rect(cc, cr, cc, cr));
    cv::Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
  }

  return distance;
}
}
