#ifndef GLOBAL_H
#define GLOBAL_H
#include <cstring>
#include <queue>
#include <set>

#include "Axis.h"
#include "Goods.h"
#include "Grid.h"
#include "Park.h"
extern int get_distance(Axis a, Axis b);

extern std::set<Goods> unpickedGoods;  // 所有的没有被拿起过且存在的货物
extern std::set<Goods> safeGoods;  // 所有被拿起过的且还在场上（没被运走）的货物

const Axis kUP{-1, 0}, kRIGHT{0, 1}, kDOWN{1, 0}, kLEFT{0, -1},
    kKEEP{0, 0};  // 上下左右停的向量，用加法

extern Grid grid[kMAX_GRID][kMAX_GRID];

extern Park park[kMAX_PARK];

#endif