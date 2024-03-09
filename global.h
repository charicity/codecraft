#ifndef GLOBAL_H
#define GLOBAL_H
#include <set>

#include "Axis.h"
#include "Goods.h"
#include "Grid.h"
#include "Park.h"

extern int ShipCapacity;

extern std::set<Goods> allGoods;  // 所有的没有被拿起过且存在的货物

const Axis kUP{-1, 0}, kRIGHT{0, 1}, kDOWN{1, 0}, kLEFT{0, -1},
    kKEEP{0, 0};  // 上下左右停的向量，用加法

extern Grid grid[kMAX_GRID][kMAX_GRID];

extern Park park[kMAX_PARK];

#endif