#include "Frame.h"

#include <iostream>

bool Frame::input() {
    std::cin >> code_;
    if (std::cin.eof() || std::cin.fail() || std::cin.bad()) {
        return false;
    }
    std::cin >> currentMoney_ >> newGoodsCount_;
    for (int i = 0; i < newGoodsCount_; ++i) {
        Goods tmp;
        tmp.input(code_);
        goodInfo.push_back(tmp);
    }

    for (int i = 0; i < kMAX_ROBOT; ++i) {
        robot[i].input();
    }

    for (int i = 0; i < kMAX_SHIP; ++i) {
        ship[i].input();
    }
    if (code_ == 1) {
        for (int i = 0; i < kMAX_SHIP; ++i) {
            ship[i].parkid_ = -1;
            ship[i].status_ = 1;
        }
    }

    return true;
}