// files.h
#pragma once


#include <fstream>

#include "../common/common.h"
#include "../common/resident.h"
#include "../array/array.h"
#include "../list/list.h"


namespace dstr {


  // Load all residents from a CSV file
  Result<Array<Resident>> load_csv(const string& path);

  // Parse a single non-header CSV line (1-based line_number for error messages)
  Result<Resident> parse_line(const string& line, i32 line_number);

  // Parse ModeOfTransport from a string token (case-insensitive)
  Result<ModeOfTransport> parse_transport(const string& s);

  // Derive City from the first character of the resident ID ("A001" -> City::CITY_A)
  City parse_city_from_id(const string& resident_id);

  // Human-readable helpers
  string transport_name(ModeOfTransport t);
  string city_name(City c);
  string age_group_name(AgeGroup g);


} // namespace dstr
