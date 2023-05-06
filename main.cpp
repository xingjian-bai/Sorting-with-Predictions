#include "SortController.h"
#include "algorithms/SortAlgo.h"
#include "settings/Interface.h"
#include "settings/settings.h"
#include "algorithms/Utils.h"
#include <iostream>
#include <random>

using namespace std;



vector<ll> A;
vector<int> preds;
vector<int> ranking;
vector <vector<bool>> rel;





vector<vector<int>> results;


void output(vector<string> names) {
    for (auto name: names)
        cout << name << " ";
    cout << endl;
    output_2D_vector(results);
}

void main_objects() {
    const int REP = 5;
    int n = 128;

    const int num_algo = 8;
    SortAlgorithm *algos[num_algo] = {new BothAlgo(), new LIS(), new MergeSort(), new QuickSort(), new HeapSort(), new TimSort(), new BlockMergeSort(), new AdaptiveMergeSort()};
    // , new InsertionSort()};
    string names[num_algo] = {"Both", "LIS", "MergeSort", "QuickSort", "HeapSort", "TimSort", "BlockMergeSort", "AdaptiveMergeSort"};
    //, "InsertionSort"};

    // cout << "n = " << n << endl;
    for (int error = 0; error <= n; error = max (error * 2, error + 1)) {
        // cerr << "start error = " << error << endl;
        double start_time = get_time();
        double error_rate = error / (double)n;
        

        vector <int> result(num_algo, 0);
        for (int i = 0; i < REP; i++) {
            SortGame* game = new SortGame();
            // badobject(game, n, error_rate);
            permuteobject(game, n, error_rate);
            // decayobject(game, n, error_rate);


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

    output(vector<string>(names, names + num_algo));
}

void main2() { //for country populations
    int n = 263;

    const int num_algo = 9;
    SortAlgorithm *algos[num_algo] = {new BothAlgo(), new LIS(), new MergeSort(), new QuickSort(), new HeapSort(), new TimSort(), new BlockMergeSort(), new AdaptiveMergeSort(), new InsertionSort()};
    string names[num_algo] = {"Both", "LIS", "MergeSort", "QuickSort", "HeapSort", "TimSort", "BlockMergeSort", "AdaptiveMergeSort", "InsertionSort"};

    for (int old = 0; old <= 60; old ++) {
        cerr << "start old = " << old << endl;
        double start_time = get_time();
        SortGame* game = new SortGame();
        countrypopulation(game, old);

        // game->print();
        SortController controller(game);
        for (int i = 0; i < num_algo; i++)
            controller.addAlgorithm(algos[i], names[i]);

        results.push_back(controller.runGame());
        cerr << "finished old = " << old << " time spend: " << get_time() - start_time << endl;
    }

    output(vector<string>(names, names + num_algo));
}

void main_relational(int n, int REP) {
    // int n = 128 * 1024;
    // int REP = 4;

    // const int num_algo = 10;
    // SortAlgorithm *algos[num_algo] = {new DirtyClean(), new BothAlgo(), new LIS(), new MergeSort(), new QuickSort(), new HeapSort(), new TimSort(), new BlockMergeSort(), new AdaptiveMergeSort(), new InsertionSort()};
    // string names[num_algo] = {"DirtyClean", "Both", "LIS", "MergeSort", "QuickSort", "HeapSort", "TimSort", "BlockMergeSort", "AdaptiveMergeSort", "InsertionSort"};

    const int num_algo = 4;
    SortAlgorithm *algos[num_algo] = {new DirtyClean(), new LIS(), new naiveDirtyClean(), new DirtyClean2()};
    string names[num_algo] = {"DirtyClean", "LIS", "naiveDirtyClean", "DirtyClean2"};

    for (int error = 0; error <= n; error = max (error * 2, error + 1)) {
        double start_time = get_time();
        double error_rate = error / (double)n;
        

        vector <int> result(num_algo, 0);
        for (int i = 0; i < REP; i++) {
            SortGame* game = new SortGame();
            // cerr << "start error = " << error << " time spend: " << get_time() - start_time << endl;
            // Goodbadrelation(game, n, error_rate);
            Badgoodrelation(game, n, error_rate);
            // cerr << "after error = " << error << " time spend: " << get_time() - start_time << endl;

            SortController controller(game);
            for (int i = 0; i < num_algo; i++)
                controller.addAlgorithm(algos[i], names[i]);
            vector<int> tmp = controller.runGame(i==0);
            for (int j = 0; j < num_algo; j++)
                result[j] += tmp[j] * 1.0 / REP;
        }

        // game.output_rank();
        results.push_back(result);
        //print result
        // cerr << "result: ";
        // for (int i = 0; i < num_algo; i++)
        //     cerr << result[i] << " ";
        // cerr << endl;
        cerr << "finished error = " << error << " time spend: " << get_time() - start_time << endl;
    }

    output(vector<string>(names, names + num_algo));
}


int main() {

    srand(1);

    // main_objects();

    int n, rep;
    cin >> n >> rep;
    main_relational(n, rep);

    return 0;
}
