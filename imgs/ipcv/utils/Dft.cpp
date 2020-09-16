/** Implementation file for computing the DFT of a complex vector
 *
 *  \file ipcv/utils/Dft.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 14 Nov 2018
 */

#include <complex>
#include <vector>

#include "Dft.h"

namespace ipcv {

std::vector<std::complex<double>> Dft(
    const std::vector<std::complex<double>>& f, int flag) {
  const std::complex<double> i(0, 1);

  int N = f.size();
  std::vector<std::complex<double>> F(N);

  // Insert your code here

  return F;
}
}
