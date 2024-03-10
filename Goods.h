#ifndef GOODS_H
#define GOODS_H

#include <set>
#include <vector>

#include "Axis.h"
#include "global.h"

class Goods {
   public:
    Axis pos_{0, 0};
    int value_{0};
    bool state;  // 表示当前货物是否被某个机器人锁定
    void input();
    // 返回货物到id号泊位的最短路径,如果v.size()等于0则没路径
    std::vector<Axis> get_path(int id);
    // 返回货物到id号泊位的最短距离长度
    int get_dis(int id);

    bool operator<(Goods a) const {
        if (value_ != a.value_) {
            return value_ < a.value_;
        }
        return pos_ < a.pos_;
    }

    void place() {
        allGoods.insert(*this);
        ;
    }
};

#endif