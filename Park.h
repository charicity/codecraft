#ifndef PARK_H
#define PARK_H

#include <queue>
#include <set>

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
    std::set<int> tend_ship;  // int装的是ship_id
    int time_;      // 表示该泊位轮船运输到虚拟点的时间
    int velocity_;  // 每帧可以装载的物品数
    Axis pre[kMAX_GRID][kMAX_GRID];
    int dis[kMAX_GRID][kMAX_GRID];
    // 初始化泊位信息以及泊位到每个点的bfs路线

    bool is_ban = false;
    static int tot_ban;

    void init();
    void preprocess_bfs();

    void put(const Goods& tobePut);
    void load(Ship& current_ship);

    bool inPark(Axis check) {
        return pos_.x_ <= check.x_ && check.x_ <= (pos_.x_ + 3) &&
               pos_.y_ <= check.y_ && check.y_ <= (pos_.y_ + 3);
    }

    bool have_ship();
};
#endif