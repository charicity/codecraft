#ifndef PARK_H
#define PARK_H

#include <queue>

#include "Axis.h"
#include "Goods.h"
#include "Grid.h"
#include "Ship.h"
const int kMAX_PARK = 10;

class Park {
   public:
    Park() : pos_{0, 0} {
        time_ = 0;
        velocity_ = 0;
    }
    Axis pos_;
    std::queue<Goods> goods_queue_;
    int time_;      // 表示该泊位轮船运输到虚拟点的时间
    int velocity_;  // 每帧可以装载的物品数
    Axis pre[kMAX_GRID][kMAX_GRID];
    int dis[kMAX_GRID][kMAX_GRID];
    // 初始化泊位信息以及泊位到每个点的bfs路线
    void init();
    void load(Ship& ship);
    void preprocess_bfs();

    void put(const Goods& tobePut);
    void load(Ship& current_ship);
};

#endif