#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include "imgs/ipcv/utils/Utils.h"

using namespace std;

int main() {
  size_t N = 32;
  size_t repetitions = 10000;

  // Create and display the original 1-dimensional function (constant)
  auto f = cv::Mat::ones(N, 1, CV_64FC2);
  cout << "Original function (1D):" << endl;
  cout << f << endl;
  cout << endl;

  // Perform 1-dimensional DFT
  cv::Mat F = ipcv::Dft(f, ipcv::DFT_SCALE);
  cout << "Fourier transform (1D):" << endl;
  cout << F << endl;
  cout << endl;

  // Time multiple repititions of the 1-dimensional DFT
  clock_t startTime = clock();
  for (size_t idx = 0; idx < repetitions; idx++) {
    F = ipcv::Dft(f, ipcv::DFT_SCALE);
  }
  clock_t endTime = clock();
  cout << "Elapsed time: "
       << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s] for " 
       << repetitions
       << " repetitions (using ipcv:Dft)"
       << endl;

  // Time multiple repititions of the 1-dimensional DFT using cv::Dft
  startTime = clock();
  for (size_t idx = 0; idx < repetitions; idx++) {
    cv::dft(f, F, cv::DFT_COMPLEX_OUTPUT + cv::DFT_SCALE);
  }
  endTime = clock();
  cout << "Elapsed time: "
       << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s] for " 
       << repetitions
       << " repetitions (using cv::Dft)"
       << endl;
  cout << endl;

  // Perform inverse 1-dimensional DFT
  cv::Mat inverse = ipcv::Dft(F, ipcv::DFT_INVERSE);
  cout << "Inverse Fourier transform (1D):" << endl;
  cout << inverse << endl;
  cout << endl;

  // Time multiple repititions of the inverse 1-dimensional DFT
  startTime = clock();
  for (size_t idx = 0; idx < repetitions; idx++) {
    inverse = ipcv::Dft(F, ipcv::DFT_INVERSE);
  }
  endTime = clock();
  cout << "Elapsed time: "
       << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s] for " 
       << repetitions
       << " repetitions (using ipcv:Dft)"
       << endl;

  // Time multiple repititions of the inverse 1-dimensional DFT using cv::Dft
  startTime = clock();
  for (size_t idx = 0; idx < repetitions; idx++) {
    cv::dft(f, F, cv::DFT_REAL_OUTPUT + cv::DFT_INVERSE);
  }
  endTime = clock();
  cout << "Elapsed time: "
       << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s] for " 
       << repetitions
       << " repetitions (using cv::Dft)"
       << endl;
  cout << endl;


  N = 8;

  // Create and display the original 2-dimensional function (constant)
  auto m = cv::Mat::ones(N, N, CV_64FC2);
  cout << "Original function (2D):" << endl;
  cout << m << endl;
  cout << endl;

  // Perform 2-dimensional DFT
  cv::Mat M;
  M = ipcv::Dft2(m, ipcv::DFT_SCALE);
  cout << "Fourier transform (2D): (using ipcv:Dft)" << endl;
  cout << M << endl;
  cout << endl;

  // Perform 2-dimensional DFT using cv::Dft
  cv::dft(m, M, cv::DFT_COMPLEX_OUTPUT + cv::DFT_SCALE);
  cout << "Fourier transform (2D): (using cv::Dft)" << endl;
  cout << M << endl;
  cout << endl;

  // Perform inverse 2-dimensional DFT
  cv::Mat m_inv;
  m_inv = ipcv::Dft2(M, ipcv::DFT_INVERSE);
  cout << "Inverse Fourier transform (2D): (using ipcv:Dft)" << endl;
  cout << m_inv << endl;
  cout << endl;

  // Perform inverse 2-dimensional DFT using cv::Dft
  cv::dft(M, m_inv, cv::DFT_REAL_OUTPUT + cv::DFT_INVERSE);
  cout << "Inverse Fourier transform (2D): (using cv::Dft)" << endl;
  cout << m_inv << endl;
  cout << endl;


  // Read image into cv::Mat
  string filename = "../data/images/misc/lenna_grayscale.pgm";         
  cv::Mat src;
  src = cv::imread(filename, cv::IMREAD_UNCHANGED);
  cout << "Image filename:" << endl;
  cout << filename << endl;
  cout << endl;

  // Perform 2-dimensional DFT and time execution
  cv::Mat dft_input;
  cv::Mat dft_output;
  src.convertTo(dft_input, CV_64F);
  startTime = clock();
  cv::dft(dft_input, dft_output, cv::DFT_COMPLEX_OUTPUT + cv::DFT_SCALE);
  endTime = clock();
  cout << "Fourier transform (2D):" << endl;
  cout << "Elapsed time: "
       << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s] (using cv::Dft)" 
       << endl;

  startTime = clock();
  dft_output = ipcv::Dft2(dft_input, ipcv::DFT_SCALE);
  endTime = clock();
  cout << "Elapsed time: "
       << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s] (using ipcv:Dft)" 
       << endl;
  cout << endl;

  // Perform inverse 2-dimensional DFT and time execution
  cv::Mat idft_output;
  startTime = clock();
  cv::dft(dft_output, idft_output, cv::DFT_REAL_OUTPUT + cv::DFT_INVERSE);
  endTime = clock();
  cout << "Inverse Fourier transform (2D):" << endl;
  cout << "Elapsed time: "
       << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s] (using cv::Dft)" 
       << endl;

  startTime = clock();
  idft_output = ipcv::Dft2(dft_output, ipcv::DFT_INVERSE);
  endTime = clock();
  cout << "Elapsed time: "
       << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s] (using ipcv:Dft)" 
       << endl;
  cout << endl;

  cv::Mat idft_output_display;
  ipcv::DftMagnitude(idft_output).convertTo(idft_output_display, CV_8U); 


  // Report out diagnotic values for the 2-dimension DFT runs
  double src_min;
  double src_max;
  cv::minMaxLoc(src, &src_min, &src_max);

  double dft_output_min;
  double dft_output_max;
  cv::minMaxLoc(dft_output, &dft_output_min, &dft_output_max);

  double idft_output_min;
  double idft_output_max;
  cv::minMaxLoc(idft_output, &idft_output_min, &idft_output_max);

  int number_pixels = src.rows * src.cols;
  cout << "Number of pixels: " << number_pixels << endl;
  cout << "Source (mean): " << cv::mean(src).val[0] << endl;
  cout << "Source (size): " << src.size() << endl;
  cout << "Source (channels): " << src.channels() << endl;
  cout << "Source (type): " << src.type() << endl;
  cout << "Source (min): " << src_min << endl;
  cout << "Source (max): " << src_max << endl;
  cout << "DFT [scaled] (size): " << dft_output.size() << endl;
  cout << "DFT [scaled] (channels): " << dft_output.channels() << endl;
  cout << "DFT [scaled] (type): " << dft_output.type() << endl;
  cout << "DFT [scaled] (min): " << dft_output_min << endl;
  cout << "DFT [scaled] (max): " << dft_output_max << endl;
  cout << "iDFT (size): " << idft_output.size() << endl;
  cout << "iDFT (channels): " << idft_output.channels() << endl;
  cout << "iDFT (type): " << idft_output.type() << endl;
  cout << "iDFT (min): " << idft_output_min << endl;
  cout << "iDFT (max): " << idft_output_max << endl;


  // Display the original image, the log|DFT|, and the inverse DFT
  cv::imshow("Source", src);
  cv::imshow("log|DFT|", 
             ipcv::DftMagnitude(dft_output, 
                                ipcv::DFT_MAGNITUDE_LOG + 
                                ipcv::DFT_MAGNITUDE_CENTER + 
                                ipcv::DFT_MAGNITUDE_NORMALIZE));
  cv::imshow("iDFT", idft_output_display);
  cv::waitKey(0);

  return EXIT_SUCCESS;
}
