#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

#include "./cli.h"


using std::cout;
using std::cin, std::getline;
using std::string;


namespace dstr {

  Result<string> trim(const string& s) {
    auto start = std::find_if_not(s.begin(), s.end(), ::isspace);
    auto end = std::find_if_not(s.rbegin(), s.rend(), ::isspace).base();
    return Result<string>((start < end) ? string(start, end) : "");
  }

  Result<int> get_option() {
    string soption;
    int option{ -1 };
    getline(cin, soption);
    auto trim_result = trim(soption);
    if (!trim_result) {
      return Err<int>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_MSG_TRIM_ERROR));
    }
    try {
      option = std::stoi(trim(soption).value());
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
}
