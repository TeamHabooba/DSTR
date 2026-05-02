// sТrings.h
#pragma once


#include "./cpp_version.h"


// NOTE: dangerous macro usage. Fix later.
#if CPP_VERSION >= 17
#define CSTR constexpr std::string_view
#define SCSTR static constexpr std::string_view
#else
#define CSTR const char*
#endif


namespace dstr::strings {
  SCSTR HELLO_MSG = "Welcome!";

  SCSTR ERR_MSG_GENERAL = "Error occured: ";
  SCSTR ERR_MSG_NOT_IMPLEMENTED = "This method or class is yet to be implemented.";
}
