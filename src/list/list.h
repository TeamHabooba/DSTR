//list.h
#pragma once


#include "../common/common.h" 


namespace dstr {

  template <typename T>
  class List {
    private:
    struct Node {
      T data;
      sp<Node> next;

      Node(const T& value);
    };

    sp<Node> head;

    public:
      List();
      ~List();

    // Basic operations
    void insert(const T& value);
    void display() const;
    void search(const T& value) const;
    void sort();
    bool empty() const;
    };


} // namespace dstr

