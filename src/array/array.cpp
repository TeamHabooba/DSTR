#include <cmath>
#include <stdexcept>

namespace dstr {

template <typename T>
array<T>::array(i32 size)
    : data_(std::make_unique<T[]>(size)),
      size_(size) {}

template <typename T>
array<T>::array(const array& other)
    : data_(std::make_unique<T[]>(other.size_)),
      size_(other.size_) {
  for (i32 i = 0; i < size_; i++) {
    data_[i] = other.data_[i];
  }
}

template <typename T>
array<T>::array(array&& other) noexcept
    : data_(std::move(other.data_)),
      size_(std::exchange(other.size_, 0)) {}

template <typename T>
bool array<T>::operator==(const array& other) const {
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
bool array<T>::operator!=(const array& other) const {
  return !(*this == other);
}

template <typename T>
array<T>& array<T>::operator=(const array& other) {
  if (this != &other) {
    data_ = std::make_unique<T[]>(other.size_);
    size_ = other.size_;
    for (i32 i = 0; i < size_; i++) {
      data_[i] = other.data_[i];
    }
  }
  return *this;
}

template <typename T>
array<T>& array<T>::operator=(array&& other) noexcept {
  if (this != &other) {
    data_ = std::move(other.data_);
    size_ = std::exchange(other.size_, 0);
  }
  return *this;
}

template <typename T>
T& array<T>::operator[](i32 index) {
  if (index < 0 || index >= size_) {
    throw std::out_of_range("array: index out of range");
  }
  return data_[index];
}

template <typename T>
const T& array<T>::operator[](i32 index) const {
  if (index < 0 || index >= size_) {
    throw std::out_of_range("array: index out of range");
  }
  return data_[index];
}

template <typename T>
T& array<T>::get(i32 index) {
  return (*this)[index];
}

template <typename T>
const T& array<T>::get(i32 index) const {
  return (*this)[index];
}

template <typename T>
i32 array<T>::size() const {
  return size_;
}

template <typename T>
void array<T>::fill(const T& value) {
  for (i32 i = 0; i < size_; i++) {
    data_[i] = value;
  }
}

template <typename T>
bool array<T>::update(i32 index, const T& value) {
  if (index < 0 || index >= size_) {
    return false;
  }
  data_[index] = value;
  return true;
}

template <typename T>
bool array<T>::reset(i32 index) {
  if (index < 0 || index >= size_) {
    return false;
  }
  data_[index] = T{};
  return true;
}

template <typename T>
template <typename Comparator>
void array<T>::bubble_sort(Comparator comp) {
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
void array<T>::insertion_sort(Comparator comp) {
  for (i32 i = 1; i < size_; i++) {
    T key = data_[i];
    i32 j = i - 1;

    while (j >= 0 && comp(key, data_[j])) {
      data_[j + 1] = data_[j];
      j--;
    }

    data_[j + 1] = key;
  }
}

template <typename T>
template <typename Comparator>
void array<T>::quick_sort(Comparator comp) {
  if (size_ <= 1) {
    return;
  }
  quick_sort_helper(comp, 0, size_ - 1);
}

template <typename T>
template <typename KeyComp>
i32 array<T>::linear_search(KeyComp key_comp) const {
  for (i32 i = 0; i < size_; i++) {
    if (key_comp(data_[i])) {
      return i;
    }
  }
  return -1;
}

template <typename T>
template <typename Comparator, typename KeyComp>
i32 array<T>::binary_search(Comparator comp, KeyComp key_comp, const T& target) const {
  i32 low = 0;
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
i32 array<T>::jump_search(Comparator comp, KeyComp key_comp) const {
  if (size_ == 0) {
    return -1;
  }

  i32 step = static_cast<i32>(std::sqrt(static_cast<double>(size_)));
  i32 prev = 0;

  while (prev < size_) {
    i32 block_end = std::min(prev + step, size_) - 1;

    if (key_comp(data_[prev])) {
      return prev;
    }

    if (comp(data_[block_end], data_[size_ - 1]) && !key_comp(data_[block_end])) {
      prev += step;
    } else {
      break;
    }
  }

  i32 block_end = std::min(prev + step, size_);
  for (i32 i = prev; i < block_end; i++) {
    if (key_comp(data_[i])) {
      return i;
    }
  }

  return -1;
}

template <typename T>
i32 array<T>::memory_usage() const {
  return static_cast<i32>(
    (size_ * sizeof(T))
    + sizeof(data_)
    + sizeof(size_)
  );
}

template <typename T>
template <typename Func>
long long array<T>::measure_time(Func func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

template <typename T>
template <typename Comparator>
void array<T>::compare_sorts(Comparator comp) const {
  array<T> copy_bubble(*this);
  array<T> copy_insert(*this);
  array<T> copy_quick(*this);

  long long t_bubble = measure_time([&]() { copy_bubble.bubble_sort(comp); });
  long long t_insert = measure_time([&]() { copy_insert.insertion_sort(comp); });
  long long t_quick = measure_time([&]() { copy_quick.quick_sort(comp); });

  i32 mem = memory_usage();

  std::cout << "\n";
  std::cout << "+--------------------+----------------+----------------+\n";
  std::cout << "| Sort Algorithm     | Time (us)      | Memory (bytes) |\n";
  std::cout << "+--------------------+----------------+----------------+\n";
  std::cout << "| Bubble Sort        | " << std::setw(14) << t_bubble << " | " << std::setw(14) << mem << " |\n";
  std::cout << "| Insertion Sort     | " << std::setw(14) << t_insert << " | " << std::setw(14) << mem << " |\n";
  std::cout << "| Quick Sort         | " << std::setw(14) << t_quick << " | " << std::setw(14) << mem << " |\n";
  std::cout << "+--------------------+----------------+----------------+\n";
  std::cout << "  Total elements: " << size_ << "\n";
}

template <typename T>
template <typename Comparator, typename KeyComp>
void array<T>::compare_searches(Comparator comp, KeyComp key_comp, const T& target) const {
  i32 r_linear = -1;
  i32 r_binary = -1;
  i32 r_jump = -1;

  long long t_linear = measure_time([&]() { r_linear = linear_search(key_comp); });
  long long t_binary = measure_time([&]() { r_binary = binary_search(comp, key_comp, target); });
  long long t_jump = measure_time([&]() { r_jump = jump_search(comp, key_comp); });

  std::cout << "\n";
  std::cout << "+--------------------+------------+--------+\n";
  std::cout << "| Search Algorithm   | Time (us)  | Index  |\n";
  std::cout << "+--------------------+------------+--------+\n";
  std::cout << "| Linear Search      | " << std::setw(10) << t_linear << " | " << std::setw(6) << r_linear << " |\n";
  std::cout << "| Binary Search      | " << std::setw(10) << t_binary << " | " << std::setw(6) << r_binary << " |\n";
  std::cout << "| Jump Search        | " << std::setw(10) << t_jump << " | " << std::setw(6) << r_jump << " |\n";
  std::cout << "+--------------------+------------+--------+\n";
  std::cout << "  Total elements: " << size_ << "\n";
}

template <typename T>
void array<T>::print() const {
  for (i32 i = 0; i < size_; i++) {
    std::cout << "[" << i << "] " << data_[i] << "\n";
  }
}

template <typename T>
void array<T>::swap_elements(i32 i, i32 j) {
  T temp = data_[i];
  data_[i] = data_[j];
  data_[j] = temp;
}

template <typename T>
template <typename Comparator>
i32 array<T>::partition(Comparator comp, i32 low, i32 high) {
  T pivot = data_[high];
  i32 i = low - 1;

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
void array<T>::quick_sort_helper(Comparator comp, i32 low, i32 high) {
  if (low < high) {
    i32 pivot_pos = partition(comp, low, high);
    quick_sort_helper(comp, low, pivot_pos - 1);
    quick_sort_helper(comp, pivot_pos + 1, high);
  }
}

} 
