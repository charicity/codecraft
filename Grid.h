#ifndef GRID_H
#define GRID_H

#include <set>

#include "Axis.h"

const int kMAX_GRID = 200;

class Grid {
   public:
    std::set<Goods> stacks_;
    int state_;

    static const int empty = 0, ocean = 1, barrier = 2, robot = 3, park = 4;
    void input();
};
Grid grid[kMAX_GRID][kMAX_GRID];

#endif