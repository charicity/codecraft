#ifndef GOODS_H
#define GOODS_H

#include <queue>
#include <set>
#include <vector>

#include "Axis.h"

extern void goods_expire(int current_frame);

class Goods {
   public:
    static const int kMAX_EXPIRE = 1000;
    Goods() : pos_(0, 0) {}
    int code_;            // 独一无二的编号
    int happened_frame_;  // 出现的帧
    Axis pos_;   // 货物的坐标，被捡起之后的货物不维护这个值
    int value_;  // 本货物的价值
    bool state;  // 表示当前货物是否被某个机器人锁定
    void input(int current_frame);  // 输入这个货物，自动标号

    // 返回货物到id号泊位的最短路径,如果v.size()等于0则没路径
    std::vector<Axis> get_path(int id);
    // 返回货物到id号泊位的最短距离长度
    int get_dis(int id);

    bool operator<(const Goods& a) const {
        if (happened_frame_ != a.happened_frame_)
            return happened_frame_ < a.happened_frame_;
        return code_ < a.code_;
    }

    void showoff();
    int expire_frame(int code_) {
        return (happened_frame_ + Goods::kMAX_EXPIRE) - code_;
    }
};

#endif