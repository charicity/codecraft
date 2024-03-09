#ifndef GOODS_H
#define GOODS_H

#include <set>
#include <vector>
#include "Axis.h"

class Goods {
   public:
    Axis pos_{0, 0};
    int value_{0};
    void input();
    // 返回货物到id号泊位的最短路径,如果v.size()等于0则没路径
    std::vector<Axis> get_path(int id);
    //返回货物到id号泊位的最短距离长度
    int get_dis(int id);
};

#endif