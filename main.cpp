#include "SortController.h"
#include "algorithms/SortAlgo.h"
#include "settings/Interface.h"
#include "settings/settings.h"
#include "algorithms/Utils.h"
#include <iostream>
#include <random>

using namespace std;

vector<vector<int>> buckets;

vector<ll> A;             // 数字数组
vector<int> preds;        // 预测排名数组
vector<int> ranking;      // 真实排名数组
vector<vector<bool>> rel; // 关系数组

vector<int> sorted, uni_preds, indexes;

vector<int> output_rank;

// for tim sort
vector<int> leftTemp, rightTemp;

// for OESM
vector<int> odd_l, odd_r, even_l, even_r, merged;

// for Kim Cook
vector<int> ordered, unordered1, unordered2;

// for Both
vector<int> p_to_A, inserted;
vector<int> left_sorted, right_sorted, left_bef, right_aft, combine;

// for DirtyClean2
vector<int> shuffledA;

// for ScapegoatTree
vector<Node*> nodes;

vector<vector<ll>> results;

vector <string> names{
    "MergeSort",
    "QuickSort",
    "TimSort",
    "BlockMergeSort",
    "OESM",
    "Cook_Kim",

    "LIS",
    "LIS_small",
    "LIS_treap",
};
//, "Both"};  //, "naiveDirtyClean2"};
vector <SortAlgorithm*> algos {
    new MergeSort(),
    new QuickSort(),
    new TimSort(),
    new BlockMergeSort(),
    new OESM(),
    new Cook_Kim(),

    new LIS(),
    new LIS_small(),
};
//, new BothAlgo()}; //, new naiveDirtyClean2()}

void main_objects(int n, int REP, string setting)
{
    int num_algo = algos.size();
    // cout << "n = " << n << endl;
    int gap = 20;
    for (int i = 0; i <= gap; i++)
    {
        // cerr << "start error = " << error << endl;
        double start_time = get_time();
        double error_rate = i / (double)gap;

        vector<ll> result(num_algo, 0);
        for (int i = 0; i < REP; i++)
        {
            SortGame *game = new SortGame();

            if (setting == "exact")
                defaultrelation(game, n);
            else if (setting == "bad")
                badobject(game, n, error_rate);
            else if (setting == "permute")
                permuteobject(game, n, error_rate);
            else if (setting == "decay")
                decayobject(game, n, error_rate);
            else if (setting == "decay2")
                decayobject2(game, n, error_rate);
            else
            {
                cerr << "wrong setting" << endl;
                exit(0);
            }
            // badobject(game, n, error_rate);
            // permutseobject(game, n, error_rate);
            // decayobject(game, n, error_rate);
            // worstobject(game, n);

            SortController controller(game);
            for (int i = 0; i < num_algo; i++)
                controller.addAlgorithm(algos[i], names[i]);

            vector<ll> tmp = controller.runGame();
            for (int j = 0; j < num_algo; j++)
                result[j] += tmp[j] * 1.0 / REP;
        }

        // game.output_rank();
        results.push_back(result);
        // print result
        for (int i = 0; i < num_algo; i++)
            cerr << result[i] << " ";
        cerr << endl;
        cerr << "finished error = " << error_rate << " time spend: " << get_time() - start_time << endl;
    }
}

void main2()
{ // for country populations
    int n = 263;
    int num_algo = algos.size();

    for (int old = 0; old <= 60; old++)
    {
        cerr << "start old = " << old << endl;
        double start_time = get_time();
        SortGame *game = new SortGame();
        countrypopulation(game, old);

        // game->print();
        SortController controller(game);
        for (int i = 0; i < num_algo; i++)
            controller.addAlgorithm(algos[i], names[i]);

        results.push_back(controller.runGame());
        cerr << "finished old = " << old << " time spend: " << get_time() - start_time << endl;
    }
}

void main_relational(int n, int REP, string setting)
{
    int num_algo = algos.size();
    for (int error = 0; error / 2 < n; error = max(error * 2, error + 1))
    {
        double start_time = get_time();
        double error_rate = error / (double)n;
        error = min(error, n);

        vector<ll> result(num_algo, 0);
        for (int i = 0; i < REP; i++)
        {
            SortGame *game = new SortGame();
            if (setting == "goodbad" || setting == "gb")
                Goodbadrelation(game, n, error_rate);
            else if (setting == "badgood" || setting == "bg")
                Badgoodrelation(game, n, error_rate);
            else if (setting == "prod")
                Productrelation(game, n, error_rate);
            else if (setting == "prod2")
                Productrelation2(game, n, error_rate);
            else if (setting == "indep")
                IndepRelation(game, n, error_rate);
            else if (setting == "sigmoid")
            {
                SigmoidRelation(game, n, error_rate);
                // game->print();
            }
            else
            {
                cerr << "wrong setting" << endl;
                exit(0);
            }

            SortController controller(game);
            for (int i = 0; i < num_algo; i++)
                controller.addAlgorithm(algos[i], names[i]);
            vector<ll> tmp = controller.runGame(i == 0);
            for (int j = 0; j < num_algo; j++)
                result[j] += tmp[j] * 1.0 / REP;
        }

        // game.output_rank();
        results.push_back(result);
        // print result
        //  cerr << "result: ";
        //  for (int i = 0; i < num_algo; i++)
        //      cerr << result[i] << " ";
        //  cerr << endl;
        cerr << "finished error = " << error << " time spend: " << get_time() - start_time << endl;
    }
}

// void main_tennis(int n, int REP) {
//     // const int num_algo = 11;
//     // SortAlgorithm *algos[num_algo] = {new DirtyClean(), new LIS(), new naiveDirtyClean(), new DirtyClean2(), new naiveDirtyClean2(), new BothAlgo(), new MergeSort(), new QuickSort(), new HeapSort(), new TimSort(), new BlockMergeSort()};
//     // string names[num_algo] = {"DirtyClean", "LIS","Both", "MergeSort", "QuickSort", "HeapSort", "TimSort", "BlockMergeSort"};

//         double start_time = get_time();

//         vector <int> result(num_algo, 0);
//         for (int i = 0; i < REP; i++) {
//             SortGame* game = new SortGame();
//             Tennisrelation(game, n);

//             SortController controller(game);
//             for (int i = 0; i < num_algo; i++)
//                 controller.addAlgorithm(algos[i], names[i]);
//             vector<int> tmp = controller.runGame(i==0);
//             for (int j = 0; j < num_algo; j++)
//                 result[j] += tmp[j] * 1.0 / REP;
//         }

//         results.push_back(result);
//         cerr << "finished " << get_time() - start_time << endl;
//     // }
//     output(vector<string>(names, names + num_algo));
// }

int main()
{

    srand(1);

    // main2();
    string pred_type, setting;
    int n, rep;
    cin >> pred_type >> setting;
    if (pred_type == "positional" || pred_type == "p")
    {
        if (setting == "country" || setting == "c")
        {
            main2();
        }
        else
        {
            cin >> n >> rep;
            main_objects(n, rep, setting);
        }
    }
    else if (pred_type == "relational" || pred_type == "r")
    {
        names.push_back("DirtyClean2");
        algos.push_back(new DirtyClean2());
        cin >> n >> rep;
        main_relational(n, rep, setting);
    }

    // turn n, rep into string
    string n_str = to_string(n);
    string rep_str = to_string(rep);

    int num_algo = algos.size();
    
    output_to_file(names, results, pred_type + "_" + setting + "_" + n_str + "_" + rep_str);
    return 0;
}
