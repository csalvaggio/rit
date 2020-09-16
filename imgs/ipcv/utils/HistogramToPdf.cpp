/** Implementation file for computing the PDF from a histogram
 *
 *  \file ipcv/utils/HistogramToPdf.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 17 Mar 2018
 */

#include "HistogramToPdf.h"

namespace ipcv {

void HistogramToPdf(const cv::Mat& h, cv::Mat& pdf) {
  pdf.create(h.size(), CV_64F);

  // Insert your code here

}
}
