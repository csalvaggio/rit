#include <cmath>

namespace shapes {

class Triangle {
 public:
  Triangle() {
    // SAS triangle definition
    a_ = 1;
    C_ = M_PI / 2;
    b_ = 1;

    c_ = sqrt(a_ * a_ + b_ * b_ - 2 * a_ * b_ * cos(C_));
    A_ = acos((b_ * b_ + c_ * c_ - a_ * a_) / (2 * b_ * c_));
    B_ = acos((c_ * c_ + a_ * a_ - b_ * b_) / (2 * c_ * a_));
  }

  Triangle(double a, double C, double b) {
    // SAS triangle definition
    a_ = a;
    C_ = C * M_PI / 180.0;
    b_ = b;

    c_ = sqrt(a_ * a_ + b_ * b_ - 2 * a_ * b_ * cos(C_));
    A_ = acos((b_ * b_ + c_ * c_ - a_ * a_) / (2 * b_ * c_));
    B_ = acos((c_ * c_ + a_ * a_ - b_ * b_) / (2 * c_ * a_));
  }

  ~Triangle(){};

  double a() const { return a_; };
  void set_a(double a);

  double b() const { return b_; };
  void set_b(double b);

  double c() const { return c_; };

  double A() const { return A_; };

  double B() const { return B_; };

  double C() const { return C_; };
  void set_C(double C);

  double perimeter() const { return a_ + b_ + c_; }

  double area() const;

 private:
  double a_;
  double A_;
  double b_;
  double B_;
  double c_;
  double C_;
};

}  // namespace shapes
