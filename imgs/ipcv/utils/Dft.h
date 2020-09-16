/** Interface file for computing the DFT of a complex vector
 *
 *  \file ipcv/utils/Dft.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 14 Nov 2018
 */

#pragma once

#include <complex>
#include <vector>

namespace ipcv {

// Available DFT computation flags
enum DftFlags {
  DFT_INVERSE = 1,
  DFT_SCALE = 2
};

/** Compute the DFT of a std::complex<double> vector
 *
 *  \param[in] f     complex function of type std::vector<std::complex<double>>
 *  \param[in] flag  bitwise options flag (see enum above)
 *                     1 - inverse transform should occur
 *                     2 - scaling should occur
 *
 *  \return          std::vector<std::complex<double>> containing the DFT
 *                   of provided function
 */
std::vector<std::complex<double>> Dft(
    const std::vector<std::complex<double>>& f, int flag = 0);
}
