#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
vector<int> new_pred(vector<int> preds) {
    int n = preds.size();
    vector<int> buckets[n + 1];
    vector<int> uni_preds = preds;
    
    for (int i = 0; i < n; i++)
        buckets[preds[i]].push_back(i);

    int counter = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < buckets[i].size(); j++)
            uni_preds[buckets[i][j]] = counter++;
    
    return uni_preds;
}

vector <int> index_to_rank(vector <int> indexes) {
    vector<int> rank(indexes.size());
    for (int i = 0; i < indexes.size(); i++) {
        rank[indexes[i]] = i;
    }
    return rank;
}

void output_2D_vector(vector<vector<int>> results) {
    int n = results.size();
    int m = results[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << results[j][i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

double get_time() {
    return clock() / (double)CLOCKS_PER_SEC;
}


typedef long long ll;
pair<vector<ll>, vector<ll>> parsePopulationData(const string& filename, int old) {
    ifstream file(filename);
    string line;
    vector<ll> row2021, rowOld;
    int targetYear = 2021 - old;

    getline(file, line);
    getline(file, line); //countries

    while (getline(file, line))
    {
        stringstream ss(line);
        int year;
        ss >> year;
        // cout << "see the target year: " << year << endl;
        if (year == 2021 || year == targetYear) {
            vector<ll> rowData;
            ll value;
            while (ss >> value) {
                // cerr << "value: " << value << endl;
                rowData.push_back(value);
            }

            if (year == 2021) {
                row2021 = rowData;
            }
            if (year == targetYear) {
                rowOld = rowData;
            }
        }

        if (!row2021.empty() && !rowOld.empty()) {
            break;
        }
    }

    // output row2021 and rowOld
    // cout << "row2021: ";
    // for (int i = 0; i < row2021.size(); i++) {
    //     cout << row2021[i] << " ";
    // }
    // cout << endl;
    // cout  << "rowOld: ";
    // for (int i = 0; i < rowOld.size(); i++) {
    //     cout << rowOld[i] << " ";
    // }
    // cout << endl;


    return make_pair(row2021, rowOld);
}
