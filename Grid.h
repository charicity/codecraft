#ifndef GRID_H
#define GRID_H
#include "Axis.h"

const int kMAX_GRID = 200;

class Grid {
   public:
    int grid_[kMAX_GRID][kMAX_GRID]{0};

    const int empty = 0, ocean = 1, barrier = 2, robot = 3, park = 4;
    void input();
}grid;

#endif