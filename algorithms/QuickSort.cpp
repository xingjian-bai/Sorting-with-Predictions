#include "QuickSort.h"
#include "Utils.h"

std::vector<int> QuickSort::sort(SortGame &game) {
    int n = game.getSize();
    vector<int> preds = game.getPreds();
    vector<int> uni_preds = new_pred(preds); // 重排preds，使得preds中的数字连续
    
    vector<int> indexes(n);
    for (int i = 0; i < n; i++)
        indexes[uni_preds[i]] = i;
    
    cerr << n << "indexes: ";
    for (int i = 0; i < n; i++)
        cerr << indexes[i] << " ";
    cerr << endl;

    quickSort(game, 0, n - 1, indexes);
    
    return index_to_rank(indexes);
}

// Recursively performs quicksort on the subarray defined by low and high indexes
void QuickSort::quickSort(SortGame &game, int low, int high, std::vector<int> &indexes) {
    if (low < high) {
        int pivotIndex = randomPivot(game, low, high, indexes); // Randomly select a pivot index
        pivotIndex = partition(game, low, high, indexes); // Partition the array around the pivot
        quickSort(game, low, pivotIndex - 1, indexes); // Recursively sort the left partition
        quickSort(game, pivotIndex + 1, high, indexes); // Recursively sort the right partition
    }
}

// Partitions the array around the pivot element and returns the new pivot index
int QuickSort::partition(SortGame &game, int low, int high, std::vector<int> &indexes) {
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
int QuickSort::randomPivot(SortGame &game, int low, int high, std::vector<int> &indexes) {
    int pivotIndex = low + std::rand() % (high - low + 1);
    std::swap(indexes[pivotIndex], indexes[high]);
    return pivotIndex;
}