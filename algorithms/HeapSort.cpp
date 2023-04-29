#include "HeapSort.h"
#include "Utils.h"

std::vector<int> HeapSort::sort(SortGame& game) {
    int n = game.getSize();
    vector<int> preds = game.getPreds();
    vector<int> uni_preds = new_pred(preds); // 重排preds，使得preds中的数字连续
    
    vector<int> indexes(n);
    for (int i = 0; i < n; i++)
        indexes[uni_preds[i]] = i;

    

    // Build the max heap
    buildMaxHeap(game, n, indexes);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        swap(indexes[0], indexes[i]); // Move current root (largest element) to the end
        heapify(game, i, 0, indexes); // Call heapify on the reduced heap
    }

    return index_to_rank(indexes);
}

void HeapSort::buildMaxHeap(SortGame& game, int n, std::vector<int>& indexes) {
    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(game, n, i, indexes);
    }
}

void HeapSort::heapify(SortGame& game, int n, int i, std::vector<int>& indexes) {
    int largest = i;         // Initialize largest as root
    int left = 2 * i + 1;     // Left child index
    int right = 2 * i + 2;    // Right child index

    // If left child is larger than root
    if (left < n && game.compare(indexes[largest], indexes[left])) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && game.compare(indexes[largest], indexes[right])) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swap(indexes[i], indexes[largest]);

        // Recursively heapify the affected sub-tree
        heapify(game, n, largest, indexes);
    }
}

void HeapSort::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}