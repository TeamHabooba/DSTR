// sТrings.h
#pragma once


#include "./cpp_version.h"


#if CPP_VERSION >= 17
using string_const = std::string_view;
#else
using string_const = const char*;
#endif


