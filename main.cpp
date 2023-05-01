#include "SortController.h"
#include "algorithms/Left.h"
#include "algorithms/Both.h"
#include "algorithms/MergeSort.h"
#include "algorithms/LIS.h"
#include "algorithms/QuickSort.h"
#include "algorithms/HeapSort.h"
#include "algorithms/TimSort.h"
#include "algorithms/BlockMergeSort.h"
#include "algorithms/InsertionSort.h"
#include "settings/Interface.h"
#include "settings/settings.h"
#include "algorithms/Utils.h"
#include <iostream>
#include <random>

using namespace std;



std::vector<ll> A;
std::vector<int> preds;
std::vector<int> ranking;



const int num_algo = 8;
SortAlgorithm *algos[num_algo] = {new BothAlgo(), new LIS(), new MergeSort(), new QuickSort(), new HeapSort(), new TimSort(), new BlockMergeSort(), new InsertionSort()};
string names[num_algo] = {"Both", "LIS", "MergeSort", "QuickSort", "HeapSort", "TimSort", "BlockMergeSort", "InsertionSort"};

vector<vector<int>> results;

void main_objects() {
    const int REP = 1;
    int n = 128 * 128;

    // cout << "n = " << n << endl;
    for (int error = 0; error <= n; error = max (error * 2, error + 1)) {
        // cerr << "start error = " << error << endl;
        double start_time = get_time();
        double error_rate = error / (double)n;
        

        vector <int> result(num_algo, 0);
        for (int i = 0; i < REP; i++) {
            SortGame* game = new SortGame(n);
            // badobject(game, n, error_rate);
            // permuteobject(game, n, error_rate);
            decayobject(game, n, error_rate);


            SortController controller(game);
            for (int i = 0; i < num_algo; i++)
                controller.addAlgorithm(algos[i], names[i]);
            vector<int> tmp = controller.runGame();
            for (int j = 0; j < num_algo; j++)
                result[j] += tmp[j] * 1.0 / REP;
        }

        // game.output_rank();
        results.push_back(result);
        //print result
        for (int i = 0; i < num_algo; i++)
            cerr << result[i] << " ";
        cerr << endl;
        cerr << "finished error = " << error << " time spend: " << get_time() - start_time << endl;
    }

    
}

void main2() { //for country populations
    int n = 263;
    for (int old = 0; old <= 60; old ++) {
        cerr << "start old = " << old << endl;
        double start_time = get_time();
        SortGame* game = new SortGame(n);
        countrypopulation(game, old);

        // game->print();
        SortController controller(game);
        for (int i = 0; i < num_algo; i++)
            controller.addAlgorithm(algos[i], names[i]);

        results.push_back(controller.runGame());
        cerr << "finished old = " << old << " time spend: " << get_time() - start_time << endl;
    }
}



int main() {

    srand(1);

    main_objects();
    
    for (auto name: names)
        cout << name << " ";
    cout << endl;
    output_2D_vector(results);
    return 0;
}
