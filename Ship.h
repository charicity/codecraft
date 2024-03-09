#ifndef SHIP_H
#define SHIP_H

const int kMAX_SHIP = 5;

struct Ship {
   public:
    static int capacity_;
    int status_;  // 航行状态（0移动，1到站，2等待）
    int parkid_;  // 正在停靠的驳口id，-1为虚拟点

    static void init();
    void input();
};

#endif