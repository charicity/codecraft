#include "Frame.h"

#include <iostream>

bool Frame::input() {
    std::cin >> code_;
    // std::cerr << "code=" << code_ << std::endl;
    if (std::cin.eof() || std::cin.fail() || std::cin.bad()) {
        return false;
    }
    std::cin >> currentMoney_ >> newGoodsCount_;
    // std::cerr << "currentMoney_=" << currentMoney_
    //           << " newGoodsCount_=" << newGoodsCount_ << std::endl;
    for (int i = 0; i < newGoodsCount_; ++i) {
        Goods tmp;
        tmp.input();
        goodInfo.push_back(tmp);
        // std::cerr << "Good #" << i << ": pos=(" << tmp.pos_.x_ << ","
        //           << tmp.pos_.y_ << "), val=" << tmp.value_ << std::endl;
    }

    // std::cerr << "ER" << std::endl;
    // std::string sample;
    // std::cin >> sample;
    // std::cerr << "Sample=" << sample << std::endl;
    // std::cerr << "State=" << std::cin.eof() << " " << std::cin.fail()
    //           << std::endl;

    // do {
    //     std::cin >> sample;
    //     std::cerr << "Sample=" << sample << std::endl;

    //     std::cerr << std::cin.eof() << " " << std::cin.fail() << std::endl;
    // } while (sample == "OK");

    for (int i = 0; i < kMAX_ROBOT; ++i) {
        robot[i].input();
        // std::cerr << "Bot #" << i << ": (" << robot[i].pos_.x_ << ","
        //           << robot[i].pos_.y_ << ") state=" << robot[i].status_
        //           << " iscarrying=" << robot[i].object_ << std::endl;
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

    for (int i = 0; i < kMAX_ROBOT; ++i) {
        // std::cerr << "Ship #" << i << " state=" << ship[i].status_
        //           << " parkid=" << ship[i].parkid_ << std::endl;
    }

    return true;
}