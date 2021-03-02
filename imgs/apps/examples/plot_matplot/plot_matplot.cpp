#include <cmath>
#include <vector>

#include <matplot/matplot.h>

using namespace std;

int main() {
  std::vector<double> x = {0, 1, 2, 3, 4, 5, 6};
  std::vector<double> y = {0, 1, 4, 9, 16, 25, 36};

  matplot::plot(x, y);
  matplot::show();

  return EXIT_SUCCESS;
}
