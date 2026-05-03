#pragma once

#include "./aliases.h"
#include "./string_helpers.h"


namespace dstr {


	enum class ModeOfTransport {
		CAR,
		BUS,
		BICYCLE,
		WALKING,
		CARPOOL,
		SCHOOL_BUS,
		UNKNOWN
	};

	enum class City {
		CITY_A,
		CITY_B,
		CITY_C,
		UNKNOWN
	};

	enum class AgeGroup {
		CHILDREN_TEENAGERS,    // 6-17
		YOUNG_ADULTS,          // 18-25
		WORKING_ADULTS_EARLY,  // 26-45
		WORKING_ADULTS_LATE,   // 46-60
		SENIOR_CITIZENS,       // 61-100
		UNKNOWN
	};


	static City parse_city_from_id(const string& resident_id) {
		if (resident_id.empty()) { return City::UNKNOWN; }
		char letter = static_cast<char>(std::toupper(static_cast<unsigned char>(resident_id[0])));
		if (letter == 'A') { return City::CITY_A; }
		if (letter == 'B') { return City::CITY_B; }
		if (letter == 'C') { return City::CITY_C; }
		return City::UNKNOWN;
	}

	static ModeOfTransport parse_transport(const string& s) {
		string cleaned;
		cleaned.reserve(s.size());
		for (char c : s) {
			if (c != '\r' && c != '\n' && c != '"') {
				cleaned += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
			}
		}
		cleaned = trim(cleaned);
		if (cleaned.empty()) {
			return ModeOfTransport::UNKNOWN;
			//return Err<ModeOfTransport>(ErrorCode::INVALID_ARGUMENT, "Empty transport token");
		}
		if (cleaned == "car") {
			return ModeOfTransport::CAR;
		}
		if (cleaned == "bus") {
			return ModeOfTransport::BUS;
		}
		if (cleaned == "bicycle") {
			return ModeOfTransport::BICYCLE;
		}
		if (cleaned == "walking") {
			return ModeOfTransport::WALKING;
		}
		if (cleaned == "carpool") {
			return ModeOfTransport::CARPOOL;
		}
		if (cleaned == "school bus" || cleaned == "schoolbus" || cleaned == "school_bus") {
			return ModeOfTransport::SCHOOL_BUS;
		}
		return ModeOfTransport::UNKNOWN;
		//return Err<ModeOfTransport>(ErrorCode::INVALID_ARGUMENT, "Unknown transport mode: '" + s + "'");
	}

	static string transport_name(ModeOfTransport t) {
		switch (t) {
		case ModeOfTransport::CAR:        return "Car";
		case ModeOfTransport::BUS:        return "Bus";
		case ModeOfTransport::BICYCLE:    return "Bicycle";
		case ModeOfTransport::WALKING:    return "Walking";
		case ModeOfTransport::CARPOOL:    return "Carpool";
		case ModeOfTransport::SCHOOL_BUS: return "School Bus";
		default:                          return "Unknown";
		}
	}

	static string city_name(City c) {
		switch (c) {
		case City::CITY_A: return "City A (Metropolitan)";
		case City::CITY_B: return "City B (University Town)";
		case City::CITY_C: return "City C (Suburban/Rural)";
		default:           return "Unknown City";
		}
	}

	static string age_group_name(AgeGroup g) {
		switch (g) {
		case AgeGroup::CHILDREN_TEENAGERS:   return "Children & Teenagers (6-17)";
		case AgeGroup::YOUNG_ADULTS:         return "Young Adults (18-25)";
		case AgeGroup::WORKING_ADULTS_EARLY: return "Working Adults Early (26-45)";
		case AgeGroup::WORKING_ADULTS_LATE:  return "Working Adults Late (46-60)";
		case AgeGroup::SENIOR_CITIZENS:      return "Senior Citizens (61-100)";
		default:                             return "Unknown Age Group";
		}
	}

} // namespace dstr
