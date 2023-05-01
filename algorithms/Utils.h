#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <vector>
using namespace std;

std::vector<int> new_pred(std::vector<int> preds);

std::vector <int> index_to_rank(std::vector <int> indexes);

void output_2D_vector(std::vector<std::vector<int>> results);

double get_time();

typedef long long ll;
pair<vector<ll>, vector<ll>> parsePopulationData(const std::string &filename, int old);

#endif // UTILS_H
