#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>

#include "common/aliases.h"

namespace dstr {

template <typename T>
class Array {
 private:
  up<T[]> data_;
  i32 size_;

 public:
  explicit Array(i32 size);
  Array(const Array& other);
  Array(Array&& other) noexcept;

  bool operator==(const Array& other) const;
  bool operator!=(const Array& other) const;

  Array& operator=(const Array& other);
  Array& operator=(Array&& other) noexcept;

  T& operator[](i32 index);
  const T& operator[](i32 index) const;

  T& get(i32 index);
  const T& get(i32 index) const;

  i32 size() const;

  void fill(const T& value);
  bool update(i32 index, const T& value);
  bool reset(i32 index);

  template <typename Comparator>
  void bubble_sort(Comparator comp);

  template <typename Comparator>
  void insertion_sort(Comparator comp);

  template <typename Comparator>
  void quick_sort(Comparator comp);

  template <typename KeyComp>
  i32 linear_search(KeyComp key_comp) const;

  template <typename Comparator, typename KeyComp>
  i32 binary_search(Comparator comp, KeyComp key_comp, const T& target) const;

  template <typename Comparator, typename KeyComp>
  i32 jump_search(Comparator comp, KeyComp key_comp) const;

  i32 memory_usage() const;

  template <typename Func>
  static long long measure_time(Func func);

  template <typename Comparator>
  void compare_sorts(Comparator comp) const;

  template <typename Comparator, typename KeyComp>
  void compare_searches(Comparator comp, KeyComp key_comp, const T& target) const;

  void print() const;

  friend std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
    for (i32 i = 0; i < arr.size_; i++) {
      os << "[" << i << "] " << arr.data_[i] << "\n";
    }
    return os;
  }

 private:
  void swap_elements(i32 i, i32 j);

  template <typename Comparator>
  i32 partition(Comparator comp, i32 low, i32 high);

  template <typename Comparator>
  void quick_sort_helper(Comparator comp, i32 low, i32 high);

};

} 
