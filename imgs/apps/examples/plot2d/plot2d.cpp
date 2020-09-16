#include <cmath>
#include <vector>

#include <opencv2/core.hpp>

#include "imgs/plot/plot.h"

using namespace std;

int main(int argc, char* argv[]) {
  plot::plot2d::Params params;
  params.set_x_label("x");
  params.set_y_label("y");
  params.set_linestyle(params.LINES + params.POINTS);

  // Vector
  std::vector<double> x;
  std::vector<double> y;
  for (int i = 0; i <= 50; i++) {
    x.push_back((double)i);
    y.push_back((double)i * 50);
  }

  plot::plot2d::Plot2d(x, y, params);

  // Vector of Vectors
  std::vector<double> x1;
  std::vector<double> y1;
  for (int i = 0; i <= 50; i++) {
    x1.push_back((double)i);
    y1.push_back((double)i * 50);
  }

  std::vector<double> x2;
  std::vector<double> y2;
  for (int i = 0; i <= 50; i=i+10) {
    x2.push_back((double)i);
    y2.push_back((double)i * (double)i);
  }

  std::vector< std::vector<double> > xs;
  xs.push_back(x1);
  xs.push_back(x2);

  std::vector< std::vector<double> > ys;
  ys.push_back(y1);
  ys.push_back(y2);

  plot::plot2d::Plot2d(xs, ys, params);

  // Single vector in a cv::Mat_<double>
  cv::Mat_<double> xm = cv::Mat_<double>::zeros(1, 51);
  cv::Mat_<double> ym = cv::Mat_<double>::zeros(1, 51);
  for (int i = 0; i <= 50; i++) {
    xm(0, i) = i;
    ym(0, i) = i * 50;
  }

  plot::plot2d::Plot2d(xm, ym, params);

  // Multiple vectors in a cv::Mat_<double>
  cv::Mat_<double> xms;
  cv::Mat_<double> yms;
  xms = cv::Mat_<double>::zeros(2, 51);
  yms = cv::Mat_<double>::zeros(2, 51);
  for (int i = 0; i <= 50; i++) {
    xms(0, i) = i;
    yms(0, i) = i * 50;
    xms(1, i) = i;
    yms(1, i) = i * i;
  }

  plot::plot2d::Plot2d(xms, yms, params);

  // Single vector in a cv::Mat_<int>
  cv::Mat_<int> xmi = cv::Mat_<int>::zeros(1, 51);
  cv::Mat_<int> ymi = cv::Mat_<int>::zeros(1, 51);
  for (int i = 0; i <= 50; i++) {
    xmi(0, i) = i;
    ymi(0, i) = i * 50;
  }

  plot::plot2d::Plot2d(xmi, ymi, params);

  params.Print();

  // Using a function
  params.set_x_min(0);
  params.set_x_max(4 * M_PI);

  plot::plot2d::Plot2d([](auto x) { return cos(x); }, params);

  return EXIT_SUCCESS;
}
