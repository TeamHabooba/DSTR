// list.h
#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../common/common.h"

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
        static constexpr float PROB = 0.5f;

        Node* head_;
        int   currentLevel_;

        int                randomLevel();
        std::vector<Node*> findUpdate(const T& value);

    public:
        List();
        ~List();

        void insert(const T& value);
        void display()  const;
        void search(const T& value) const;
        bool remove(const T& value);
        void sort();
        bool empty() const;
    };

} // namespace dstr

// Implementation — must be visible to every translation unit that uses List<T>
#include "list.inl"
