namespace shapes {

class Rectangle {
 public:
  Rectangle() {
    length_ = 1;
    width_ = 1;
  }

  Rectangle(double length, double width) {
    length_ = length;
    width_ = width;
  }

  ~Rectangle() {};

  double length() const { return length_; }
  void set_length(double length) { length_ = length; }

  double width() const { return width_; }
  void set_width(double width) { width_ = width; }

  double perimeter() const { return 2 * length_ + 2 * width_; }

  double area() const { return length_ * width_; }

 private:
  double length_;
  double width_;
};

}  // namespace shapes
