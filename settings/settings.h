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
void decayobject2(SortGame *game, int size, double decay);

void defaultrelation(SortGame *game, int size);

void Goodbadrelation(SortGame *game, int size, double ratio);

void Badgoodrelation(SortGame *game, int size, double ratio);

void Productrelation(SortGame *game, int size, double ratio);
void Productrelation2(SortGame *game, int size, double ratio);

void IndepRelation(SortGame *game, int size, double ratio);

void Tennisrelation(SortGame *game, int size);

void SigmoidRelation(SortGame *game, int size, double ratio);