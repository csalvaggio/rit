/** Implementation file for plot parameter specification
 *
 *  \file plot/plot3d/Params.cpp
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 19 April 2020
 */

#include "Params.h"

#include <cmath>
#include <iostream>

using namespace std;

namespace plot::plot3d {

Params::Params() {}

Params::Params(std::string x_label, std::string y_label, std::string z_label) {
  x_label_ = x_label;
  y_label_ = y_label;
  z_label_ = z_label;
}

Params::~Params() {}

std::string Params::terminal_type() const { return terminal_type_; }
void Params::set_terminal_type(std::string terminal_type) {
  terminal_type_ = terminal_type;
}

std::string Params::font_face() const { return font_face_; }
void Params::set_font_face(std::string font_face) { font_face_ = font_face; }

int Params::font_size() const { return font_size_; }
void Params::set_font_size(int font_size) { font_size_ = font_size; }

std::string Params::x_label() const { return x_label_; }
void Params::set_x_label(std::string x_label) { x_label_ = x_label; }

std::string Params::y_label() const { return y_label_; }
void Params::set_y_label(std::string y_label) { y_label_ = y_label; }

std::string Params::z_label() const { return z_label_; }
void Params::set_z_label(std::string z_label) { z_label_ = z_label; }

std::string Params::title() const { return title_; }
void Params::set_title(std::string title) { title_ = title; }

double Params::x_min() const { return x_min_; }
void Params::set_x_min(double x_min) { x_min_ = x_min; }
double Params::x_max() const { return x_max_; }
void Params::set_x_max(double x_max) { x_max_ = x_max; }

double Params::y_min() const { return y_min_; }
void Params::set_y_min(double y_min) { y_min_ = y_min; }
double Params::y_max() const { return y_max_; }
void Params::set_y_max(double y_max) { y_max_ = y_max; }

double Params::z_min() const { return z_min_; }
void Params::set_z_min(double z_min) { z_min_ = z_min; }
double Params::z_max() const { return z_max_; }
void Params::set_z_max(double z_max) { z_max_ = z_max; }

bool Params::x_tics() const { return x_tics_; }
void Params::set_x_tics(bool x_tics) { x_tics_ = x_tics; }
bool Params::y_tics() const { return y_tics_; }
void Params::set_y_tics(bool y_tics) { y_tics_ = y_tics; }
bool Params::z_tics() const { return z_tics_; }
void Params::set_z_tics(bool z_tics) { z_tics_ = z_tics; }

bool Params::mesh() const { return mesh_; }
void Params::set_mesh(bool mesh) { mesh_ = mesh; }

int Params::mesh_x_size() const { return mesh_x_size_; }
void Params::set_mesh_x_size(int mesh_x_size) {
  if (mesh_x_size <= 0) {
    mesh_x_size_ = 0;
  } else if (mesh_x_size < 2) {
    mesh_x_size_ = 2;
  } else if (mesh_x_size > 1000) {
    mesh_x_size_ = 1000;
  } else {
    mesh_x_size_ = mesh_x_size;
  }
}
int Params::mesh_y_size() const { return mesh_y_size_; }
void Params::set_mesh_y_size(int mesh_y_size) {
  if (mesh_y_size <= 0) {
    mesh_y_size_ = 0;
  } else if (mesh_y_size < 2) {
    mesh_y_size_ = 2;
  } else if (mesh_y_size > 1000) {
    mesh_y_size_ = 1000;
  } else {
    mesh_y_size_ = mesh_y_size;
  }
}

bool Params::palette_mapping() const { return palette_mapping_; }
void Params::set_palette_mapping(bool palette_mapping) {
  palette_mapping_ = palette_mapping;
}

int Params::declination() const { return declination_; }
void Params::set_declination(int declination) {
  if (declination < 0) {
    declination_ = 0;
  } else if (declination > 180) {
    declination_ = 180;
  } else {
    declination_ = declination;
  }
}
int Params::azimuth() const { return azimuth_; }
void Params::set_azimuth(int azimuth) {
  azimuth_ = abs(azimuth % 360);
}

double Params::scale() const { return scale_; }
void Params::set_scale(double scale) { scale_ = scale; }
double Params::z_scale() const { return z_scale_; }
void Params::set_z_scale(double z_scale) { z_scale_ = z_scale; }

int Params::linestyle() const { return linestyle_[0]; }
void Params::set_linestyle(int linestyle) {
  auto number_linestyles = sizeof(linestyle_) / sizeof(linestyle_[0]);
  for (size_t idx = 0; idx < number_linestyles; idx++) {
    linestyle_[idx] = linestyle;
  }
}
int Params::linestyle(size_t series_idx) const {
  auto number_linestyles = sizeof(linestyle_) / sizeof(linestyle_[0]);
  return linestyle_[series_idx % number_linestyles];
}
void Params::set_linestyle(size_t series_idx, int linestyle) {
  auto number_linestyles = sizeof(linestyle_) / sizeof(linestyle_[0]);
  linestyle_[series_idx % number_linestyles] = linestyle;
}

std::string Params::destination_filename() const { return dst_filename_; }
void Params::set_destination_filename(std::string dst_filename) {
  dst_filename_ = dst_filename;
}

void Params::Print() const {
  cout << "Params dump:" << endl;
  cout << "  terminal_type: " << terminal_type_ << endl;
  cout << "  font_face: " << font_face_ << endl;
  cout << "  font_size: " << font_size_ << endl;
  cout << "  x_label: " << x_label_ << endl;
  cout << "  y_label: " << y_label_ << endl;
  cout << "  z_label: " << z_label_ << endl;
  cout << "  title: " << title_ << endl;
  cout << "  x_min: " << x_min_ << endl;
  cout << "  x_max: " << x_max_ << endl;
  if (x_min_ >= x_max_) {
    cout << "  *** Autoscaling being used for the x-axis" << endl;
  }
  cout << "  y_min: " << y_min_ << endl;
  cout << "  y_max: " << y_max_ << endl;
  if (y_min_ >= y_max_) {
    cout << "  *** Autoscaling being used for the y-axis" << endl;
  }
  cout << "  z_min: " << z_min_ << endl;
  cout << "  z_max: " << z_max_ << endl;
  if (z_min_ >= z_max_) {
    cout << "  *** Autoscaling being used for the z-axis" << endl;
  }
  cout << "  x_tics: " << x_tics_ << endl;
  cout << "  y_tics: " << y_tics_ << endl;
  cout << "  y_tics: " << z_tics_ << endl;
  cout << "  mesh: " << mesh_ << endl;
  cout << "  mesh_x_size: " << mesh_x_size_ << endl;
  cout << "  mesh_y_size: " << mesh_y_size_ << endl;
  cout << "  palette_mapping: " << palette_mapping_ << endl;
  cout << "  declination: " << declination_ << endl;
  cout << "  azimuth: " << azimuth_ << endl;
  cout << "  scale: " << scale_ << endl;
  cout << "  z_scale: " << z_scale_ << endl;
  cout << "  dst_filename: " << dst_filename_ << endl;
}
}
