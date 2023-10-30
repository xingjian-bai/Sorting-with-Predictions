#include "Interface.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
#include <chrono>
using namespace std;

void defaultobject(SortGame *game, int size);
void countrypopulation(SortGame *game, int old);
// void decayobject(SortGame *game, int size, double decay);
void decayobject2(SortGame *game, int size, double decay);
void decayobject2_1000(SortGame *game, int size, double decay);
void localshuffleobject(SortGame *game, int size, int seg);

void new_object_setting(SortGame *game, int size, double ratio);
void swap_and_noise(SortGame *game, int size, double ratio);

void defaultrelation(SortGame *game, int size);
void Goodbadrelation(SortGame *game, int size, double ratio);
void Badgoodrelation(SortGame *game, int size, double ratio);