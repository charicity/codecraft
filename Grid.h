#ifndef GRID_H
#define GRID_H

#include <set>

#include "Axis.h"
#include "Goods.h"

const int kMAX_GRID = 200;

class Grid {
   public:
    Grid() : goodHere() { haveGood = false; }
    bool haveGood = false;
    Goods goodHere;
    int state_;

    static const int empty = 0, ocean = 1, barrier = 2, robot = 3, park = 4;
    void init();

    void place(const Goods& tobeplace);
    void remove();
};

#endif