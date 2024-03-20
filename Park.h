#ifndef PARK_H
#define PARK_H

#include <climits>
#include <queue>
#include <set>

#include "Axis.h"
#include "Goods.h"
#include "Grid.h"
#include "Ship.h"
const int kMAX_PARK = 10;

class Park {
   public:
    const static int impossible = INT_MAX;
    Park() : pos_{0, 0} {
        time_ = 0;
        velocity_ = 0;
    }
    Axis pos_;
    std::queue<Goods> goods_queue_;
    std::set<int> tend_ship;  // int装的是ship_id
    int id_;
    int time_;      // 表示该泊位轮船运输到虚拟点的时间
    int min_time_;  // 表示该泊位经过其它泊位运输到虚拟点的时间
    int velocity_;  // 每帧可以装载的物品数
    Axis pre[kMAX_GRID][kMAX_GRID];
    int dis[kMAX_GRID][kMAX_GRID];
    // 初始化泊位信息以及泊位到每个点的bfs路线

    bool is_ban = false;
    static int tot_ban, min_back, min_id, max_back;

    void init(int id);
    void preprocess_bfs();
    static void preprocess_mintime();

    void put(const Goods& tobePut);
    void load(Ship& current_ship);

    int canback_from_virtual(Frame& current);
    int canback_from_other(Frame& current);
    bool can_return(Frame& current);

    // 返回是否需要经过其它港口到虚拟点最快
    bool need_shortcut() { return time_ != min_time_; }

    bool inPark(Axis check) {
        return pos_.x_ <= check.x_ && check.x_ <= (pos_.x_ + 3) &&
               pos_.y_ <= check.y_ && check.y_ <= (pos_.y_ + 3);
    }

    bool have_ship();
};
#endif