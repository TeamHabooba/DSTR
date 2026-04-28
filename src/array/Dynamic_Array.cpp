#include "DynamicArray.h"

#include <cmath>
#include <stdexcept>

namespace dstr {

constexpr i32 DEFAULT_CAPACITY = 8;

template <typename T>
DynamicArray<T>::DynamicArray()
    : data_(std::make_unique<T[]>(DEFAULT_CAPACITY)),
      size_(0),
      capacity_(DEFAULT_CAPACITY) {}

template <typename T>
DynamicArray<T>::DynamicArray(i32 initial_capacity)
    : data_(std::make_unique<T[]>(initial_capacity)),
      size_(0),
      capacity_(initial_capacity) {}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
    : data_(std::make_unique<T[]>(other.capacity_)),
      size_(other.size_),
      capacity_(other.capacity_) {
  for (i32 i = 0; i < size_; i++) {
    data_[i] = other.data_[i];
  }
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept
    : data_(std::move(other.data_)),
      size_(std::exchange(other.size_, 0)),
      capacity_(std::exchange(other.capacity_, 0)) {}

template <typename T>
bool DynamicArray<T>::operator==(const DynamicArray& other) const {
  if (size_ != other.size_) {
    return false;
  }
  for (i32 i = 0; i < size_; i++) {
    if (data_[i] != other.data_[i]) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool DynamicArray<T>::operator!=(const DynamicArray& other) const {
  return !(*this == other);
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
  if (this != &other) {
    data_     = std::make_unique<T[]>(other.capacity_);
    size_     = other.size_;
    capacity_ = other.capacity_;
    for (i32 i = 0; i < size_; i++) {
      data_[i] = other.data_[i];
    }
  }
  return *this;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& other) noexcept {
  if (this != &other) {
    data_     = std::move(other.data_);
    size_     = std::exchange(other.size_, 0);
    capacity_ = std::exchange(other.capacity_, 0);
  }
  return *this;
}

template <typename T>
T& DynamicArray<T>::operator[](i32 index) {
  if (index < 0 || index >= size_) {
    throw std::out_of_range("DynamicArray: index out of range");
  }
  return data_[index];
}

template <typename T>
const T& DynamicArray<T>::operator[](i32 index) const {
  if (index < 0 || index >= size_) {
    throw std::out_of_range("DynamicArray: index out of range");
  }
  return data_[index];
}

template <typename T>
T& DynamicArray<T>::get(i32 index) {
  return (*this)[index];
}

template <typename T>
const T& DynamicArray<T>::get(i32 index) const {
  return (*this)[index];
}

template <typename T>
i32 DynamicArray<T>::size() const {
  return size_;
}

template <typename T>
i32 DynamicArray<T>::capacity() const {
  return capacity_;
}

template <typename T>
bool DynamicArray<T>::empty() const {
  return size_ == 0;
}

template <typename T>
void DynamicArray<T>::push_back(const T& value) {
  if (size_ == capacity_) {
    grow();
  }
  data_[size_] = value;
  size_++;
}

template <typename T>
bool DynamicArray<T>::insert(i32 index, const T& value) {
  if (index < 0 || index > size_) {
    return false;
  }
  if (size_ == capacity_) {
    grow();
  }
  for (i32 i = size_; i > index; i--) {
    data_[i] = data_[i - 1];
  }
  data_[index] = value;
  size_++;
  return true;
}

template <typename T>
bool DynamicArray<T>::update(i32 index, const T& value) {
  if (index < 0 || index >= size_) {
    return false;
  }
  data_[index] = value;
  return true;
}

template <typename T>
bool DynamicArray<T>::pop_back() {
  if (size_ == 0) {
    return false;
  }
  size_--;
  return true;
}

template <typename T>
bool DynamicArray<T>::remove(i32 index) {
  if (index < 0 || index >= size_) {
    return false;
  }
  for (i32 i = index; i < size_ - 1; i++) {
    data_[i] = data_[i + 1];
  }
  size_--;
  return true;
}

template <typename T>
void DynamicArray<T>::clear() {
  size_ = 0;
}

template <typename T>
template <typename Comparator>
void DynamicArray<T>::bubble_sort(Comparator comp) {
  for (i32 i = 0; i < size_ - 1; i++) {
    bool swapped = false;

    for (i32 j = 0; j < size_ - i - 1; j++) {
      if (comp(data_[j + 1], data_[j])) {
        swap_elements(j, j + 1);
        swapped = true;
      }
    }

    if (!swapped) {
      break;
    }
  }
}

template <typename T>
template <typename Comparator>
void DynamicArray<T>::insertion_sort(Comparator comp) {
  for (i32 i = 1; i < size_; i++) {
    T   key = data_[i];
    i32 j   = i - 1;

    while (j >= 0 && comp(key, data_[j])) {
      data_[j + 1] = data_[j];
      j--;
    }

    data_[j + 1] = key;
  }
}

template <typename T>
template <typename Comparator>
void DynamicArray<T>::quick_sort(Comparator comp) {
  if (size_ <= 1) {
    return;
  }
  quick_sort_helper(comp, 0, size_ - 1);
}

template <typename T>
template <typename KeyComp>
i32 DynamicArray<T>::linear_search(KeyComp key_comp) const {
  for (i32 i = 0; i < size_; i++) {
    if (key_comp(data_[i])) {
      return i;
    }
  }
  return -1;
}

template <typename T>
template <typename Comparator, typename KeyComp>
i32 DynamicArray<T>::binary_search(Comparator comp, KeyComp key_comp, const T& target) const {
  i32 low  = 0;
  i32 high = size_ - 1;

  while (low <= high) {
    i32 mid = low + (high - low) / 2;

    if (key_comp(data_[mid])) {
      return mid;
    } else if (comp(data_[mid], target)) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}

template <typename T>
template <typename Comparator, typename KeyComp>
i32 DynamicArray<T>::jump_search(Comparator comp, KeyComp key_comp) const {
  if (size_ == 0) {
    return -1;
  }

  i32 step = static_cast<i32>(std::sqrt(static_cast<double>(size_)));
  i32 prev = 0;

  while (prev < size_) {
    i32 block_end = prev + step;
    if (block_end >= size_) {
      block_end = size_ - 1;
    }

    if (key_comp(data_[prev])) {
      return prev;
    }

    if (comp(data_[block_end], data_[size_ - 1]) && !key_comp(data_[block_end])) {
      prev += step;
    } else {
      break;
    }
  }

  i32 scan_end = prev + step;
  if (scan_end > size_) {
    scan_end = size_;
  }

  for (i32 i = prev; i < scan_end; i++) {
    if (key_comp(data_[i])) {
      return i;
    }
  }

  return -1;
}

template <typename T>
i32 DynamicArray<T>::memory_usage() const {
  return static_cast<i32>(
    (capacity_ * sizeof(T))
    + sizeof(data_)
    + sizeof(size_)
    + sizeof(capacity_)
  );
}

template <typename T>
template <typename Comparator>
void DynamicArray<T>::compare_sorts(Comparator comp) const {
  DynamicArray<T> copy_bubble(*this);
  DynamicArray<T> copy_insert(*this);
  DynamicArray<T> copy_quick(*this);

  auto start_bubble = std::chrono::high_resolution_clock::now();
  copy_bubble.bubble_sort(comp);
  auto end_bubble = std::chrono::high_resolution_clock::now();
  long long t_bubble = std::chrono::duration_cast<std::chrono::microseconds>(end_bubble - start_bubble).count();

  auto start_insert = std::chrono::high_resolution_clock::now();
  copy_insert.insertion_sort(comp);
  auto end_insert = std::chrono::high_resolution_clock::now();
  long long t_insert = std::chrono::duration_cast<std::chrono::microseconds>(end_insert - start_insert).count();

  auto start_quick = std::chrono::high_resolution_clock::now();
  copy_quick.quick_sort(comp);
  auto end_quick = std::chrono::high_resolution_clock::now();
  long long t_quick = std::chrono::duration_cast<std::chrono::microseconds>(end_quick - start_quick).count();

  i32 mem = memory_usage();

  std::cout << "\n";
  std::cout << "+--------------------+----------------+----------------+\n";
  std::cout << "| Sort Algorithm     | Time (us)      | Memory (bytes) |\n";
  std::cout << "+--------------------+----------------+----------------+\n";
  std::cout << "| Bubble Sort        | " << std::setw(14) << t_bubble << " | " << std::setw(14) << mem << " |\n";
  std::cout << "| Insertion Sort     | " << std::setw(14) << t_insert << " | " << std::setw(14) << mem << " |\n";
  std::cout << "| Quick Sort         | " << std::setw(14) << t_quick  << " | " << std::setw(14) << mem << " |\n";
  std::cout << "+--------------------+----------------+----------------+\n";
  std::cout << "  Elements: " << size_ << " | Capacity: " << capacity_ << "\n";
}

template <typename T>
template <typename Comparator, typename KeyComp>
void DynamicArray<T>::compare_searches(Comparator comp, KeyComp key_comp, const T& target) const {
  i32 r_linear = -1;
  i32 r_binary = -1;
  i32 r_jump   = -1;

  auto start_linear = std::chrono::high_resolution_clock::now();
  r_linear = linear_search(key_comp);
  auto end_linear = std::chrono::high_resolution_clock::now();
  long long t_linear = std::chrono::duration_cast<std::chrono::microseconds>(end_linear - start_linear).count();

  auto start_binary = std::chrono::high_resolution_clock::now();
  r_binary = binary_search(comp, key_comp, target);
  auto end_binary = std::chrono::high_resolution_clock::now();
  long long t_binary = std::chrono::duration_cast<std::chrono::microseconds>(end_binary - start_binary).count();

  auto start_jump = std::chrono::high_resolution_clock::now();
  r_jump = jump_search(comp, key_comp);
  auto end_jump = std::chrono::high_resolution_clock::now();
  long long t_jump = std::chrono::duration_cast<std::chrono::microseconds>(end_jump - start_jump).count();

  std::cout << "\n";
  std::cout << "+--------------------+------------+--------+\n";
  std::cout << "| Search Algorithm   | Time (us)  | Index  |\n";
  std::cout << "+--------------------+------------+--------+\n";
  std::cout << "| Linear Search      | " << std::setw(10) << t_linear << " | " << std::setw(6) << r_linear << " |\n";
  std::cout << "| Binary Search      | " << std::setw(10) << t_binary << " | " << std::setw(6) << r_binary << " |\n";
  std::cout << "| Jump Search        | " << std::setw(10) << t_jump   << " | " << std::setw(6) << r_jump   << " |\n";
  std::cout << "+--------------------+------------+--------+\n";
  std::cout << "  Elements: " << size_ << "\n";
}

template <typename T>
void DynamicArray<T>::print() const {
  for (i32 i = 0; i < size_; i++) {
    std::cout << "[" << i << "] " << data_[i] << "\n";
  }
}

template <typename T>
void DynamicArray<T>::grow() {
  capacity_ = capacity_ * 2;
  up<T[]> new_data = std::make_unique<T[]>(capacity_);
  for (i32 i = 0; i < size_; i++) {
    new_data[i] = data_[i];
  }
  data_ = std::move(new_data);
}

template <typename T>
void DynamicArray<T>::swap_elements(i32 i, i32 j) {
  T temp   = data_[i];
  data_[i] = data_[j];
  data_[j] = temp;
}

template <typename T>
template <typename Comparator>
i32 DynamicArray<T>::partition(Comparator comp, i32 low, i32 high) {
  T   pivot = data_[high];
  i32 i     = low - 1;

  for (i32 j = low; j < high; j++) {
    if (comp(data_[j], pivot)) {
      i++;
      swap_elements(i, j);
    }
  }

  swap_elements(i + 1, high);
  return i + 1;
}

template <typename T>
template <typename Comparator>
void DynamicArray<T>::quick_sort_helper(Comparator comp, i32 low, i32 high) {
  if (low < high) {
    i32 pivot_pos = partition(comp, low, high);
    quick_sort_helper(comp, low, pivot_pos - 1);
    quick_sort_helper(comp, pivot_pos + 1, high);
  }
}

}
