#ifndef ROBOT_H
#define ROBOT_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "Axis.h"
const int kMAX_ROBOT = 10;

class Robot {
   public:
    bool object_;       // 是否正在扛着物品
    bool status_;       // 机器人状态 （0恢复中，1正常）
    int object_value_;  // 机器人扛着的物品的价值
    Axis pos_;

    void input();
    //返回dx,dy表示他的行走方向
    Axis get_dir();
    // 返回机器人到id号泊位的最短路径,如果v.size()等于0则没路径
    std::vector<Axis> get_path(int id);
    //返回机器人到id号泊位的最短距离长度
    int get_dis(int id);
};

#endif