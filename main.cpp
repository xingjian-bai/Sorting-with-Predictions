#include "SortController.h"
#include "algorithms/Left.h"
#include "algorithms/Both.h"
#include "Interface.h"
#include <iostream>

using namespace std;
    
int main() {

    for (int n = 4; n <= 100000; n *= 2)
    {
        double average = 0;
        for (int rep = 0; rep < 10; rep ++) {
            SortGame game = SortGame(n);
            // cerr << "init game with " << n << " numbers" << endl;
            // game.print();
            BothAlgo bothalgo;
            SortController controller1(game, bothalgo);
            controller1.runGame();
            double r = game.summary();
            average += r;
            cerr << n << " " << r << endl;
        }
        // cout << n << " : " << average / 10 << endl;
    }

    return 0;
}
