#ifndef FRAME_H
#define FRAME_H

#include <vector>

#include "Axis.h"
#include "Goods.h"
#include "Grid.h"
#include "Robot.h"
#include "Ship.h"

class Frame {
   public:
    int code_;           // 当前帧的代号
    int currentMoney_;   // 目前持有的金钱
    int newGoodsCount_;  // 新货物的数量
    std::vector<Goods> goodInfo;

    Ship ship[kMAX_SHIP];
    Robot robot[kMAX_ROBOT];

    void input();
};
#endif