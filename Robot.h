#ifndef ROBOT_H
#define ROBOT_H

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>

#include "Axis.h"
#include "Goods.h"
const int kMAX_ROBOT = 10;

class Frame;

class Robot {
   public:
    int id_;
    static const int RIGHT = 0, LEFT = 1, UP = 2, DOWN = 3, KEEP = 4;
    bool object_;  // 是否正在扛着物品
    bool status_;  // 机器人状态 （0恢复中，1正常）
    Goods carrying;
    Axis pos_;
    int direction;
    void input(int id);
    // 返回{dx,dy}表示他的最优行走方向以及要找的货物的位置
    std::pair<Axis, Axis> get_dir(std::set<Goods>&, Frame&);
    // 返回机器人到id号泊位的最短路径,如果v.size()等于0则没路径
    // std::vector<Axis> get_path(int id);
    // 返回机器人到id号泊位的最短距离长度
    int get_dis(int id);
    // 机器人有了货物后要去到的泊位的估值函数:
    double get_toship_w(int, std::vector<std::vector<int>>&);
    void move(int state);
    void pickUp();     // 捡起一个货物
    void placeDown();  // 放下一个货物
};

#endif