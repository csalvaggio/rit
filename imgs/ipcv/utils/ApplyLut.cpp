/** Implementation file for applying a 3-channel LUT
 *  
 *  \file imgs/ipcv/utils/ApplyLut.spp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 3 Sep 2018
 */

#include "ApplyLut.h"

namespace ipcv {

bool ApplyLut(const cv::Mat& src, const cv::Mat &lut, cv::Mat& dst) {
  dst.create(src.size(), src.type());
  for (int r = 0; r < src.rows; r++) {
    for (int c = 0; c < src.cols; c++) {
      const auto& src_dc = src.at<cv::Vec3b>(r, c);
      auto& dst_dc = dst.at<cv::Vec3b>(r, c);
      dst_dc[0] = lut.at<uint8_t>(0, src_dc[0]);
      dst_dc[1] = lut.at<uint8_t>(1, src_dc[1]);
      dst_dc[2] = lut.at<uint8_t>(2, src_dc[2]);
    }
  }
  return true;
}
}
