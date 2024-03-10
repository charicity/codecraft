#ifndef SHIP_H
#define SHIP_H

const int kMAX_SHIP = 5;

struct Ship {
   public:
    int id_;
    static int capacity_;
    int remain_capacity_;
    int status_;  // 航行状态（0移动，1到站，2等待）
    int parkid_;  // 正在停靠的驳口id，-1为虚拟点
    static void init();
    void input(int id);
    // 船要去往的位置 -1，0，1....9,-1表示虚拟点，0-9表示泊位编号
    void go(int id);
};

#endif