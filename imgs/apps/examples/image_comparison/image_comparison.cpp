#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "imgs/ipcv/utils/Utils.h"

using namespace std;

int main() {
  string filename = "../data/images/misc/lenna_color.ppm";

  cv::Mat src = cv::imread(filename, cv::IMREAD_UNCHANGED);
  cout << "Image ..." << endl;
  cout << filename << endl;
  cout << "Dimensions: " << src.rows << "x" << src.cols << endl;
  cout << "Channels: " << src.channels() << endl;
  cout << endl;

  cv::Mat blur;
  cv::blur(src, blur, cv::Size(3, 3));
  cout << "Blurred image ..." << endl;
  cout << "Dimensions: " << blur.rows << "x" << blur.cols << endl;
  cout << "Channels: " << blur.channels() << endl;
  cout << endl;

  cv::Mat weights;
  weights.create(src.rows, src.cols, CV_32FC1);
  weights.setTo(cv::Scalar(1));

  std::vector<double> channel_psnr;
  auto psnr = ipcv::Psnr(src, blur, 255, weights, channel_psnr);
  // auto psnr = ipcv::Psnr(src, blur, 255, weights);
  // auto psnr = ipcv::Psnr(src, blur, 255, channel_psnr);
  // auto psnr = ipcv::Psnr(src, blur, 255);
  cout << "PSNR = " << psnr << endl;
  if (!channel_psnr.empty()) {
    cout << "PSNR (Channel 0) = " << channel_psnr[0] << endl;
    cout << "PSNR (Channel 1) = " << channel_psnr[1] << endl;
    cout << "PSNR (Channel 2) = " << channel_psnr[2] << endl;
  }
  cout << endl;

  std::vector<double> channel_rmse;
  auto rmse = ipcv::Rmse(src, blur, weights, channel_rmse);
  // auto rmse = ipcv::Rmse(src, blur, weights);
  // auto rmse = ipcv::Rmse(src, blur, channel_rmse);
  // auto rmse = ipcv::Rmse(src, blur);
  cout << "RMSE = " << rmse << endl;
  if (!channel_rmse.empty()) {
    cout << "RMSE (Channel 0) = " << channel_rmse[0] << endl;
    cout << "RMSE (Channel 1) = " << channel_rmse[1] << endl;
    cout << "RMSE (Channel 2) = " << channel_rmse[2] << endl;
  }
  cout << endl;

  int standard = 2000;
  string application = "graphic_arts";
  cv::Mat dE;
  auto deltae =
      ipcv::DeltaE(src, blur, 255, weights, dE, standard, application);
  // auto deltae = ipcv::DeltaE(src, blur, 255, weights, standard, application);
  // auto deltae = ipcv::DeltaE(src, blur, 255, dE, standard, application);
  // auto deltae = ipcv::DeltaE(src, blur, 255, standard, application);
  string label = "dE (" + to_string(standard) + ")";
  if (standard == 1994) {
    label += " (" + application + ")";
  }
  cout << label + " [avg] = " << deltae << endl;
  if (!dE.empty()) {
    double dE_min, dE_max;
    cv::minMaxLoc(dE, &dE_min, &dE_max);
    cout << label + " [min] = " << dE_min << endl;
    cout << label + " [max] = " << dE_max << endl;
    cout << endl;
    cv::imshow(label, dE / dE_max);
    cv::waitKey(0);
  }

  return EXIT_SUCCESS;
}
