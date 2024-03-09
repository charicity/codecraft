#ifndef SHIP_H
#define SHIP_H

const int kMAX_SHIP = 5;

class Ship {
   public:
    int capacity_;  // 最多能装的物品数
    int status_;    // 航行状态
    int parkid_;    // 正在停靠的驳口id，-1为虚拟点

    void init();
    void input();
};

#endif