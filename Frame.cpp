#include "Frame.h"

#include <iostream>

bool Frame::input() {
    std::cin >> code_;
    if (std::cin.eof()) {
        return false;
    }
    std::cin >> currentMoney_ >> newGoodsCount_;
    for (int i = 0; i < newGoodsCount_; ++i) {
        Goods tmp;
        tmp.input();
        goodInfo.push_back(tmp);
    }

    for (int i = 0; i < kMAX_ROBOT; ++i) {
        robot[i].input();
    }

    for (int i = 0; i < kMAX_SHIP; ++i) {
        ship[i].input();
    }

    return true;
}