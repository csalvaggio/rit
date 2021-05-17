/** Interface file for three-dimensional plotting
 *
 *  \file plot/plot3d/Plot3d.h
 *  \author Philip Salvaggio, Ph.D. (psscis@rit.edu)
 *          Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 19 April 2020
 */

#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <Eigen/Dense>

#include "imgs/third_party/gnuplot-iostream.h"

#include "imgs/plot/plot3d/Params.h"

namespace plot::plot3d {

void set_common_parameters(std::string& gp_msg, const plot3d::Params& params);

/** Plot three-dimensional data
 *
 *  \param[in] number_of_data_series
 *      number of data series provided to include in the current plot
 *  \param[in] params
 *      plot parameters object of type plot3d::Params
 *  \param[in] callback
 *      callback function to deliver x, y, and z data series
 */
template <class Callable>
void Plot3d(std::size_t number_of_data_series, const plot3d::Params& params,
            Callable callback) {
  std::string gp_msg;
  for (std::size_t series_idx = 0; series_idx < number_of_data_series;
       series_idx++) {
    gp_msg += "$data" + std::to_string(series_idx) + " << EOD\n";
    std::size_t point_idx = 0;
    double x;
    double y;
    double z;
    while (callback(series_idx, point_idx++, x, y, z)) {
      gp_msg += std::to_string(x) + " " + std::to_string(y) + " " +
                std::to_string(z) + "\n";
    }
    gp_msg += "EOD\n";
  }

  set_common_parameters(gp_msg, params);

  for (std::size_t series_idx = 0; series_idx < number_of_data_series;
       series_idx++) {
    if (series_idx == 0) {
      gp_msg += "splot $data" + std::to_string(series_idx);
      switch (params.linestyle(series_idx)) {
        case Params::LINES:
          gp_msg += " with lines linetype -1";
          break;
        case Params::POINTS:
          gp_msg += " with points pointtype 5";
          break;
        case Params::LINES + Params::POINTS:
          gp_msg += " with linespoints linestyle 5";
          break;
        default:
          gp_msg += " with lines linetype -1";
          break;
      }
      gp_msg += " linecolor '" + params.colors[series_idx];
    } else {
      gp_msg += "', $data" + std::to_string(series_idx);
      switch (params.linestyle(series_idx)) {
        case Params::LINES:
          gp_msg += " with lines linetype -1";
          break;
        case Params::POINTS:
          gp_msg += " with points pointtype 5";
          break;
        case Params::LINES + Params::POINTS:
          gp_msg += " with linespoints linestyle 5";
          break;
        default:
          gp_msg += " with lines linetype -1";
          break;
      }
      gp_msg += " linecolor '" + params.colors[series_idx];
    }
  }
  gp_msg += "'\n";

  Gnuplot gp;
  gp << gp_msg << std::endl;
}

/** Convenience function for plotting three-dimensional vector data
 *
 *  \param[in] x
 *     independent variable vector of type T1
 *  \param[in] y
 *     independent variable vector of type T2
 *  \param[in] z
 *     dependent variable vector of type T3
 *  \param[in] params
 *     plot parameters object of type plot3d::Params
 */
template <class T1, class T2, class T3>
void Plot3d(const std::vector<T1>& x, const std::vector<T2>& y,
            const std::vector<T3>& z, const plot3d::Params& params) {
  Plot3d(1, params,
         [&](std::size_t, std::size_t point_idx, double& x_value,
             double& y_value, double& z_value) {
           if (point_idx < x.size()) {
             x_value = x[point_idx];
             y_value = y[point_idx];
             z_value = z[point_idx];
             return true;
           }
           return false;
         });
}

/** Convenience function for plotting multiple three-dimensional vector data
 *
 *  \param[in] x
 *     independent variable vector of vectors of type T1
 *  \param[in] y
 *     independent variable vector of vectors of type T2
 *  \param[in] z
 *     dependent variable vector of vectors of type T3
 *  \param[in] params
 *     plot parameters object of type plot3d::Params
 */
template <class T1, class T2, class T3>
void Plot3d(const std::vector<std::vector<T1> >& x,
            const std::vector<std::vector<T2> >& y,
            const std::vector<std::vector<T3> >& z,
            const plot3d::Params& params) {
  Plot3d(x.size(), params,
         [&](std::size_t series_idx, std::size_t point_idx, double& x_value,
             double& y_value, double& z_value) {
           if (point_idx < x[series_idx].size()) {
             x_value = x[series_idx][point_idx];
             y_value = y[series_idx][point_idx];
             z_value = z[series_idx][point_idx];
             return true;
           }
           return false;
         });
}

/** Convenience function for plotting three-dimensional vector data stored
 *  in the row(s) of cv::Mat_
 *
 *  \param[in] x
 *     independent variable cv::Mat_ with 1 or multiple rows
 *  \param[in] y
 *     independent variable cv::Mat_ with 1 or multiple rows
 *  \param[in] z
 *     dependent variable cv::Mat_ with 1 or multiple rows
 *  \param[in] params
 *     plot parameters object of type plot3d::Params
 */
template <class T1, class T2, class T3>
void Plot3d(const cv::Mat_<T1> x, const cv::Mat_<T2> y, const cv::Mat_<T3> z,
            const plot3d::Params params) {
  Plot3d(x.rows, params,
         [&](std::size_t series_idx, std::size_t point_idx, double& x_value,
             double& y_value, double& z_value) {
           if (point_idx < (std::size_t)x.cols) {
             x_value = x(series_idx, point_idx);
             y_value = y(series_idx, point_idx);
             z_value = z(series_idx, point_idx);
             return true;
           }
           return false;
         });
}

/** Convenience function for plotting a cv::Mat_ as a three-dimensional
 *  surface plot (index values used to label the x and y axes)
 *
 *  \param[in] z
 *     dependent variable cv::Mat_ (single channel)
 *  \param[in] params
 *     plot parameters object of type plot3d::Params
 */
template <class T1>
void Plot3d(const cv::Mat_<T1> z, const plot3d::Params params) {
  Plot3d(1, params,
         [&](std::size_t, std::size_t point_idx, double& x_value,
             double& y_value, double& z_value) {
           if (point_idx < (std::size_t)z.rows * (std::size_t)z.cols) {
             int x_idx = point_idx % z.cols;
             x_value = x_idx;
             int y_idx = (point_idx / z.cols) % z.rows;
             y_value = y_idx;
             z_value = z(y_idx, x_idx);
             return true;
           }
           return false;
         });
}

/** Convenience function for plotting three-dimensional vector data stored
 *  in the column(s) of Eigen::Matrix (or Eigen::Vector)
 *
 *  \param[in] x
 *     independent variable Eigen::Matrix with 1 or multiple columns
 *  \param[in] y
 *     independent variable Eigen::Matrix with 1 or multiple columns
 *  \param[in] z
 *     dependent variable Eigen::Matrix with 1 or multiple columns
 *  \param[in] params
 *     plot parameters object of type plot3d::Params
 */
template <class T1, class T2, class T3, int rows, int cols, int options,
          int max_rows, int max_cols>
void Plot3d(const Eigen::Matrix<T1, rows, cols, options, max_rows, max_cols> x,
            const Eigen::Matrix<T2, rows, cols, options, max_rows, max_cols> y,
            const Eigen::Matrix<T3, rows, cols, options, max_rows, max_cols> z,
            const plot3d::Params params) {
  Plot3d(x.cols(), params,
         [&](std::size_t series_idx, std::size_t point_idx, double& x_value,
             double& y_value, double& z_value) {
           if (point_idx < (std::size_t)x.rows()) {
             x_value = x(point_idx, series_idx);
             y_value = y(point_idx, series_idx);
             z_value = z(point_idx, series_idx);
             return true;
           }
           return false;
         });
}

/** Convenience function for plotting three-dimensional data described by the
 *  provided function over the interval [x_min, x_max] and [y_min, y_max]
 *  as defined in the provided parameters
 *
 *  \param[in] f
 *     function you would like to plot (prototype cannot be ambiguous)
 *  \param[in] params
 *     plot parameters object of type plot3d::Params
 *  \param[in] nx
 *     the number of points in x at which to define the discrete
 *     representation of the function [default is 100]
 *  \param[in] ny
 *     the number of points in y at which to define the discrete
 *     representation of the function [default is 100]
 */
template <class CALLABLE>
void Plot3d(const CALLABLE f, plot::plot3d::Params params, std::size_t nx = 100,
            std::size_t ny = 100) {
  if (params.x_max() <= params.x_min()) {
    auto msg = "The provided parameter x_max is less than x_min";
    throw std::runtime_error(msg);
  }
  if (params.y_max() <= params.y_min()) {
    auto msg = "The provided parameter y_max is less than y_min";
    throw std::runtime_error(msg);
  }
  double dx = (static_cast<double>(params.x_max()) -
               static_cast<double>(params.x_min())) /
              (nx - 1);
  double dy = (static_cast<double>(params.y_max()) -
               static_cast<double>(params.y_min())) /
              (ny - 1);
  Plot3d(1, params,
         [&](std::size_t, std::size_t point_idx, double& x_value,
             double& y_value, double& z_value) {
           if (point_idx < nx * ny) {
             x_value = params.x_min() + (point_idx % nx) * dx;
             y_value = params.y_min() + ((point_idx / nx) % ny) * dy;
             z_value = f(x_value, y_value);
             return true;
           }
           return false;
         });
}

}
