// cli.cpp
#include "./cli.h"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


using std::cout;
using std::cin;
using std::getline;
using std::string;


namespace dstr {


  // Helpers
  
  Result<int> get_option() {
    string soption;
    int option{ -1 };
    getline(cin, soption);
    auto trim_result = trim(soption);
    try {
      option = std::stoi(trim(soption));
    }
    catch (const std::invalid_argument& e) {
      return Err<int>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_MSG_NOT_NUMBER));
    }
    if (option < 0) {
      return Err<int>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_MSG_MENU_OPT_BELOW_ZERO));
    }
    return Ok<int>(option);
  }


  // Intro and main menu
  Result<void> cli_start(char* argv, int argc) {
    cout << strings::MSG_MAIN_MENU_INTRO << '\n';
    cout << strings::MSG_MAIN_MENU_OPTIONS << '\n';
    auto option = get_option();
    if (!option) {
      return Result(option);
    }
    switch (option.value()) {
    case 0:
      return Err(ErrorCode::TERMINATED, string(strings::ERR_MSG_TERMINATED));
    }
  }


  Result<void> goto_creds() {
    cout << dstr::strings::MSG_DESC << "\n";
    cout << dstr::strings::MSG_DESC_MEMBERS << "\n";
    cout << dstr::strings::MSG_DESC_DOCS << "\n";
    cout << dstr::strings::MSG_DESC_DOCS_FILES << "\n";
    return Err();
  }
} // namespace dstr
