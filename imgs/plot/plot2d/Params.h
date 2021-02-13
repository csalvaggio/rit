/** Interface file for plot parameter specification
 *
 *  \file plot/plot2d/Params.h
 *  \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 *  \date 4 April 2020
 */

#pragma once

#include <string>

namespace plot::plot2d {

class Params {
 public:
  /** Constructors for the plot parameters object
   *
   *  \param[in] x_label a string containing the x-axis label
   *  \param[in] y_label a string containing the y-axis label
   */
  Params();

  Params(std::string x_label, std::string y_label);

  /** Destructor for the plot parameters object
   */
  ~Params();

  /** Accessor and mutator for the terminal_type member
   */
  std::string terminal_type() const;
  void set_terminal_type(std::string terminal_type);

  /** Accessor and mutator for the font_face member
   */
  std::string font_face() const;
  void set_font_face(std::string font_face);

  /** Accessor and mutator for the font_size member
   */
  int font_size() const;
  void set_font_size(int font_size);

  /** Accessor and mutator for the x_label member
   */
  std::string x_label() const;
  void set_x_label(std::string x_label);

  /** Accessor and mutator for the y_label member
   */
  std::string y_label() const;
  void set_y_label(std::string y_label);

  /** Accessor and mutator for the title member
   */
  std::string title() const;
  void set_title(std::string title);

  /** Accessor and mutator for the x_min and x_max members
   */
  double x_min() const;
  void set_x_min(double x_min);
  double x_max() const;
  void set_x_max(double x_max);

  /** Accessor and mutator for the y_min and y_max members
   */
  double y_min() const;
  void set_y_min(double y_min);
  double y_max() const;
  void set_y_max(double y_max);

  /** Accessor and mutator for the x_tics and y_tics members
   */
  bool x_tics() const;
  void set_x_tics(bool x_tics);
  bool y_tics() const;
  void set_y_tics(bool y_tics);

  /** Accessor and mutator for the linestyle member
   */
  int linestyle() const;
  void set_linestyle(int linestyle);
  int linestyle(size_t series_idx) const;
  void set_linestyle(size_t series_idx, int linestyle);

  /** Accessor and mutator for the xvline member
   */
  double xvline() const;
  void set_xvline(double xvline);

  /** Accessor and mutator for the destination filename member
   */
  std::string destination_filename() const;
  void set_destination_filename(std::string dst_filename);

  /** Print function to carry out a diagnostic dump of object values
   */
  void Print() const;

  /** Class public constants
   */
  const std::string colors[6] = {"blue", "green",   "red",
                                 "cyan", "magenta", "yellow"};

  enum LineStyle {
    LINES = 0x01,  // Use lines
    POINTS = 0x02  // Use points
  };

 private:
  std::string terminal_type_ = "qt";
  std::string font_face_ = "Courier";
  int font_size_ = 12;
  std::string x_label_ = "";
  std::string y_label_ = "";
  std::string title_ = "";
  double x_min_ = 0;
  double x_max_ = -1;
  double y_min_ = 0;
  double y_max_ = -1;
  bool x_tics_ = false;
  bool y_tics_ = false;
  int linestyle_[6] = {LINES, LINES, LINES, LINES, LINES, LINES};
  double xvline_ = 0;
  std::string dst_filename_ = "";
};
}
