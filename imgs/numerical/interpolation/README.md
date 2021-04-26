# INTRODUCTION
This directory contains interpolation functions for the <span style="font-family:Courier">Eigen::VectorXd</span> type.

# USAGE
Within this build environment, all one needs to do to utilize these interpolation functions is to include the aggregate header file for interpolation

    #include "imgs/numerical/interpolation/interpolation.h"


and be sure to include <span style="font-family:Courier">    rit::numerical\_interpolation</span> in the <span style="font-family:Courier">target\_link\_libraries</span> directive in your project's <span style="font-family:Courier">CMakeLists.txt</span> file.


# EXAMPLES
Here is an example code using <span style="font-family:Courier">Interp1</span> to interpolate the provided vectors, <span style="font-family:Courier">x</span> and <span style="font-family:Courier">y</span>, at the points provided in <span style="font-family:Courier">x\_hat</span>

    #include <cmath>
    #include <iostream>

    #include "imgs/numerical/interpolation/interpolation.h"

    using namespace std;

    int main() {
      Eigen::VectorXd x(11);
      x << 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
      Eigen::VectorXd y(11);
      for (int idx = 0; idx < x.size(); idx++) {    
        y[idx] = pow(x[idx], 2);
      }

      Eigen::VectorXd xhat(6);
      xhat << 0, 1.7, 4, 6.2, 7.8, 10;

      Eigen::VectorXd yhat = numerical::Interp1(xhat, x, y);

      cout << "Original data:" << endl;
      for (size_t idx = 0; idx < static_cast<size_t>(x.size()); idx++) {
        cout << x[idx] << ", " << y[idx] << endl;
      }
      cout << endl;

      cout << "Interpolated data:" << endl;
      for (size_t idx = 0; idx < static_cast<size_t>(xhat.size()); idx++) {
        cout << xhat[idx] << ", " << yhat[idx] << endl;
      }
      cout << endl;
    }

# FUNCTIONS

###### Interp1
Returns interpolated values of a 1-D function (<span style="font-family:Courier">x</span>, <span style="font-family:Courier">y</span>) at specific query points (<span style="font-family:Courier">x_hat</span>) using linear interpolation

    Eigen::VectorXd Interp1(const Eigen::VectorXd& xhat,
                            const Eigen::VectorXd& x,
                            const Eigen::VectorXd& y);
# REQUIREMENTS
* C++ compiler that supports C++17 dialect/ISO standard

# DEPENDENCIES
* Eigen/Dense
