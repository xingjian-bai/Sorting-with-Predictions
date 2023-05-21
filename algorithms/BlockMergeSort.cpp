#include "SortAlgo.h"
#include "Utils.h"


void BlockMergeSort::sort(SortGame& game) {
    int n = game.getSize();
    new_pred();
    
    indexes.resize(n);
    for (int i = 0; i < n; i++)
        indexes[uni_preds[i]] = i;

    blockMergeSort(game, n);
    return index_to_rank();
}

int BlockMergeSort::calcMinRun(int n) {
    int r = 0;
    while (n >= 1) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

void BlockMergeSort::insertionSort(SortGame& game, int left, int right) {
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

void BlockMergeSort::merge(SortGame& game, int left, int mid, int right) {
    if (mid == right) {
        return;
    }

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {
        if (game.compare(indexes[i], indexes[j])) {
            i++;
        } else {
            int temp = indexes[j];
            int k = j;

            while (k > i) {
                indexes[k] = indexes[k - 1];
                k--;
            }
            indexes[i] = temp;

            i++;
            mid++;
            j++;
        }
    }
}

void BlockMergeSort::blockMergeSort(SortGame& game, int n) {
    int minRun = calcMinRun(n);

    for (int i = 0; i < n; i += minRun) {
        insertionSort(game, i, min(i + minRun - 1, n - 1));
    }

    for (int size = minRun; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);

            merge(game, left, mid, right);
        }
    }
}