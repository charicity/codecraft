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
    Park(Axis pos, int time, int velocity) {
        pos_ = pos;
        time_ = time;
        velocity_ = velocity;
        while (!goods_queue_.empty()) goods_queue_.pop();
        while (!ships_queue_.empty()) ships_queue_.pop();
    }
    Axis pos_;
    std::queue<Goods> goods_queue_;
    std::queue<Ship> ships_queue_;
    int time_;      // 表示该泊位轮船运输到虚拟点的时间
    int velocity_;  // 每帧可以装载的物品数
    Axis pre[kMAX_GRID][kMAX_GRID];
    int dis[kMAX_GRID][kMAX_GRID];
    // 初始化泊位信息以及泊位到每个点的bfs路线
    void init();
};

Park park[kMAX_PARK];

#endif