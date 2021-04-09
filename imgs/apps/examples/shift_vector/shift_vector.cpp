#include <iostream>

#include <Eigen/Dense>

#include "imgs/utils/shift_vector/ShiftVector.h"

using namespace std;

int main() {
  int offset = -2;
  cout << "Offset:" << endl;
  cout << offset << endl;

  Eigen::VectorXd x(5);
  x << 1, 2, 3, 4, 5;

  cout << "Original column vector:" << endl;
  cout << x << endl;

  cout << "Shifted column vector:" << endl;
  cout << utils::ShiftVector(x, offset) << endl;

  Eigen::RowVectorXd y(5);
  y << 1, 2, 3, 4, 5;

  cout << "Original row vector:" << endl;
  cout << y << endl;

  cout << "Shifted row vector:" << endl;
  cout << utils::ShiftVector(y, offset) << endl;
}
