#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <random>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

void new_pred() {
    // input: preds
    // output: uni_preds
    int n = preds.size();

    buckets.resize(n + 1);
    for (int i = 0; i <= n; i++)
        buckets[i].clear();
    uni_preds.resize(n);
    
    for (int i = 0; i < n; i++)
        buckets[preds[i]].push_back(i);
    
    //random shuffle each bucket
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < buckets[i].size(); j++)
            swap(buckets[i][j], buckets[i][rand() % buckets[i].size()]);

    int counter = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < buckets[i].size(); j++)
            uni_preds[buckets[i][j]] = counter++;
    
}

void index_to_rank() {
    // input: indexes
    // output: output_rank
    output_rank.clear();
    output_rank.resize(indexes.size());
    for (int i = 0; i < indexes.size(); i++) {
        output_rank[indexes[i]] = i;
    }
}

void output_to_file(vector<string> names, vector<vector<vector<ll>>> results, string filename) {
    //output to a file
    int n = results.size();
    int m = results[0].size();
    // cerr << "sizes" << names.size() << " " << n << " " << m << endl;
    for (int i = 0; i < m; i++) {
        //align
        // cout << names[i] << " ";
        for (int j = 0; j < n; j++) {
            vector <ll> reps = results[j][i];
            cout << names[i] << " ";
            for (int k = 0; k < reps.size(); k++) {
                cout << reps[k] << " ";
            }
            cout << endl;
        }
    }

    ofstream outFile("data/" + filename + ".txt");
    cerr << "saved to " << filename << endl;
    for (int i = 0; i < m; i++) {
        outFile << names[i] << " ";
    }
    outFile << endl
            << m << " " << n << " " << results[0][0].size() << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            vector <ll> reps = results[j][i];
            for (int k = 0; k < reps.size(); k++) {
                outFile << reps[k] << " ";
            }
            outFile << endl;
        }
    }
    outFile.close();
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

vector <vector<bool> > parseTennisRelation(const string &filename, int size) 
{
    ifstream file(filename);
    //first line is the number of players
    int n;
    file >> n;
    cout << "n: " << n << endl;
    //the rest of the file is the relation
    string line;
    vector <vector<bool> > relation;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        vector<bool> row;
        bool value;
        while (ss >> value)
            row.push_back(value);
        relation.push_back(row);
    }
    
    return relation;
}