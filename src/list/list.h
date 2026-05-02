//list.h
#pragma once

#include <memory>
#include "common/aliases.h" 

namespace dstr {

  template <typename T>
  class list {
    private:
    struct Node {
      T data;
      sp<Node> next;

      Node(const T& value);
    };

    sp<Node> head;

    public:
      list();
      ~list();

    // Basic operations
    void insert(const T& value);
    void display() const;

    // Searching
    void search(const T& value) const;

    // Sorting
    void sort();

    // Utility
    bool empty() const;
    };

} // namespace dstr

#include "list.cpp"
