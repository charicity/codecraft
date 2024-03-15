#include "Ship.h"

#include <iostream>

#include "global.h"

int Ship::capacity_ = 0;
Ship_Keep ship_info[kMAX_SHIP];

void Ship::input(int id) {
    std::cin >> status_ >> parkid_;
    id_ = id;
    if (status_ == 1 && parkid_ == -1) {
        remain_capacity_ = Ship::capacity_;
    }
}

void Ship::init() { std::cin >> Ship::capacity_; }

void Ship::go(int id, Frame& current) {
    // if (status_ == 1 && parkid_ != -1 &&)
    int now_id = parkid_;
    if (id == -1) {
        for (int i = 0; i < kMAX_PARK; ++i) {
            park[i].tend_ship.erase(id_);
        }
        std::string s = "go ";
        s += (char)('0' + id_);
        action_sequence.push(s);
    } else {
        for (int i = 0; i < kMAX_PARK; ++i) {
            park[i].tend_ship.erase(id_);
        }
        park[id].tend_ship.insert(id_);
        std::string s = "ship ";
        s += (char)('0' + id_);
        s += (char)(' ');
        s += (char)('0' + id);
        action_sequence.push(s);
    }

    if (park[now_id].tend_ship.size() == 0 &&
        1010 + park[now_id].time_ <= 15000 - current.code_) {
        park[now_id].is_ban = true;
    }
}