// list.h
#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../common/aliases.h"

namespace dstr {

  template <typename T>
  class List {
  private:
    struct Node {
      T data;
      std::vector<Node*> forward;

      Node(const T& value, int level);
    };

    static constexpr int   MAX_LEVEL = 16;
    static constexpr float PROB      = 0.5f;

    Node* head_;
    int   currentLevel_;
    int   size_;

    int                randomLevel();
    std::vector<Node*> findUpdate(const T& value);

  public:
    List();
    ~List();

    // Core operations
    void insert(const T& value);
    void display()  const;
    void search(const T& value) const;
    bool remove(const T& value);
    void sort();        // no-op: always sorted on insert
    bool empty() const;
    int  size()  const;

    // Calls fn(element) for every node in sorted order
    template <typename Visitor>
    void for_each(Visitor fn) const;

    // O(log n) lookup — returns pointer to data, nullptr if not found
    const T* find(const T& value) const;
  };

} // namespace dstr

#include "list.inl"
