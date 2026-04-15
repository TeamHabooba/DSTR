#include "list.h"
#include <iostream>

namespace dstr {

    // ================= NODE =================
    template <typename T>
    list<T>::Node::Node(const T& value)
        : data(value), next(nullptr) {
    }


    // ================= LIST =================
    template <typename T>
    list<T>::list() : head(nullptr) {}

    template <typename T>
    list<T>::~list() {
        // No manual delete needed (smart pointers handle it)
    }


    // ================= INSERT =================
    template <typename T>
    void list<T>::insert(const T& value) {
        sp<Node> newNode = std::make_shared<Node>(value);
        newNode->next = head;
        head = newNode;
    }


    // ================= DISPLAY =================
    template <typename T>
    void list<T>::display() const {
        sp<Node> temp = head;

        while (temp != nullptr) {
            std::cout << temp->data << std::endl;
            temp = temp->next;
        }
    }


    // ================= SEARCH =================
    template <typename T>
    void list<T>::search(const T& value) const {
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


    // ================= SORT (Bubble) =================
    template <typename T>
    void list<T>::sort() {
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


    // ================= EMPTY =================
    template <typename T>
    bool list<T>::empty() const {
        return head == nullptr;
    }

} // namespace dstr
