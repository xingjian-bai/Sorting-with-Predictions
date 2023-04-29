#include "BlockMergeSort.h"
#include "Utils.h"


std::vector<int> BlockMergeSort::sort(SortGame& game) {
    int n = game.getSize();
    vector<int> preds = game.getPreds();
    vector<int> uni_preds = new_pred(preds); // 重排preds，使得preds中的数字连续
    
    vector<int> indexes(n);
    for (int i = 0; i < n; i++)
        indexes[uni_preds[i]] = i;

    blockMergeSort(game, n, indexes);
    return index_to_rank(indexes);
}

int BlockMergeSort::calcMinRun(int n) {
    int r = 0;
    while (n >= 16) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

void BlockMergeSort::insertionSort(SortGame& game, int left, int right, std::vector<int>& indexes) {
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

void BlockMergeSort::merge(SortGame& game, int left, int mid, int right, std::vector<int>& indexes) {
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

void BlockMergeSort::blockMergeSort(SortGame& game, int n, std::vector<int>& indexes) {
    int minRun = calcMinRun(n);

    for (int i = 0; i < n; i += minRun) {
        insertionSort(game, i, std::min(i + minRun - 1, n - 1), indexes);
    }

    for (int size = minRun; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min(left + 2 * size - 1, n - 1);

            merge(game, left, mid, right, indexes);
        }
    }
}