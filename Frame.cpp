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
        robot[i].input(i);
    }

    for (int i = 0; i < kMAX_SHIP; ++i) {
        ship[i].input(i);
    }

    // 题目说的，特判第一帧
    if (code_ == 1) {
        for (int i = 0; i < kMAX_SHIP; ++i) {
            ship[i].parkid_ = -1;
            ship[i].status_ = 1;
            ship[i].remain_capacity_ = Ship::capacity_;
        }
    }

    // for (int i = 0; i < kMAX_SHIP; ++i) {
    //     std::cerr << "parkid=" << ship[i].parkid_
    //               << "| status=" << ship[i].status_ << std::endl;
    //     ;
    // }

    return true;
}