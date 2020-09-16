/** Interface file for CSV file class
 *
 * \file imgs/utils/file/csvfile/CsvFile.h
 * \author Carl Salvaggio, Ph.D. (salvaggio@cis.rit.edu)
 * \date 06 March 2020
 */

#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace utils {

class CsvFile {
 public:
  /* Constructor (default)
   */
  CsvFile() {
    filename_ = "";
    header_lines_ = 0;
    label_line_ = 0;
  }

  /* Constructor
   *
   * \param[in] filename
   *     CSV filename
   * \param[in] header_lines
   *     number of header lines [default is 0]
   * \param[in] label_line
   *     line number that column labels appear on [default is 0]
   */
  CsvFile(std::string filename, size_t header_lines = 0,
          size_t label_line = 0) {
    auto exists = std::filesystem::exists(filename);
    if (!exists) {
      auto msg = "Specified file does not exist";
      throw std::runtime_error(msg);
    }

    filename_ = filename;
    header_lines_ = header_lines;
    label_line_ = label_line;
  }

  /* Filename getter
   */
  std::string filename() const { return filename_; }

  /* Filename setter
   *
   * \param[in] filename
   *     CSV filename
   */
  void set_filename(std::string filename) {
    auto exists = std::filesystem::exists(filename);
    if (!exists) {
      auto msg = "Specified file does not exist";
      throw std::runtime_error(msg);
    }

    filename_ = filename;
  }

  /* Header lines getter
   */
  size_t header_lines() const { return header_lines_; }

  /* Header lines setter
   *
   * \param[in] header_lines
   *     number of header lines [default is 0]
   */
  void set_header_lines(size_t header_lines) { header_lines_ = header_lines; }

  /* Label line getter
   */
  size_t label_line() const { return label_line_; }

  /* Label line setter
   *
   * \param[in] label_line
   *     line number that column labels appear on [default is 0]
   */
  void set_label_line(size_t label_line) { label_line_ = label_line; }

  /* Return data from desired column
   *
   * \param[in] column
   *     column number to return (begin numbering at 1) ... if column
   *     exceeds the number of columns present in the file, the last
   *     column will be returned
   *
   * \return
   *     std::vector containing the data from the desired column
   */
  template <typename T1>
  std::vector<T1> get_column(size_t column) const {
    if (column <= 0) {
      auto msg = "Requested column is out of range";
      throw std::runtime_error(msg);
    }

    std::ifstream f(filename_);

    std::string line;
    for (size_t idx = 1; idx <= header_lines_; idx++) {
      std::getline(f, line);
    }

    std::vector<T1> vector;
    while (std::getline(f, line)) {
      std::stringstream ss(line);
      std::string str;
      for (size_t idx = 1; idx <= column; idx++) {
        std::getline(ss, str, ',');
      }
      if (std::is_same_v<T1, double>) {
        vector.push_back(stod(str));
      } else if (std::is_same_v<T1, float>) {
        vector.push_back(stof(str));
      } else if (std::is_same_v<T1, int>) {
        vector.push_back(stoi(str));
      } else if (std::is_same_v<T1, long>) {
        vector.push_back(stol(str));
      } else if (std::is_same_v<T1, long double>) {
        vector.push_back(stold(str));
      } else if (std::is_same_v<T1, long long>) {
        vector.push_back(stoll(str));
      } else if (std::is_same_v<T1, unsigned long>) {
        vector.push_back(stoul(str));
      } else if (std::is_same_v<T1, unsigned long long>) {
        vector.push_back(stoull(str));
      } else {
        std::string msg = "Unmatch templated data type for string conversion";
        throw std::runtime_error(msg);
      }
    }

    f.close();

    return vector;
  }

  /* Return label/title from desired column
   *
   * \param[in] column
   *     column number to return (begin numbering at 1) ... if column
   *     exceeds the number of columns present in the file, the last
   *     column's label will be returned
   *
   * \return
   *     std::string containing the label from the desired column
   */
  std::string get_label(size_t column) const {
    if (column <= 0) {
      auto msg = "Requested column is out of range";
      throw std::runtime_error(msg);
    }

    if (label_line_ <= 0) {
      auto msg = "No line for labels specified";
      throw std::runtime_error(msg);
    }

    std::ifstream f(filename_);

    std::string line;
    for (size_t idx = 1; idx <= label_line_; idx++) {
      std::getline(f, line);
    }

    std::stringstream ss(line);
    std::string str;
    for (size_t idx = 1; idx <= column; idx++) {
      std::getline(ss, str, ',');
    }

    f.close();

    auto whitespace = " \n\r\t\f\v";
    auto str_begin = str.find_first_not_of(whitespace);
    auto str_end = str.find_last_not_of(whitespace);
    auto str_range = str_end - str_begin + 1;

    return str.substr(str_begin, str_range);
  }

 private:
  std::string filename_;
  size_t header_lines_;
  size_t label_line_;
};

}
