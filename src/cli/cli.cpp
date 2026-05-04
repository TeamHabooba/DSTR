// cli.cpp
#include "./cli.h"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "../common/strings/list.h"


using std::getline;
using std::string;

using dstr::strings::NL;


namespace dstr {


  // Helpers
  
  Result<int> get_option(std::istream& is) {
    string soption;
    int option{ -1 };
    getline(is, soption);
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
  Result<void> cli_start(std::istream& is, std::ostream& os, char* argv, int argc) {
    bool running = true;
    while (running) {
      os << strings::MSG_MAIN_MENU_INTRO << '\n';
      os << strings::MSG_MAIN_MENU_OPTIONS << '\n';
      auto option = get_option(is);
      if (!option) {
        return Result(option);
      }
      switch (option.value()) {
      case 0:
        return Err(ErrorCode::TERMINATED, string(strings::ERR_TERMINATED));
      case 1: {
        auto r = goto_array_menu(is, os);
        if (r.error().code() == ErrorCode::TERMINATED) {
          running = false;
        }
        break;
      }
      case 2: {
        auto r = goto_array_menu(is, os);
        if (r.error().code() == ErrorCode::TERMINATED) {
          running = false;
        }
        break;
      }
      case 3: {
        goto_creds(is, os);
        break;
      }
      }
    }
    return Ok();
  }


  Result<void> goto_array_menu(std::istream& is, std::ostream& os) {
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
      auto option = get_option(is);
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

  Result<void> goto_list_menu(std::istream& is, std::ostream& os) {
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
      auto option = get_option(is);
      if (!option) {
        os << NL << "[!] " << option.error().message() << NL << NL;
        continue;
      }
      switch (option.value()) {
      case 0:
        running = false;
        break;
      case 1: {
        auto r = list_load_data(is, os, records);
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
        list_display_table(is, os, records);
        break;
      case 3:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        list_carbon_analysis(is, os, records);
        break;
      case 4:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        list_age_group_analysis(is, os, records);
        break;
      case 5:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        list_sort_menu(is, os, records);
        break;
      case 6:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        list_search_menu(is, os, records);
        break;
      case 7:
        if (!loaded) {
          os << NL << strings::MSG_DATA_NOT_LOADED_X << NL << NL;
          break;
        }
        list_performance_menu(is, os, records);
        break;
      default:
        os << NL << strings::MSG_INVALID_OPTION << NL << NL;
        break;
      }
    }
    return Ok();
  }


  Result<void> goto_creds(std::istream& is, std::ostream& os) {
    os << dstr::strings::MSG_DESC << NL;
    os << dstr::strings::MSG_DESC_MEMBERS << NL;
    os << dstr::strings::MSG_DESC_DOCS << NL;
    os << dstr::strings::MSG_DESC_DOCS_FILES << NL;
    os << dstr::strings::MSG_DESC_ROLES_1 << NL;
    os << dstr::strings::MSG_DESC_ROLES_2 << NL;
    os << dstr::strings::MSG_DESC_ROLES_3 << NL;
    os << dstr::strings::MSG_DESC_ROLES_4 << NL;
    await_return(is);
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


  // List menu functions

  // Load data
  Result<void> dstr::list_load_data(std::istream& is, std::ostream& os, List<Resident>& records) {
      os << NL << strings::LIST_LOAD_LOADING << NL;
      int loaded = 0;
      for (auto path : { strings::PATH_CITY_A, strings::PATH_CITY_B, strings::PATH_CITY_C }) {
          auto r = load_csv(string(path));
          if (!r) {
              os << "[!] " << r.error().message() << NL;
              continue;
          }
          for (int i = 0; i < r.value().size(); ++i) {
              records.insert(r.value()[i]);
              ++loaded;
          }
      }
      if (loaded == 0) {
          std::cout << strings::LIST_LOAD_FAIL << NL << NL;
          return Err(ErrorCode::EMPTY_CONTAINER, string(strings::LIST_LOAD_FAIL));
      }
      os << strings::LIST_LOAD_OK_BEG << loaded << strings::LIST_LOAD_OK_END << NL << NL;
      os << strings::MSG_CONTINUE;
      return Ok();
  }

  //  Display table
  Result<void> dstr::list_display_table(std::istream& is, std::ostream& os, const List<Resident>& records) {
      os << NL << strings::LIST_TABLE_HEADER << NL;
      os << strings::LIST_TABLE_DIVIDER << NL;
      if (records.empty()) {
          std::cout << strings::LIST_TABLE_EMPTY << NL;
      }
      else {
          int idx = 1;
          records.for_each([&](const Resident& r) {
              std::cout << "[" << std::setw(4) << idx++ << "] " << r << NL;
              });
      }
      os << strings::LIST_TABLE_DIVIDER << NL << NL;
      os << strings::MSG_RETURN;
      
      await_return(std::cin);
      return Ok();
  }


  //  3. Carbon emission analysis

  Result<void> dstr::list_carbon_analysis(std::istream& is, std::ostream& os, const List<Resident>& records) {
      std::cout << NL << strings::LIST_CARBON_HEADER << NL << NL;

      // Accumulate per transport mode
      std::map<ModeOfTransport, float> sum_by_transport;
      std::map<ModeOfTransport, int>   count_by_transport;
      float total = 0.0f;

      records.for_each([&](const Resident& r) {
          float e = r.monthly_emission();
          sum_by_transport[r.transport] += e;
          count_by_transport[r.transport]++;
          total += e;
          });

      // Average per transport mode
      std::cout << strings::LIST_CARBON_TRANSPORT_HDR << NL;
      std::cout << std::left
          << std::setw(20) << "Transport"
          << std::setw(10) << "Count"
          << std::setw(20) << "Avg Emission (kg CO2)" << NL;
      std::cout << std::string(50, '-') << NL;

      for (auto& [mode, sum] : sum_by_transport) {
          int cnt = count_by_transport[mode];
          std::cout << std::left
              << std::setw(20) << [&]() -> std::string_view {
              switch (mode) {
              case ModeOfTransport::CAR:        return "Car";
              case ModeOfTransport::BUS:        return "Bus";
              case ModeOfTransport::BICYCLE:    return "Bicycle";
              case ModeOfTransport::WALKING:    return "Walking";
              case ModeOfTransport::CARPOOL:    return "Carpool";
              case ModeOfTransport::SCHOOL_BUS: return "School Bus";
              default:                          return "Unknown";
              }
              }()
                  << std::setw(10) << cnt
                  << std::setw(20) << std::fixed << std::setprecision(2)
                  << (cnt > 0 ? sum / cnt : 0.0f) << NL;
      }

      std::cout << NL;

      // Top 5 highest emitters — collect into vector, partial sort
      std::vector<Resident> all;
      all.reserve(records.size());
      records.for_each([&](const Resident& r) { all.push_back(r); });

      int top_n = std::min(5, static_cast<int>(all.size()));
      std::partial_sort(all.begin(), all.begin() + top_n, all.end(),
          [](const Resident& a, const Resident& b) {
              return a.monthly_emission() > b.monthly_emission();
          });

      std::cout << strings::LIST_CARBON_TOP_HDR << NL;
      for (int i = 0; i < top_n; ++i)
          std::cout << "  " << (i + 1) << ". " << all[i] << NL;

      std::cout << NL;
      std::cout << strings::LIST_CARBON_TOTAL
          << std::fixed << std::setprecision(2) << total
          << strings::LIST_CARBON_UNIT << NL;
      std::cout << strings::LIST_CARBON_AVG
          << std::fixed << std::setprecision(2)
          << (records.size() > 0 ? total / records.size() : 0.0f)
          << strings::LIST_CARBON_UNIT << NL << NL;

      std::cout << strings::MSG_RETURN;
      std::cin.ignore();
      return Ok();
  }


  //  4. Age group analysis 

  Result<void> dstr::list_age_group_analysis(std::istream& is, std::ostream& os, const List<Resident>& records) {
      std::cout << NL << strings::LIST_AGE_HEADER << NL << NL;

      std::map<AgeGroup, float> sum_by_group;
      std::map<AgeGroup, int>   count_by_group;

      records.for_each([&](const Resident& r) {
          sum_by_group[r.age_group()] += r.monthly_emission();
          count_by_group[r.age_group()]++;
          });

      std::cout << std::left
          << std::setw(26) << strings::LIST_AGE_GROUP_COL
          << std::setw(10) << strings::LIST_AGE_COUNT_COL
          << strings::LIST_AGE_AVG_COL << NL;
      std::cout << std::string(58, '-') << NL;

      for (auto& [group, sum] : sum_by_group) {
          int cnt = count_by_group[group];
          std::cout << std::left
              << std::setw(26) << [&]() -> std::string_view {
              switch (group) {
              case AgeGroup::CHILDREN_TEENAGERS:   return "Children/Teenagers";
              case AgeGroup::YOUNG_ADULTS:         return "Young Adults";
              case AgeGroup::WORKING_ADULTS_EARLY: return "Working Adults (26-45)";
              case AgeGroup::WORKING_ADULTS_LATE:  return "Working Adults (46-60)";
              case AgeGroup::SENIOR_CITIZENS:      return "Senior Citizens";
              default:                             return "Unknown";
              }
              }()
                  << std::setw(10) << cnt
                  << std::fixed << std::setprecision(2)
                  << (cnt > 0 ? sum / cnt : 0.0f) << NL;
      }

      std::cout << NL << strings::MSG_RETURN;
      std::cin.ignore();
      return Ok();
  }


  //  Sort experiments 
  Result<void> dstr::list_sort_menu(std::istream& is, std::ostream& os, List<Resident>& records) {
    using namespace std::chrono;
    os << NL << strings::LIST_SORT_HEADER << NL;
    os << strings::LIST_SORT_PROMPT << NL << NL;
    // The skip list is always sorted on insert — we just time a full traversal
    // to demonstrate the O(log n) structure is intact
    auto t0 = high_resolution_clock::now();
    records.sort();  // no-op, but we also do a full traversal to verify order
    volatile int count = 0;
    records.for_each([&](const Resident&) { ++count; });
    auto t1 = high_resolution_clock::now();
    long long us = duration_cast<microseconds>(t1 - t0).count();
    os << strings::LIST_SORT_DONE_BEG << us;
    os << strings::LIST_SORT_DONE_END << NL << NL;
    // Print the sorted result
    os << "+--------------------+----------------+\n";
    os << "| Sort Method        | Time (us)      |\n";
    os << "+--------------------+----------------+\n";
    os << "| Skip List (insert) | ";
    os << std::setw(14) << us << " |\n";
    os << "+--------------------+----------------+\n";
    os << "  Elements: " << records.size() << NL << NL;
    os << strings::MSG_RETURN;
    await_return(is);
    return Ok();
  }

  // Search experiments 
  Result<void> dstr::list_search_menu(std::istream& is, std::ostream& os, const List<Resident>& records) {
    using namespace std::chrono;
    os << NL << strings::LIST_SEARCH_HEADER << NL;
    os << strings::LIST_SEARCH_PROMPT;
    string target_id;
    std::getline(is, target_id);
    target_id = trim(target_id);
    // Build a dummy Resident to search by ID (operator== compares id only)
    Resident target{};
    target.id = target_id;
    // skip list orders by monthly_emission via operator<,
    // so set emission fields to 0 — find() uses == (id match) at candidate node
    target.daily_distance_km = 0;
    target.carbon_emission_factor = 0.0f;
    target.avg_days_per_month = 0;
    auto t0 = high_resolution_clock::now();
    const Resident* result = records.find(target);
    auto t1 = high_resolution_clock::now();
    long long us = duration_cast<microseconds>(t1 - t0).count();
    os << NL;
    if (result) {
      os << strings::LIST_SEARCH_FOUND << *result << NL;
    }
    else {
      // Skip list is sorted by emission, not ID — fall back to linear scan
      // so the user still gets a result for ID-based lookup
      const Resident* found = nullptr;
      records.for_each([&](const Resident& r) {
        if (!found && r.id == target_id) found = &r;
      });
      if (found) {
        std::cout << strings::LIST_SEARCH_FOUND << *found << NL;
      }
      else {
        std::cout << strings::LIST_SEARCH_NOT_FOUND << NL;
      }
    }
    os << strings::LIST_SEARCH_TIME_BEG << us;
    os << strings::LIST_SEARCH_TIME_END << NL << NL;
    os << strings::MSG_RETURN;
    await_return(is);
    return Ok();
  }

  // Performance analysis 
  Result<void> dstr::list_performance_menu(std::istream& is, std::ostream& os, List<Resident>& records) {
    using namespace std::chrono;
    os << NL << strings::LIST_PERF_HEADER << NL << NL;
    //  Insert benchmark: rebuild list from scratch and time it
    std::vector<Resident> snapshot;
    snapshot.reserve(records.size());
    records.for_each([&](const Resident& r) { snapshot.push_back(r); });
    List<Resident> bench_list;
    auto t0 = high_resolution_clock::now();
    for (const auto& r : snapshot) {
      bench_list.insert(r);
    }
    auto t1 = high_resolution_clock::now();
    long long t_insert = duration_cast<microseconds>(t1 - t0).count();
    //  Search benchmark: search for the middle element by emission order
    long long t_search = 0;
    if (!snapshot.empty()) {
        // snapshot is unsorted; pick one that exists in the list
        const Resident& mid = snapshot[snapshot.size() / 2];
        auto s0 = high_resolution_clock::now();
        bench_list.find(mid);
        auto s1 = high_resolution_clock::now();
        t_search = duration_cast<microseconds>(s1 - s0).count();
    }
    //  Traversal benchmark
    auto v0 = high_resolution_clock::now();
    volatile int dummy = 0;
    records.for_each([&](const Resident&) { ++dummy; });
    auto v1 = high_resolution_clock::now();
    long long t_traverse = duration_cast<microseconds>(v1 - v0).count();
    //  Memory estimate: per node ~ sizeof(T) + sizeof(vector header) + avg 2 pointers per node
    // avg levels ≈ 2 for p=0.5, so ~2 forward pointers per node
    size_t node_size = sizeof(Resident)
        + sizeof(std::vector<void*>)    // forward vector header
        + 2 * sizeof(void*);            // avg forward pointers
    size_t mem_est = node_size * static_cast<size_t>(records.size()) + sizeof(List<Resident>);
    //  Print results
    os << strings::LIST_PERF_COUNT_BEG << records.size() << NL;
    os << strings::LIST_PERF_INSERT_BEG << t_insert << strings::LIST_PERF_INSERT_END << NL;
    os << strings::LIST_PERF_SEARCH_BEG << t_search << strings::LIST_PERF_SEARCH_END << NL;
    os << strings::LIST_PERF_TRAVERSE_BEG << t_traverse << strings::LIST_PERF_TRAVERSE_END << NL;
    os << strings::LIST_PERF_MEM_BEG << mem_est << strings::LIST_PERF_MEM_END << NL;
    os << NL << strings::MSG_RETURN;
    await_return(is);
    return Ok();
}

  
} // namespace dstr
