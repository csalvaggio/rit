#include <iostream>

#include <opencv2/core.hpp>

#include "imgs/ipcv/utils/Utils.h"
#include "imgs/plot/plot.h"

using namespace std;

int main(int argc, char* argv[]) {
  double standard_deviation = 2;
  int rows = 11;
  int cols = 11;
  cv::Mat exponent;
  cv::pow(ipcv::Dist(rows, cols) / standard_deviation, 2, exponent);
  cv::Mat gauss;
  cv::exp(-0.5 * exponent, gauss);

  plot::plot3d::Params params;
  params.set_x_label("x");
  params.set_y_label("y");
  params.set_z_label("z");
  params.set_title("");
  params.set_x_tics(false);
  params.set_y_tics(false);
  params.set_z_tics(false);
  params.set_mesh(true);
  params.set_mesh_x_size(cols);
  params.set_mesh_y_size(rows);
  params.set_palette_mapping(false);
  params.set_declination(60);
  params.set_azimuth(30);
  params.set_scale(1);
  params.set_z_scale(1);
  params.set_linestyle(params.LINES);

  // Vector
  std::vector<double> x;
  std::vector<double> y;
  std::vector<double> z;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      x.push_back(col - cols / 2);
      y.push_back(row - rows / 2);
      z.push_back(gauss.at<double>(row, col));
    }
  }
  plot::plot3d::Plot3d(x, y, z, params);

  // cv::Mat (surface plot)
  plot::plot3d::Plot3d<double>(gauss, params);

  params.Print();

  return EXIT_SUCCESS;
}
