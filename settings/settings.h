#include "Interface.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
#include <chrono>
using namespace std;

void badobject(SortGame *game, int size, double prob);

void permuteobject(SortGame *game, int size, double prob);

void worstobject(SortGame *game, int size);

void defaultobject(SortGame *game, int size);

void countrypopulation(SortGame *game, int old);

void decayobject(SortGame *game, int size, double decay);