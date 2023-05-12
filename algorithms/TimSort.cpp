#include "SortAlgo.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


void TimSort::sort(SortGame& game) {
    int n = game.getSize();
    new_pred();

    indexes.resize(n);
    for (int i = 0; i < n; i++)
        indexes[uni_preds[i]] = i;

    timSort(game, n);
    index_to_rank();
}

void TimSort::insertionSort(SortGame& game, int left, int right) {
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

void TimSort::merge(SortGame& game, int left, int mid, int right) {
    int len1 = mid - left + 1;
    int len2 = right - mid;

    leftTemp.resize(len1);
    rightTemp.resize(len2);
    for (int i = 0; i < len1; i++)    leftTemp[i] = indexes[left + i];
    for (int j = 0; j < len2; j++)    rightTemp[j] = indexes[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Merge the temporary arrays back into the original array
    while (i < len1 && j < len2) {
        if (game.compare(leftTemp[i], rightTemp[j]))    indexes[k++] = leftTemp[i++];
        else    indexes[k++] = rightTemp[j++];
    }

    while (i < len1)    indexes[k++] = leftTemp[i++];
    while (j < len2)    indexes[k++] = rightTemp[j++];
}

void TimSort::timSort(SortGame& game, int n) {
    // Apply insertion sort on small subarrays (length <= RUN)
    for (int i = 0; i < n; i += RUN) {
        insertionSort(game, i, std::min(i + RUN - 1, n - 1));
    }
    // cerr << "aft insertion sort" << endl;

    // Merge the sorted subarrays
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min(left + 2 * size - 1, n - 1);

            // if right is empty
            if (mid >= right)
                continue;

            // Merge the two subarrays
            merge(game, left, mid, right);
        }
    }
}