/** Implementation file for computing a CDF from a histogram
 *
 *  \file ipcv/utils/HistogramToCdf.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 17 Mar 2018
 */

#include "HistogramToCdf.h"

#include "imgs/ipcv/utils/HistogramToPdf.h"

namespace ipcv {

void HistogramToCdf(const cv::Mat& h, cv::Mat& cdf) {
  cv::Mat pdf;
  HistogramToPdf(h, pdf);

  cdf.create(h.size(), CV_64F);

  // Insert your code here

}
}
