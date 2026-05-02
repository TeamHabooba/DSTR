#pragma once


#include "../common/common.h"
#include "../files/files.h"


namespace dstr {


  // =====Utility
  Result<int> get_option();

  // =====Entry point
  Result<void> cli_start(char* argv, int argc);

  // =====Top-level menus
  Result<void> goto_array_menu();
  Result<void> goto_list_menu();
  Result<void> goto_creds();

  // =====Array sub-menu actions
  Result<void> array_load_data(Array<Resident>& records);
  Result<void> array_display_table(const Array<Resident>& records);
  Result<void> array_carbon_analysis(const Array<Resident>& records);
  Result<void> array_age_group_analysis(const Array<Resident>& records);
  Result<void> array_sort_menu(Array<Resident>& records);
  Result<void> array_search_menu(const Array<Resident>& records);
  Result<void> array_performance_menu(Array<Resident>& records);

  // =====List sub-menu actions
  Result<void> list_load_data(List<Resident>& records);
  Result<void> list_display_table(const List<Resident>& records);
  Result<void> list_carbon_analysis(const List<Resident>& records);
  Result<void> list_age_group_analysis(const List<Resident>& records);
  Result<void> list_sort_menu(List<Resident>& records);
  Result<void> list_search_menu(const List<Resident>& records);
  Result<void> list_performance_menu(List<Resident>& records);

  // =====Display helpers (shared)
  void print_resident_row(std::ostream&, const Resident& r, i32 index);


} // namespace dstr
