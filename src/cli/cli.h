#pragma once


#include "../common/common.h"
#include "../array/array.h"
#include "../list/list.h"
#include "../files/files.h"


namespace dstr {


  // Utility

  Result<int> get_option(std::istream& is);


  // Entry point

  Result<void> cli_start(std::istream& is, std::ostream& os, char* argv, int argc);


  // Top-level menus

  Result<void> goto_array_menu(std::istream& is, std::ostream& os, Array<Resident>& records, bool& loaded);
  Result<void> goto_list_menu(std::istream& is, std::ostream& os, List<Resident>& records, bool& loaded);
  Result<void> goto_creds(std::istream& is, std::ostream& os);


  // Array sub-menu actions

  Result<void> array_load_data(std::istream& is, std::ostream& os, Array<Resident>& records);
  Result<void> array_display_table(std::istream& is, std::ostream& os, const Array<Resident>& records);
  Result<void> array_carbon_analysis(std::istream& is, std::ostream& os, const Array<Resident>& records);
  Result<void> array_age_group_analysis(std::istream& is, std::ostream& os, const Array<Resident>& records);
  Result<void> array_sort_menu(std::istream& is, std::ostream& os, Array<Resident>& records);
  Result<void> array_search_menu(std::istream& is, std::ostream& os, const Array<Resident>& records);
  Result<void> array_performance_menu(std::istream& is, std::ostream& os, Array<Resident>& records);


  // List sub-menu actions

  Result<void> list_load_data(std::istream& is, std::ostream& os, List<Resident>& records);
  Result<void> list_display_table(std::istream& is, std::ostream& os, const List<Resident>& records);
  Result<void> list_carbon_analysis(std::istream& is, std::ostream& os, const List<Resident>& records);
  Result<void> list_age_group_analysis(std::istream& is, std::ostream& os, const List<Resident>& records);
  Result<void> list_sort_menu(std::istream& is, std::ostream& os, List<Resident>& records);
  Result<void> list_search_menu(std::istream& is, std::ostream& os, const List<Resident>& records);
  Result<void> list_performance_menu(std::istream& is, std::ostream& os, List<Resident>& records);


} // namespace dstr
