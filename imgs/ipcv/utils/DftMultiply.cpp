/** Implementation file for multiplying a spectrum by a mask/filter
 *
 *  \file ipcv/utils/DftMultiply.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 04 Dec 2018
 */

#include "DftMultiply.h"

namespace ipcv {

cv::Mat DftMultiply(const cv::Mat spectrum, const cv::Mat filter) {
  if (spectrum.channels() != 2 || spectrum.type() != 14) {
    throw "The provided spectrum must be complex (CV_64FC2)";
  }

  if (filter.channels() != 1 || filter.type() != 6) {
    throw "The provided filter must be double (CV_64F)";
  }

  if (spectrum.rows != filter.rows || spectrum.cols != filter.cols) {
    throw "The number of rows/columns of the spectrum and filter must match";
  }

  cv::Mat planes[2];
  cv::split(spectrum, planes);
  cv::multiply(planes[0], filter, planes[0]);
  cv::multiply(planes[1], filter, planes[1]);
  cv::Mat product;
  cv::merge(planes, 2, product);

  return product;
}
}
