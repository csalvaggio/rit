#include <complex>
#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include "imgs/ipcv/utils/Utils.h"

using namespace std;

int main() {
  // Set up parameters for 1-dimensional DFT testing
  size_t N = 32;
  size_t repetitions = 100000;

  // Create and display the original 1-dimensional function using a
  // vector of double-precision complex values
  vector<complex<double>> f(N);
  for (size_t idx = 0; idx < N; idx++) {
    f[idx] = 1;
  }
  cout << "Original function:" << endl;
  for (size_t idx = 0; idx < N; idx++) {
    cout << "f[" << idx << "]: " << f[idx] << endl;
  }
  cout << endl;

  // Perform 1-dimensional DFT and time multiple repititions
  vector<complex<double>> F = ipcv::Dft(f, ipcv::DFT_SCALE);
  cout << "Fourier transform:" << endl;
  for (size_t idx = 0; idx < N; idx++) {
    cout << "F[" << idx << "]: " << F[idx] << endl;
  }
  clock_t startTime = clock();
  for (size_t idx = 0; idx < repetitions; idx++) {
    F = ipcv::Dft(f, ipcv::DFT_SCALE);
  }
  clock_t endTime = clock();
  cout << "Elapsed time: "
       << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s] for " 
       << repetitions
       << " repetitions"
       << endl;
  cout << endl;

  // Perform 1-dimensional inverse DFT and time multiple repititions
  f = ipcv::Dft(F, ipcv::DFT_INVERSE);
  cout << "Inverse Fourier transform:" << endl;
  for (size_t idx = 0; idx < N; idx++) {
    cout << "f[" << idx << "]: " << f[idx] << endl;
  }
  startTime = clock();
  for (size_t idx = 0; idx < repetitions; idx++) {
    f = ipcv::Dft(F, ipcv::DFT_INVERSE);
  }
  endTime = clock();
  cout << "Elapsed time: "
       << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s] for " 
       << repetitions
       << " repetitions"
       << endl;
  cout << endl;

  // Create and display the original 1-dimensional function using cv::Mat
  cv::Mat f_Mat = cv::Mat::ones(N, 1, CV_64F);
  cout << "Original function (cv::Mat):" << endl;
  cout << "f:\n" << f_Mat << endl;
  cout << endl;

  // Perform 1-dimensional DFT and time multiple repititions (OpenCV)
  cv::Mat F_Mat;


  // *************************************************************************
  // INSERT YOUR CODE HERE
  // to compute the DFT using the OpenCV cv::dft function
  // *************************************************************************


  cout << "Fourier transform (OpenCV):" << endl;
  cout << "F:\n" << F_Mat << endl;
  startTime = clock();
  for (size_t idx = 0; idx < repetitions; idx++) {


     // **********************************************************************
     // INSERT YOUR CODE HERE
     // (same as above)
     // **********************************************************************


  }
  endTime = clock();
  cout << "Elapsed time: "
       << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s] for " 
       << repetitions
       << " repetitions"
       << endl;
  cout << endl;

  // Perform 1-dimensional inverse DFT and time multiple repititions (OpenCV)


  // *************************************************************************
  // INSERT YOUR CODE HERE
  // to compute the inverse DFT using the OpenCV cv::dft function
  // *************************************************************************


  cout << "Inverse Fourier transform (OpenCV):" << endl;
  cout << "f:\n" << f_Mat << endl;
  startTime = clock();
  for (size_t idx = 0; idx < repetitions; idx++) {


     // **********************************************************************
     // INSERT YOUR CODE HERE
     // (same as above)
     // **********************************************************************


  }
  endTime = clock();
  cout << "Elapsed time: "
       << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s] for " 
       << repetitions
       << " repetitions"
       << endl;
  cout << endl;

  // Read image in to cv::Mat
  string filename = "../data/images/misc/lenna_grayscale.pgm";         
  cv::Mat src;
  src = cv::imread(filename, cv::IMREAD_UNCHANGED);
  cout << "Image filename:" << endl;
  cout << filename << endl;
  cout << endl;

  // Perform 2-dimensional DFT and time execution (OpenCV)
  cv::Mat dft_input;
  cv::Mat dft_output;
  src.convertTo(dft_input, CV_64F);
  startTime = clock();


  // *************************************************************************
  // INSERT YOUR CODE HERE
  // to compute the DFT using the OpenCV cv::dft function
  // *************************************************************************


  endTime = clock();
  cout << "Fourier transform (OpenCV):" << endl;
  cout << "Elapsed time: "
       << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s]" 
       << endl;
  cout << endl;

  // Perform 2-dimensional inverse DFT and time execution (OpenCV)
  cv::Mat idft_output;
  startTime = clock();


  // *************************************************************************
  // INSERT YOUR CODE HERE
  // to compute the inverse DFT using the OpenCV cv::dft function
  // *************************************************************************


  endTime = clock();
  cout << "Inverse Fourier transform (OpenCV):" << endl;
  cout << "Elapsed time: "
       << (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC)
       << " [s]" 
       << endl;
  cout << endl;
  cv::Mat idft_output_display;
  idft_output.convertTo(idft_output_display, CV_8U); 

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


  // *************************************************************************
  // INSERT YOUR CODE HERE
  // to display the original image, the centered log|DFT|, and the inverse
  // transformation result image
  // *************************************************************************


  return EXIT_SUCCESS;
}
