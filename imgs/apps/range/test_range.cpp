#include <iostream>
#include <vector>

#include "imgs/numerical/numerical.h"

using namespace std;

int main() {
  auto print_vector = [](const auto& v) -> void {
    for (auto element : v) {
      cout << element << " ";
    }
    cout << endl;
  };

  auto v1 = numerical::Range(2, 7);
  print_vector(v1);

  auto v2 = numerical::Range(2.0, 7.0, 11);
  print_vector(v2);

  auto v3 = numerical::Range(10);
  print_vector(v3);
}

