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

using dstr::strings::NL;


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
      return Err<int>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_NOT_NUMBER));
    }
    if (option < 0) {
      return Err<int>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_MENU_OPT_BELOW_ZERO));
    }
    return Ok<int>(option);
  }


  // Intro and main menu
  Result<void> cli_start(std::ostream& os, char* argv, int argc) {
    bool running = true;
    while (running) {
      os << strings::MSG_MAIN_MENU_INTRO << '\n';
      os << strings::MSG_MAIN_MENU_OPTIONS << '\n';
      auto option = get_option();
      if (!option) {
        return Result(option);
      }
      switch (option.value()) {
      case 0:
        return Err(ErrorCode::TERMINATED, string(strings::ERR_TERMINATED));
      case 1: {
        auto r = goto_array_menu(os);
        if (r.error().code() == ErrorCode::TERMINATED) {
          running = false;
        }
        break;
      }
      case 2: {
        auto r = goto_array_menu(os);
        if (r.error().code() == ErrorCode::TERMINATED) {
          running = false;
        }
        break;
      }
      case 3: {
        goto_creds(os);
        break;
      }
      }
    }
    return Ok();
  }


  Result<void> goto_array_menu(std::ostream& os) {
    Array<Resident> records;
    bool loaded = false;
    bool running = true;
    while (running) {
      print_header(os, string(strings::MSG_ARR_MENU_HEADER));
      os << strings::MSG_SUB_MENU_OPT_1 << NL;
      os << strings::MSG_SUB_MENU_OPT_2 << NL;
      os << strings::MSG_SUB_MENU_OPT_3 << NL;
      os << strings::MSG_SUB_MENU_OPT_4 << NL;
      os << strings::MSG_SUB_MENU_OPT_5 << NL;
      os << strings::MSG_SUB_MENU_OPT_6 << NL;
      os << strings::MSG_SUB_MENU_OPT_7 << NL;
      os << strings::MSG_SUB_MENU_OPT_0 << NL << NL;
      if (loaded) {
        os << strings::MSG_DATA_LOADED_BEG << records.size() << strings::MSG_DATA_LOADED_END << NL;
      }
      else {
        os << strings::MSG_DATA_NOT_LOADED << NL;
      }
      os << NL << strings::MSG_OPTION;
      auto option = get_option();
      if (!option) {
        os << NL << "[!] " << option.error().message() << NL << NL;
        continue;
      }
      switch (option.value()) {
      case 0:
        running = false;
        break;
      case 1: {
        auto r = array_load_data(records);
        if (r) {
          loaded = true;
        }
        break;
      }
      case 2:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        array_display_table(records);
        break;
      case 3:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        array_carbon_analysis(records);
        break;
      case 4:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        array_age_group_analysis(records);
        break;
      case 5:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        array_sort_menu(records);
        break;
      case 6:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        array_search_menu(records);
        break;
      case 7:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        array_performance_menu(records);
        break;
      default:
        os << NL << strings::MSG_INVALID_OPTION << NL << NL;
        break;
      }
    }
    return Ok();
  }

  Result<void> goto_list_menu(std::ostream& os) {
    List<Resident> records;
    bool loaded = false;
    bool running = true;
    while (running) {
      print_header(os, string(strings::MSG_LIST_MENU_HEADER));
      os << strings::MSG_SUB_MENU_OPT_1 << NL;
      os << strings::MSG_SUB_MENU_OPT_2 << NL;
      os << strings::MSG_SUB_MENU_OPT_3 << NL;
      os << strings::MSG_SUB_MENU_OPT_4 << NL;
      os << strings::MSG_SUB_MENU_OPT_5 << NL;
      os << strings::MSG_SUB_MENU_OPT_6 << NL;
      os << strings::MSG_SUB_MENU_OPT_7 << NL;
      os << strings::MSG_SUB_MENU_OPT_0 << NL << NL;
      if (loaded) {
        os << strings::MSG_DATA_LOADED_BEG << /*records.size() <<*/ strings::MSG_DATA_LOADED_END << NL;
      }
      else {
        os << strings::MSG_DATA_NOT_LOADED << NL;
      }
      os << NL << strings::MSG_OPTION;
      auto option = get_option();
      if (!option) {
        os << NL << "[!] " << option.error().message() << NL << NL;
        continue;
      }
      switch (option.value()) {
      case 0:
        running = false;
        break;
      case 1: {
        auto r = list_load_data(records);
        if (r) {
          loaded = true;
        }
        break;
      }
      case 2:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        list_display_table(records);
        break;
      case 3:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        list_carbon_analysis(records);
        break;
      case 4:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        list_age_group_analysis(records);
        break;
      case 5:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        list_sort_menu(records);
        break;
      case 6:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        list_search_menu(records);
        break;
      case 7:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        list_performance_menu(records);
        break;
      default:
        os << NL << strings::MSG_INVALID_OPTION << NL << NL;
        break;
      }
    }
    return Ok();
  }


  Result<void> goto_creds(std::ostream& os) {
    os << dstr::strings::MSG_DESC << NL;
    os << dstr::strings::MSG_DESC_MEMBERS << NL;
    os << dstr::strings::MSG_DESC_DOCS << NL;
    os << dstr::strings::MSG_DESC_DOCS_FILES << NL;
    os << dstr::strings::MSG_DESC_ROLES_1 << NL;
    os << dstr::strings::MSG_DESC_ROLES_2 << NL;
    os << dstr::strings::MSG_DESC_ROLES_3 << NL;
    os << dstr::strings::MSG_DESC_ROLES_4 << NL;
    return Ok();
  }

  Result<void> array_load_data(Array<Resident>& records) {
    return Result<void>();
  }

  Result<void> array_display_table(const Array<Resident>& records) {
    return Result<void>();
  }

  Result<void> array_carbon_analysis(const Array<Resident>& records) {
    return Result<void>();
  }

  Result<void> array_age_group_analysis(const Array<Resident>& records) {
    return Result<void>();
  }

  Result<void> array_sort_menu(Array<Resident>& records) {
    return Result<void>();
  }

  Result<void> array_search_menu(const Array<Resident>& records) {
    return Result<void>();
  }

  Result<void> array_performance_menu(Array<Resident>& records) {
    return Result<void>();
  }

  Result<void> list_load_data(List<Resident>& records)
  {
    return Result<void>();
  }
  Result<void> list_display_table(const List<Resident>& records)
  {
    return Result<void>();
  }
  Result<void> list_carbon_analysis(const List<Resident>& records)
  {
    return Result<void>();
  }
  Result<void> list_age_group_analysis(const List<Resident>& records)
  {
    return Result<void>();
  }
  Result<void> list_sort_menu(List<Resident>& records)
  {
    return Result<void>();
  }
  Result<void> list_search_menu(const List<Resident>& records)
  {
    return Result<void>();
  }
  Result<void> list_performance_menu(List<Resident>& records)
  {
    return Result<void>();
  }


  
} // namespace dstr
