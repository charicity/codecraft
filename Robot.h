#ifndef ROBOT_H
#define ROBOT_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
const int kMAX_ROBOT = 10;

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
    // robot去哪个点的路径
    std::vector<Axis> get_path(Axis);
    // robot去哪拿哪个货物再去哪个
    void get_which_good_and_ship();
};

#endif