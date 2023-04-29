#include "SortController.h"
#include "algorithms/Left.h"
#include "algorithms/Both.h"
#include "algorithms/MergeSort.h"
#include "algorithms/LIS.h"
#include "algorithms/QuickSort.h"
#include "algorithms/HeapSort.h"
#include "algorithms/TimSort.h"
#include "algorithms/BlockMergeSort.h"
#include "settings/Interface.h"
#include "settings/BadObjects.h"
#include <iostream>
#include <random>

using namespace std;
    
int main() {
    srand(1);
    const int N = 1000000;
    const int REP = 10;
    for (int n = 4; n <= 4; n *= 2)
    {
        cout << "n = " << n << endl;
        SortController controller(new BadObjects(n, 0.5));
        // game.output_rank();
        // controller.addAlgorithm(new BothAlgo(), "Both");
        // controller.addAlgorithm(new LIS(), "LIS");
        // controller.addAlgorithm(new MergeSort(), "MergeSort");
        controller.addAlgorithm(new QuickSort(), "QuickSort");
        // controller.addAlgorithm(new HeapSort(), "HeapSort");
        // controller.addAlgorithm(new TimSort(), "TimSort");
        // controller.addAlgorithm(new BlockMergeSort(), "BlockMergeSort");

        controller.runGame();
    }

    return 0;
}
