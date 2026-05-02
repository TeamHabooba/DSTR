#pragma once


#include "../common/common.h"


namespace dstr {


  Result<string> trim(const string& s);
  Result<int> get_option();
  Result<void> cli_start(char* argv, int argc);
  Result<void> goto_creds();


}
