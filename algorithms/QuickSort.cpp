#include "SortAlgo.h"
#include "Utils.h"

void QuickSort::sort(SortGame &game) {
    int n = game.getSize();
    new_pred();
    
    indexes.resize(n);
    for (int i = 0; i < n; i++)
        indexes[uni_preds[i]] = i;

    quickSort(game, 0, n - 1);
    
    return index_to_rank();
}

// Recursively performs quicksort on the subarray defined by low and high indexes
void QuickSort::quickSort(SortGame &game, int low, int high) {
    if (low < high) {
        int pivotIndex = randomPivot(game, low, high); // Randomly select a pivot index
        pivotIndex = partition(game, low, high); // Partition the array around the pivot
        quickSort(game, low, pivotIndex - 1); // Recursively sort the left partition
        quickSort(game, pivotIndex + 1, high); // Recursively sort the right partition
    }
}

// Partitions the array around the pivot element and returns the new pivot index
int QuickSort::partition(SortGame &game, int low, int high) {
    int pivotIndex = high;
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (game.compare(indexes[j], indexes[pivotIndex])) {
            i++;
            std::swap(indexes[i], indexes[j]);
        }
    }
    std::swap(indexes[i + 1], indexes[pivotIndex]);
    return i + 1;
}

// Randomly selects a pivot index and swaps it with the last element
int QuickSort::randomPivot(SortGame &game, int low, int high) {
    int pivotIndex = low + std::rand() % (high - low + 1);
    std::swap(indexes[pivotIndex], indexes[high]);
    return pivotIndex;
}