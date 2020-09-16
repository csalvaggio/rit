/** Implementation file for computing a DFT magnitude spectra
 *
 *  \file ipcv/utils/DftMagnitude.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 14 Nov 2018
 */

#include <opencv2/imgproc.hpp>

#include "DftMagnitude.h"

namespace ipcv {

cv::Mat DftMagnitude(const cv::Mat& spectra, int flag) {
  // Compute the magnitude of the provided spectra
  cv::Mat planes[] = {cv::Mat::zeros(spectra.size(), CV_64F),
                      cv::Mat::zeros(spectra.size(), CV_64F)};
  cv::split(spectra, planes);
  cv::magnitude(planes[0], planes[1], planes[0]);
  cv::Mat magnitude = planes[0];

  // Compute the natural log of the magnitude spectra if requested
  if (flag & ipcv::DFT_MAGNITUDE_LOG) {
    cv::log(magnitude, magnitude);
  }

  // Rearrange quadrants so the (0,0) frequency is centered if requested
  if (flag & ipcv::DFT_MAGNITUDE_CENTER) {
    int cx = magnitude.cols / 2;
    int cy = magnitude.rows / 2;
    cv::Mat q0(magnitude, cv::Rect(0, 0, cx, cy));
    cv::Mat q1(magnitude, cv::Rect(cx, 0, cx, cy));
    cv::Mat q2(magnitude, cv::Rect(0, cy, cx, cy));
    cv::Mat q3(magnitude, cv::Rect(cx, cy, cx, cy));
    cv::Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
  }

  // Normalize the magnitude spectra between [0,1] if requested
  if (flag & ipcv::DFT_MAGNITUDE_NORMALIZE) {
    cv::normalize(magnitude, magnitude, 0, 1, cv::NORM_MINMAX);
  }

  return magnitude;
}
}
