/** Implementation file for computing an image histogram
 *
 *  \file ipcv/utils/Histogram.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 17 Mar 2018
 */

#include "Histogram.h"

namespace ipcv {

void Histogram(const cv::Mat& src, cv::Mat& h) {
  h = cv::Mat_<int>::zeros(3, 256);

  // Insert your code here

}
}
