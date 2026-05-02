// files.cpp
#include "./files.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>


namespace dstr {


  // =====load_csv
  Result<Array<Resident>> load_csv(const string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
      return Err<Array<Resident>>(
        ErrorCode::IO_ERROR,
        "Cannot open file: " + path
      );
    }
    Array<Resident> records;
    string line;
    i32 line_number = 0;
    // Skip header line
    if (!std::getline(file, line)) {
      return Err<Array<Resident>>(
        ErrorCode::IO_ERROR,
        "File is empty or missing header: " + path
      );
    }
    while (std::getline(file, line)) {
      line_number++;
      // Skip blank lines
      if (line.empty() || line.find_first_not_of(" \t\r\n") == string::npos) {
        continue;
      }
      auto result = parse_line(line, line_number);
      if (!result) {
        // Report bad line but continue loading the rest
        // Callers may inspect the array size vs. expected count
        continue;
      }
      records.push_back(result.value());
    }
    if (records.empty()) {
      return Err<Array<Resident>>(
        ErrorCode::EMPTY_CONTAINER,
        "No valid records found in: " + path
      );
    }
    return Ok(records);
  }


  // =====parse_line
  // Expected CSV columns (0-based):
  //   0: ResidentID   1: Age   2: ModeOfTransport
  //   3: DailyDistance(km)   4: CarbonEmissionFactor   5: AvgDaysPerMonth
  Result<Resident> parse_line(const string& line, i32 line_number) {
    std::istringstream ss(line);
    string token;
    Resident r;
    // --- Column 0: ResidentID ---
    if (!std::getline(ss, token, ',')) {
      return Err<Resident>(
        ErrorCode::INVALID_ARGUMENT,
        "Line " + std::to_string(line_number) + ": missing ResidentID"
      );
    }
    r.id = token;
    r.city = parse_city_from_id(token);
    // --- Column 1: Age ---
    if (!std::getline(ss, token, ',')) {
      return Err<Resident>(
        ErrorCode::INVALID_ARGUMENT,
        "Line " + std::to_string(line_number) + ": missing Age"
      );
    }
    try {
      r.age = std::stoi(token);
    }
    catch (...) {
      return Err<Resident>(
        ErrorCode::INVALID_ARGUMENT,
        "Line " + std::to_string(line_number) + ": invalid Age value"
      );
    }
    // --- Column 2: ModeOfTransport ---
    if (!std::getline(ss, token, ',')) {
      return Err<Resident>(
        ErrorCode::INVALID_ARGUMENT,
        "Line " + std::to_string(line_number) + ": missing ModeOfTransport"
      );
    }
    auto transport_result = parse_transport(token);
    if (!transport_result) {
      return Err<Resident>(
        ErrorCode::INVALID_ARGUMENT,
        "Line " + std::to_string(line_number) + ": " + transport_result.error().message()
      );
    }
    r.transport = transport_result.value();
    // --- Column 3: DailyDistance (km) ---
    if (!std::getline(ss, token, ',')) {
      return Err<Resident>(
        ErrorCode::INVALID_ARGUMENT,
        "Line " + std::to_string(line_number) + ": missing DailyDistance"
      );
    }
    try {
      r.daily_distance_km = std::stoi(token);
    }
    catch (...) {
      return Err<Resident>(
        ErrorCode::INVALID_ARGUMENT,
        "Line " + std::to_string(line_number) + ": invalid DailyDistance value"
      );
    }
    // --- Column 4: CarbonEmissionFactor ---
    if (!std::getline(ss, token, ',')) {
      return Err<Resident>(
        ErrorCode::INVALID_ARGUMENT,
        "Line " + std::to_string(line_number) + ": missing CarbonEmissionFactor"
      );
    }
    try {
      r.carbon_emission_factor = std::stof(token);
    }
    catch (...) {
      return Err<Resident>(
        ErrorCode::INVALID_ARGUMENT,
        "Line " + std::to_string(line_number) + ": invalid CarbonEmissionFactor value"
      );
    }
    // --- Column 5: AvgDaysPerMonth ---
    if (!std::getline(ss, token, ',')) {
      return Err<Resident>(
        ErrorCode::INVALID_ARGUMENT,
        "Line " + std::to_string(line_number) + ": missing AvgDaysPerMonth"
      );
    }
    try {
      r.avg_days_per_month = std::stoi(token);
    }
    catch (...) {
      return Err<Resident>(
        ErrorCode::INVALID_ARGUMENT,
        "Line " + std::to_string(line_number) + ": invalid AvgDaysPerMonth value"
      );
    }
    return Ok(r);
  }


  Result<ModeOfTransport> parse_transport(const string& s) {
    // Trim and lowercase for comparison
    string cleaned;
    cleaned.reserve(s.size());
    for (char c : s) {
      if (c != '\r' && c != '\n' && c != '"') {
        cleaned += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
      }
    }
    // Remove leading/trailing spaces
    auto first = cleaned.find_first_not_of(' ');
    auto last = cleaned.find_last_not_of(' ');
    if (first == string::npos) {
      return Err<ModeOfTransport>(
        ErrorCode::INVALID_ARGUMENT,
        "Empty transport token"
      );
    }
    cleaned = cleaned.substr(first, last - first + 1);
    if (cleaned == "car") { return Ok(ModeOfTransport::CAR); }
    if (cleaned == "bus") { return Ok(ModeOfTransport::BUS); }
    if (cleaned == "bicycle") { return Ok(ModeOfTransport::BICYCLE); }
    if (cleaned == "walking") { return Ok(ModeOfTransport::WALKING); }
    if (cleaned == "carpool") { return Ok(ModeOfTransport::CARPOOL); }
    if (cleaned == "school bus" || cleaned == "schoolbus" || cleaned == "school_bus") {
      return Ok(ModeOfTransport::SCHOOL_BUS);
    }
    return Err<ModeOfTransport>(
      ErrorCode::INVALID_ARGUMENT,
      "Unknown transport mode: '" + s + "'"
    );
  }


} // namespace dstr
