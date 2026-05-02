// sТrings.h
#pragma once


#include "./cpp_version.h"


#if CPP_VERSION >= 17
using string_const = std::string_view;
#else
using string_const = const char*;
#endif


namespace dstr::strings {
  string_const HELLO_MSG = "Welcome!";

  string_const ERR_MSG_GENERAL = "Error occured: ";
  string_const ERR_MSG_NOT_IMPLEMENTED = "This method or class is yet to be implemented.";
}
