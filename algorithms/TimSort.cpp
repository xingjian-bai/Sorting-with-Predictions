#include "SortAlgo.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


vector<int> TimSort::sort(SortGame& game) {
    int n = game.getSize();
    vector<int> preds = game.getPreds();
    vector<int> uni_preds = new_pred(preds); // 重排preds，使得preds中的数字连续
    
    vector<int> indexes(n);
    for (int i = 0; i < n; i++)
        indexes[uni_preds[i]] = i;

    // cerr << "bef sort" << endl;
    timSort(game, n, indexes);
    // cerr << "aft sort" << endl;

    return index_to_rank(indexes);
}

void TimSort::insertionSort(SortGame& game, int left, int right, std::vector<int>& indexes) {
    for (int i = left + 1; i <= right; i++) {
        int temp = indexes[i];
        int j = i - 1;
        while (j >= left && game.compare(temp, indexes[j])) {
            indexes[j + 1] = indexes[j];
            j--;
        }
        indexes[j + 1] = temp;
    }
}

void TimSort::merge(SortGame& game, int left, int mid, int right, std::vector<int>& indexes) {
    int len1 = mid - left + 1;
    int len2 = right - mid;

    // Create temporary arrays for the two subarrays
    std::vector<int> leftTemp(len1);
    std::vector<int> rightTemp(len2);

    // Copy the original array elements to the temporary arrays
    for (int i = 0; i < len1; i++) {
        leftTemp[i] = indexes[left + i];
    }
    for (int j = 0; j < len2; j++) {
        rightTemp[j] = indexes[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    // Merge the temporary arrays back into the original array
    while (i < len1 && j < len2) {
        if (game.compare(leftTemp[i], rightTemp[j])) {
            indexes[k++] = leftTemp[i++];
        } else {
            indexes[k++] = rightTemp[j++];
        }
    }

    // Copy any remaining elements in the left temporary array
    while (i < len1) {
        indexes[k++] = leftTemp[i++];
    }

    // Copy any remaining elements in the right temporary array
    while (j < len2) {
        indexes[k++] = rightTemp[j++];
    }
}

void TimSort::timSort(SortGame& game, int n, std::vector<int>& indexes) {
    // Apply insertion sort on small subarrays (length <= RUN)
    for (int i = 0; i < n; i += RUN) {
        insertionSort(game, i, std::min(i + RUN - 1, n - 1), indexes);
    }
    // cerr << "aft insertion sort" << endl;

    // Merge the sorted subarrays
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min(left + 2 * size - 1, n - 1);

            // if right is empty
            if (mid >= right) {
                continue;
            }

            // Merge the two subarrays
            merge(game, left, mid, right, indexes);
        }
    }
}