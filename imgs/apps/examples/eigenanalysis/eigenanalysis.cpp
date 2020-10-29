#include <iostream>

#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

#include "imgs/plot/plot.h"

using namespace std;

int main() {
  // Typical data
  auto number_of_points = 24;
  Eigen::VectorXd x(number_of_points);
  x << 46, 22, 12, 50, 26, 40, 38, 34, 18, 24, 34, 36, 16, 32, 32, 28, 20, 40,
      26, 40, 38, 34, 50, 36;
  Eigen::VectorXd y(number_of_points);
  y << 58, 30, 16, 70, 36, 56, 46, 44, 88, 34, 66, 44, 56, 42, 38, 50, 30, 52,
      30, 52, 76, 74, 76, 54;

  /*
  // Linear data
  auto number_of_points = 10;
  Eigen::VectorXd x(number_of_points);
  x << 20, 25, 30, 35, 40, 45, 50, 55, 60, 65;
  Eigen::VectorXd y(number_of_points);
  y << 40, 45, 50, 55, 60, 65, 70, 75, 80, 85;
  */

  /*
  // Linear data (to demonstrate rotational invariance of eigenvalues)
  auto number_of_points = 10;
  Eigen::VectorXd x(number_of_points);
  x << 65, 60, 55, 50, 45, 40, 35, 30, 25, 20;
  Eigen::VectorXd y(number_of_points);
  y << 40, 45, 50, 55, 60, 65, 70, 75, 80, 85;
  */

  /*
  // Linear data (to further demonstrate rotational invariance of eigenvalues)
  auto number_of_points = 10;
  Eigen::VectorXd x(number_of_points);
  x << 75, 67.8, 60.6, 53.4, 46.2, 39, 31.8, 24.6, 17.4, 10;
  Eigen::VectorXd y(number_of_points);
  y << 60, 60, 60, 60, 60, 60, 60, 60, 60, 60;
  */

  /*
  // Car-shaped data
  auto number_of_points = 24;
  Eigen::VectorXd x(number_of_points);
  x << 20, 21, 22, 23, 24, 25,
       20, 21, 22, 23, 24, 25,
       21, 22, 23, 24, 25, 26,
       21, 22, 23, 24, 25, 26;
  Eigen::VectorXd y(number_of_points);
  y << 40, 41, 42, 43, 44, 45,
       41, 42, 43, 44, 45, 46,
       42, 43, 44, 45, 46, 47,
       43, 44, 45, 46, 47, 48;
  */

  /*
  // L-shaped data
  auto number_of_points = 10;
  Eigen::VectorXd x(number_of_points);
  x << 20, 25, 30, 35, 40, 45, 50, 45, 40, 35;
  Eigen::VectorXd y(number_of_points);
  y << 40, 45, 50, 55, 60, 65, 70, 75, 80, 85;
  */

  /*
  // T-shaped data
  auto number_of_points = 13;
  Eigen::VectorXd x(number_of_points);
  x << 20, 25, 30, 35, 40, 45, 50, 45, 40, 35, 55, 60, 65;
  Eigen::VectorXd y(number_of_points);
  y << 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 65, 60, 55;
  */

  // Place x and y vectors in a 2-column matrix
  Eigen::MatrixXd data(number_of_points, 2);
  data.col(0) = x;
  data.col(1) = y;
  cout << "Data:" << endl;
  cout << data << endl;
  cout << endl;

  // Compute the univariate means for the columns of "data"
  cout << "Means:" << endl;
  cout << data.colwise().mean() << endl;
  cout << endl;

  // Compute the zero-meaned version of "data"
  Eigen::MatrixXd zero_meaned = data.rowwise() - data.colwise().mean();
  cout << "Zero-meaned data:" << endl;
  cout << zero_meaned << endl;
  cout << endl;

  // Compute the univariate variances for the columns of "data"
  auto variance = zero_meaned.cwiseProduct(zero_meaned).colwise().sum() /
                  zero_meaned.rows();
  cout << "Variances:" << endl;
  cout << variance << endl;
  cout << endl;

  // Compute the covariance matrix of the zero-meaned version of "data"
  Eigen::MatrixXd cov = (zero_meaned.transpose() * zero_meaned) /
                        static_cast<double>(number_of_points);
  cout << "Covariance matrix:" << endl;
  cout << cov << endl;
  cout << endl;

  // Solve for the eigenvalues and eigenvectors of the covariance matrix
  //
  // If the matrix is self-adjoint (symmetric), then the eigenvalues are
  // guaranteed to be real-valued (use SelfAdjointEigenSolver)
  Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> es(cov);
  //
  // If the matrix is not symmetric, then the eigenvalues may be complex-
  // valued (use the general-purpose EigenSolver)
  //Eigen::EigenSolver<Eigen::MatrixXd> es(cov);

  cout << "Eigenvalues:" << endl;
  cout << es.eigenvalues() << endl;
  cout << endl;
  cout << "Eigenvectors [in columns]:" << endl;
  cout << es.eigenvectors() << endl;
  cout << endl;

  // Plot the original "data"
  plot::plot2d::Params params;
  params.set_title("Original Data");
  params.set_x_label("x");
  params.set_y_label("y");
  params.set_x_min(-148);
  params.set_x_max(148);
  params.set_y_min(-100);
  params.set_y_max(100);
  params.set_linestyle(0, params.POINTS);
  plot::plot2d::Plot2d(x, y, params);

  // Plot the zero-meaned version of "data"
  params.set_title("Original Data (Zero-Meaned)");
  plot::plot2d::Plot2d(static_cast<Eigen::VectorXd>(zero_meaned.col(0)),
                       static_cast<Eigen::VectorXd>(zero_meaned.col(1)),
                       params);

  // Compute values to depict the eigenvectors
  //auto vector1_slope =
  //    es.eigenvectors().col(0)(1).real() / es.eigenvectors().col(0)(0).real();
  //auto vector2_slope =
  //    es.eigenvectors().col(1)(1).real() / es.eigenvectors().col(1)(0).real();
  auto vector1_slope =
      es.eigenvectors().col(0)(1) / es.eigenvectors().col(0)(0);
  auto vector2_slope =
      es.eigenvectors().col(1)(1) / es.eigenvectors().col(1)(0);

  Eigen::VectorXd vector_x(number_of_points);
  auto range = params.x_max() - params.x_min();
  auto increment = range / (number_of_points - 1);
  for (int idx = 0; idx < number_of_points; idx++) {
    vector_x[idx] = params.x_min() + idx * increment;
  }
  auto vector1_y = vector1_slope * vector_x;
  auto vector2_y = vector2_slope * vector_x;

  // Plot the zero-meaned version of "data" and the depiction of the
  // eigenvectors (as axes)
  Eigen::MatrixXd xs(number_of_points, 3);
  xs << static_cast<Eigen::VectorXd>(zero_meaned.col(0)), vector_x, vector_x;
  Eigen::MatrixXd ys(number_of_points, 3);
  ys << static_cast<Eigen::VectorXd>(zero_meaned.col(1)), vector1_y, vector2_y;

  params.set_title("Eigenvectors");
  params.set_linestyle(0, params.POINTS);
  params.set_linestyle(1, params.LINES);
  params.set_linestyle(2, params.LINES);
  plot::plot2d::Plot2d(xs, ys, params);
}
