#include "MyArray.h"

int main() {
    MyArray<int> arr;

    // Insert elements
    arr.push_back(30);
    arr.push_back(10);
    arr.push_back(50);
    arr.push_back(20);
    arr.push_back(40);

    std::cout << "Original: ";
    arr.print();

    // Sorting using Bubble Sort
    arr.bubbleSort();
    std::cout << "Bubble Sort: ";
    arr.print();

    // Sorting using Quick Sort
    arr.quickSort(0, arr.size() - 1);
    std::cout << "Quick Sort: ";
    arr.print();

    // Searching
    std::cout << "Linear Search (20): " << arr.linearSearch(20) << "\n";
    std::cout << "Binary Search (30): " << arr.binarySearch(30) << "\n";
    std::cout << "Jump Search (40): " << arr.jumpSearch(40) << "\n";

    return 0;
}
