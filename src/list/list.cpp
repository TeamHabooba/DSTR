//list.cpp
#pragma once


#include "list.h"


namespace dstr {


  // node
  template <typename T>
  List<T>::Node::Node(const T& value)
    : data(value), next(nullptr) {
  }

  // list
  template <typename T>
  List<T>::List() : head(nullptr) {}

  template <typename T>
  List<T>::~List() {
    // No manual delete needed (smart pointers handle it)
  }

  template <typename T>
  void List<T>::insert(const T& value) {
    sp<Node> newNode = std::make_shared<Node>(value);
    newNode->next = head;
    head = newNode;
  }

  template <typename T>
  void List<T>::display() const {
    sp<Node> temp = head;

    while (temp != nullptr) {
      std::cout << temp->data << std::endl;
      temp = temp->next;
      }
    }

  template <typename T>
  void List<T>::search(const T& value) const {
    sp<Node> temp = head;

    while (temp != nullptr) {
      if (temp->data == value) {
        std::cout << "Found: " << temp->data << std::endl;
          return;
        }
      temp = temp->next;
      }
      std::cout << "Not found\n";
    }

  // bubblesort
  template <typename T>
  void List<T>::sort() {
    if (!head) return;

    bool swapped;
    do {
      swapped = false;
      sp<Node> current = head;

      while (current->next != nullptr) {
        if (current->data > current->next->data) {
          T temp = current->data;
          current->data = current->next->data;
          current->next->data = temp;
          swapped = true;
        }
        current = current->next;
      }

      } while (swapped);
    }

  template <typename T>
  bool List<T>::empty() const {
    return head == nullptr;
  }


} // namespace dstr
