#ifndef ROBOT_H
#define ROBOT_H

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

#include "Axis.h"
const int kMAX_ROBOT = 10;

class Robot {
   public:
    bool object_;  // 是否正在扛着物品
    bool status_;  // 机器人状态 （0恢复中，1正常）
    Goods carrying;
    Axis pos_;

    void input();
    // 返回{dx,dy}表示他的行走方向
    Axis get_dir();
    // 返回机器人到id号泊位的最短路径,如果v.size()等于0则没路径
    std::vector<Axis> get_path(int id);
    // 返回机器人到id号泊位的最短距离长度
    int get_dis(int id);

    void pickUp(Goods &tobePicked);  // 捡起一个货物
    void placeDown();                // 放下一个货物
};

#endif