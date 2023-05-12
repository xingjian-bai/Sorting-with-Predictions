#include "SortAlgo.h"
#include "Utils.h"

void MergeSort::sort(SortGame& game) {
    int n = game.getSize();
    new_pred();
    
    indexes.resize(n);
    for (int i = 0; i < n; i++)
        indexes[uni_preds[i]] = i;

    mergeSort(game, 0, n - 1);
    
    return index_to_rank();
}

// Recursively divides the array into two halves, sorts them, and then merges the two sorted halves
void MergeSort::mergeSort(SortGame& game, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(game, low, mid);
        mergeSort(game, mid + 1, high);
        merge(game, low, mid, high);
    }
}

// Merges two sorted subarrays defined by their low, mid, and high indices
void MergeSort::merge(SortGame& game, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    // Create temporary arrays for the two subarrays
    std::vector<int> left(n1);
    std::vector<int> right(n2);

    // Copy the original array elements to the temporary arrays
    for (int i = 0; i < n1; i++)
        left[i] = indexes[low + i];
    for (int j = 0; j < n2; j++)
        right[j] = indexes[mid + 1 + j];

    // Merge the temporary arrays back into the original array
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (game.compare(left[i], right[j])) {
            indexes[k++] = left[i++];
        } else {
            indexes[k++] = right[j++];
        }
    }

    // Copy any remaining elements in the left temporary array
    while (i < n1)
        indexes[k++] = left[i++];
    // Copy any remaining elements in the right temporary array
    while (j < n2)
        indexes[k++] = right[j++];
}





