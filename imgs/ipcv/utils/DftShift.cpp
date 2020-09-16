/** Implementation file for shifting/quadrant exchange of a frequency spectrum
 *
 *  \file ipcv/utils/Dist.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 03 Dec 2018
 */

#include "DftShift.h"

namespace ipcv {

cv::Mat DftShift(const cv::Mat spectrum) {
  cv::Mat shifted_spectrum = spectrum.clone();

  int cr = shifted_spectrum.rows / 2;
  int cc = shifted_spectrum.cols / 2;

  cv::Mat q0(shifted_spectrum, cv::Rect(0, 0, cc, cr));
  cv::Mat q1(shifted_spectrum, cv::Rect(cc, 0, cc, cr));
  cv::Mat q2(shifted_spectrum, cv::Rect(0, cr, cc, cr));
  cv::Mat q3(shifted_spectrum, cv::Rect(cc, cr, cc, cr));
  cv::Mat tmp;
  q0.copyTo(tmp);
  q3.copyTo(q0);
  tmp.copyTo(q3);
  q1.copyTo(tmp);
  q2.copyTo(q1);
  tmp.copyTo(q2);

  return shifted_spectrum;
}
}
