#ifndef GRID_H
#define GRID_H

#include "Axis.h"

class Grid {
    int grid_[200][200]{0};

    const int empty = 0, ocean = 1, barrier = 2, robot = 3, park = 4;
    void input();
};

#endif