#include "SortAlgo.h"
#include "Utils.h"

void Insertion::sort(SortGame &game) {
    int n = game.getSize();
    new_pred();
    
    indexes.resize(n);
    for (int i = 0; i < n; i++)
        indexes[uni_preds[i]] = i;

    for (int i = 1; i < n; i++) {
        int temp = indexes[i];
        int j = i - 1;
        while (j >= 0 && game.compare(temp, indexes[j])) {
            indexes[j + 1] = indexes[j];
            j--;
        }
        indexes[j + 1] = temp;
    }
    
    return index_to_rank();
}
