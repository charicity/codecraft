#ifndef SHIP_H
#define SHIP_H
class Frame;

const int kMAX_SHIP = 5;

struct Ship {
   public:
    int id_;
    static int capacity_;
    int remain_capacity_;
    int status_;  // 航行状态（0移动，1到站，2等待）
    int parkid_;  // 正在停靠的驳口id，-1为虚拟点

    // 有Ship_Keep后期维护
    int last_;

    static void init();
    void input(int id);
    // 船要去往的位置 -1，0，1....9,-1表示虚拟点，0-9表示泊位编号
    void go(int id, Frame& current);
};

struct Ship_Keep {
    int last_;  // 最后一次到岗在的地方
};

#endif