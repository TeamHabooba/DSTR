#pragma once


#include <iostream>
#include "./aliases.h"
#include "./strings.h"


using std::string;


namespace dstr {


  // Constants

  static constexpr int TABLE_WIDTH = 90;
  static constexpr int COL_IDX = 5;
  static constexpr int COL_ID = 8;
  static constexpr int COL_CITY = 9;
  static constexpr int COL_AGE = 5;
  static constexpr int COL_TRANSPORT = 12;
  static constexpr int COL_DIST = 6;
  static constexpr int COL_FACTOR = 8;
  static constexpr int COL_DAYS = 5;
  static constexpr int COL_EMISSION = 10;


  // Helpers

  static string trim(const string& s) {
    auto start = std::find_if_not(s.begin(), s.end(), ::isspace);
    auto end = std::find_if_not(s.rbegin(), s.rend(), ::isspace).base();
    return (start < end) ? string(start, end) : "";
  }

  static string pad_right(const string& s, const int width) {
    int size = static_cast<int>(s.size());
    if (size >= width) {
      return s.substr(0, width);
    }
    return s + string(width - size, ' ');
  }

  static string pad_left(const string& s, const int width) {
    int size = static_cast<int>(s.size());
    if (size >= width) {
      return s.substr(0, width);
    }
    return string(width - size, ' ') + s;
  }

  static  string format_float(const float value, const int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
  }

  static void print_separator(std::ostream& os, const char c, const int width) {
    os << string(width, c) << '\n';
  }

  static void print_header(std::ostream& os, const string& title) {
    print_separator(os, '=', TABLE_WIDTH);
    int padding = (TABLE_WIDTH - static_cast<int>(title.size())) / 2;
    if (padding > 0) {
      os << string(padding, ' ');
    }
    os << title << '\n';
    print_separator(os, '=', TABLE_WIDTH);
  }

  static void print_residents_table_header(std::ostream& os) {
    print_separator(os, '-', TABLE_WIDTH);
    os << "| "
      << pad_right("#", COL_IDX)
      << "| " << pad_right("ID", COL_ID)
      << "| " << pad_right("City", COL_CITY)
      << "| " << pad_right("Age", COL_AGE)
      << "| " << pad_right("Transport", COL_TRANSPORT)
      << "| " << pad_right("Dist", COL_DIST)
      << "| " << pad_right("Factor", COL_FACTOR)
      << "| " << pad_right("Days", COL_DAYS)
      << "| " << pad_right("Emission", COL_EMISSION)
      << "|\n";
    print_separator(os, '-', TABLE_WIDTH);
  }


} // namespace dstr
