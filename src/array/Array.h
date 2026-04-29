#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>

#include "common/aliases.h"

namespace dstr {

template <typename T>
class DynamicArray {

 private:
  up<T[]> data_;
  i32     size_;
  i32     capacity_;

 public:

  DynamicArray();

  explicit DynamicArray(i32 initial_capacity);

  DynamicArray(const DynamicArray& other);

  DynamicArray(DynamicArray&& other) noexcept;

  bool operator==(const DynamicArray& other) const;

  bool operator!=(const DynamicArray& other) const;

  DynamicArray& operator=(const DynamicArray& other);

  DynamicArray& operator=(DynamicArray&& other) noexcept;

  T&       operator[](i32 index);
  const T& operator[](i32 index) const;

  T&       get(i32 index);
  const T& get(i32 index) const;

  i32 size() const;

  i32 capacity() const;

  bool empty() const;

  void push_back(const T& value);

  bool insert(i32 index, const T& value);

  bool update(i32 index, const T& value);

  bool pop_back();

  bool remove(i32 index);

  void clear();

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

  template <typename Comparator>
  void compare_sorts(Comparator comp) const;

  template <typename Comparator, typename KeyComp>
  void compare_searches(Comparator comp, KeyComp key_comp, const T& target) const;

  void print() const;

  friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& arr) {
    for (i32 i = 0; i < arr.size_; i++) {
      os << "[" << i << "] " << arr.data_[i] << "\n";
    }
    return os;
  }

 private:

  void grow();

  void swap_elements(i32 i, i32 j);

  template <typename Comparator>
  i32 partition(Comparator comp, i32 low, i32 high);

  template <typename Comparator>
  void quick_sort_helper(Comparator comp, i32 low, i32 high);

};

}
