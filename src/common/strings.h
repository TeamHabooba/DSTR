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


  SCSTR ERR_MSG_GENERAL = "Error occured: ";
  SCSTR ERR_MSG_NOT_IMPLEMENTED = "This method or class is yet to be implemented.";
  SCSTR ERR_MSG_INVALID_ARGUMENT = "Invalid method/function argument.";
  SCSTR ERR_MSG_NOT_NUMBER = "Not a number.";
  SCSTR ERR_MSG_TRIM_ERROR = "trim() finished with an error.";
  SCSTR ERR_MSG_TERMINATED = "Program was terminated by user.";
  SCSTR ERR_MSG_MENU_OPT_BELOW_ZERO = "Menu option number was less than zero.";


}
