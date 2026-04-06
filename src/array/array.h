#ifndef MYARRAY_H
#define MYARRAY_H

#include <iostream>
#include <cmath>

// Template class to support any data type (int, double, etc.)
template <typename T>
class MyArray {
private:
    T data[100];        // Fixed-size internal storage (simplified)
    int currentSize;    // Number of elements in the array

public:
    // Constructor - initialize size to 0
    MyArray() {
        currentSize = 0;
    }

    // ===== Analysis API =====

    // Returns number of elements
    int size() {
        return currentSize;
    }

    // Checks if array is empty
    bool empty() {
        return currentSize == 0;
    }

    // ===== Access API =====

    // Allows access using arr[index]
    T& operator[](int index) {
        return data[index];   // No bounds check (simple version)
    }

    // ===== Insert API =====

    // Adds element at the end
    void push_back(T value) {
        data[currentSize++] = value;
    }

    // Inserts element at specific index
    void insert(int index, T value) {
        // Shift elements to the right
        for (int i = currentSize; i > index; i--) {
            data[i] = data[i - 1];
        }

        data[index] = value;  // Insert new value
        currentSize++;
    }

    // ===== Delete API =====

    // Removes last element
    void pop_back() {
        currentSize--;
    }

    // Removes element at given index
    void erase(int index) {
        // Shift elements left
        for (int i = index; i < currentSize - 1; i++) {
            data[i] = data[i + 1];
        }

        currentSize--;
    }

    // ===== Print Function =====

    // Displays array elements
    void print() {
        for (int i = 0; i < currentSize; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << "\n";
    }

    // ===== Sorting Algorithms =====

    // Bubble Sort: compares adjacent elements
    void bubbleSort() {
        for (int i = 0; i < currentSize - 1; i++) {
            for (int j = 0; j < currentSize - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    T temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }

    // Insertion Sort: inserts element into correct position
    void insertionSort() {
        for (int i = 1; i < currentSize; i++) {
            T key = data[i];
            int j = i - 1;

            // Shift larger elements to the right
            while (j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                j--;
            }

            data[j + 1] = key;
        }
    }

    // Partition function used in Quick Sort
    int partition(int low, int high) {
        T pivot = data[high];  // Choose last element as pivot
        int i = low;

        for (int j = low; j < high; j++) {
            if (data[j] < pivot) {
                // Swap elements
                T temp = data[i];
                data[i] = data[j];
                data[j] = temp;
                i++;
            }
        }

        // Place pivot in correct position
        T temp = data[i];
        data[i] = data[high];
        data[high] = temp;

        return i;
    }

    // Quick Sort: divide and conquer sorting
    void quickSort(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);

            // Recursively sort left and right
            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }
    }

    // ===== Searching Algorithms =====

    // Linear Search: checks every element
    int linearSearch(T target) {
        for (int i = 0; i < currentSize; i++) {
            if (data[i] == target)
                return i;
        }
        return -1; // Not found
    }

    // Binary Search: works on sorted array
    int binarySearch(T target) {
        int left = 0, right = currentSize - 1;

        while (left <= right) {
            int mid = (left + right) / 2;

            if (data[mid] == target)
                return mid;
            else if (data[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return -1;
    }

    // Jump Search: faster than linear for sorted arrays
    int jumpSearch(T target) {
        int step = std::sqrt(currentSize);
        int prev = 0;

        // Jump ahead in blocks
        while (prev < currentSize &&
               data[(step < currentSize ? step : currentSize) - 1] < target) {
            prev = step;
            step += std::sqrt(currentSize);

            if (prev >= currentSize)
                return -1;
        }

        // Linear search in block
        for (int i = prev; i < (step < currentSize ? step : currentSize); i++) {
            if (data[i] == target)
                return i;
        }

        return -1;
    }
};

#endif
