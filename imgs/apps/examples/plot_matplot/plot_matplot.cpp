#include <cmath>
#include <vector>

#include <matplot/matplot.h>

using namespace std;

int main() {
  std::vector<double> x = {0, 1, 2, 3, 4, 5, 6};
  std::vector<double> y = {0, 1, 4, 9, 16, 25, 36};

  matplot::plot(x, y, "-s")
      ->color("r")
      .line_width(1)
      .marker_size(10)
      .marker_color("b")
      .marker_face_color({0.0, 1.0, 1.0});
  matplot::xlabel("x");
  matplot::ylabel("y");

  matplot::show();

  return EXIT_SUCCESS;
}
