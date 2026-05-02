// sТrings.h
#pragma once


#include "./cpp_version.h"


// NOTE: dangerous macro usage. Fix later.
// CSTR = constant string value
// SCSTR = static constant string value
#if CPP_VERSION >= 17
#define CSTR constexpr std::string_view
#define SCSTR static constexpr std::string_view
#else
#define CSTR const char*
#endif


namespace dstr::strings {


  SCSTR MSG_MAIN_MENU_INTRO = "Welcome!\nYou are in the main menu. Choose an option and press ENTER to interact with the program.";
  SCSTR MSG_MAIN_MENU_OPTIONS = "1.Array implementation\n2.List implementation\n3.Credits\n0.Exit";
  SCSTR MSG_DESC = "This is Data Structures (DSTR) assignment of group DSTR32.";
  SCSTR MSG_DESC_MEMBERS = "Group members are:\nTP081705 - Kurapatkin Aliaksandr (Alex) (Leader)\nTP082557 - Leon Frank Aminiel (Leo)\nTP082459 - Mohamed Abdifatah Ali (Moha)";
  SCSTR MSG_DESC_DOCS = "All the documentation can be found at our GitHub repository: https://github.com/TeamHabooba/DSTR";
  SCSTR MSG_DESC_DOCS_FILES = "Refer to README.md file or docs directory.";


  SCSTR ERR_GENERAL = "Error occured: ";
  SCSTR ERR_TERMINATED = "Program was terminated by user.";
  SCSTR ERR_NOT_IMPLEMENTED = "This method or class is yet to be implemented.";
  SCSTR ERR_INVALID_ARGUMENT = "Invalid method/function argument.";
  SCSTR ERR_NOT_NUMBER = "Not a number.";

  SCSTR ERR_TRIM_ERROR = "trim() finished with an error.";
  SCSTR ERR_MENU_OPT_BELOW_ZERO = "Menu option number was less than zero.";

  SCSTR ERR_CANT_OPEN_FILE = "Cannot open file: ";
  SCSTR ERR_FILE_EMPTY = "File is empty: ";
  SCSTR ERR_FILE_NO_RECORDS = "No valid records found in file: ";

  SCSTR ERR_LINE_MISSING_RID = ": missing ResidentID.";
  SCSTR ERR_LINE_INVALID_RID = ": invalid ResidentID value.";
  SCSTR ERR_LINE_MISSING_AGE = ": missing Age.";
  SCSTR ERR_LINE_INVALID_AGE = ": invalid Age value.";
  SCSTR ERR_LINE_MISSING_MOT = ": missing ModeOfTransport.";
  SCSTR ERR_LINE_INVALID_MOT = ": invalid ModeOfTransport value.";
  SCSTR ERR_LINE_MISSING_DD = ": missing DailyDistance.";
  SCSTR ERR_LINE_INVALID_DD = ": invalid DailyDistance value.";
  SCSTR ERR_LINE_MISSING_CEF = ": missing CarbonEmissionFactor.";
  SCSTR ERR_LINE_INVALID_CEF = ": invalid CarbonEmissionFactor value.";
  SCSTR ERR_LINE_MISSING_ADM = ": missing AvgDaysPerMonth.";
  SCSTR ERR_LINE_INVALID_ADM = ": invalid AvgDaysPerMonth value.";


  SCSTR PATH_CITY_A = "data/city_a.csv";
  SCSTR PATH_CITY_B = "data/city_b.csv";
  SCSTR PATH_CITY_C = "data/city_c.csv";


}
