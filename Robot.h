#ifndef ROBOT_H
#define ROBOT_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <utility>
#include "Axis.h"
const int kMAX_ROBOT = 10;

class Robot {
   public:
    static const int UP = 2, DOWN = 3, LEFT = 1, RIGHT = 0;
    bool object_;       // 是否正在扛着物品
    bool status_;       // 机器人状态 （0恢复中，1正常）
    int object_value_;  // 机器人扛着的物品的价值
    Axis pos_;
    int direction;
    void input();
    // 返回{dx,dy}表示他的最优行走方向以及要找的货物的位置
    std::pair<Axis,Axis> get_dir();
    void move(int state);
    void pick();
    void pull();
    // 返回机器人到id号泊位的最短路径,如果v.size()等于0则没路径
    std::vector<Axis> get_path(int id);
    // 返回机器人到id号泊位的最短距离长度
    int get_dis(int id);
};

#endif