#include "SortAlgo.h"

class QuickSort : public SortAlgorithm {
public:
    //init functions
    QuickSort() = default;

    std::vector<int> sort(SortGame& game) override;

private:
    static void quickSort(SortGame &game, int low, int high, std::vector<int> &indexes);
    static int partition(SortGame &game, int low, int high, std::vector<int> &indexes);
    static int randomPivot(SortGame &game, int low, int high, std::vector<int> &indexes);
};
