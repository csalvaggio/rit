/** Interface file for computing a DFT magnitude spectra
 *
 *  \file ipcv/utils/DftMagnitude.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 14 Nov 2018
 */

#pragma once

#include <opencv2/core.hpp>

namespace ipcv {

// Available DFT magnitude computation flags
enum DftMagnitudeFlags {
  DFT_MAGNITUDE_LOG = 1,
  DFT_MAGNITUDE_CENTER = 2,
  DFT_MAGNITUDE_NORMALIZE = 4
};

/** Compute the magnitude spectra of a provided complex spectra (OpenCV)
 *
 *  \param[in] spectra  complex spectra cv::Mat of CV_32FC2 or CV_64FC2
 *  \param[in] flag     bitwise options flag (see enum class above)
 *                        1 - log magnitude should be returned
 *                        2 - spectra should be centered
 *                        4 - spectra should be normalized
 *
 *  \return             cv::Mat of CV_64F containing the magnitude spectra
 */
cv::Mat DftMagnitude(const cv::Mat& spectra, int flag = 0);
}
