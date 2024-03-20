#include "Ship.h"

#include <iostream>

#include "Park.h"
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
    int now_id = parkid_;
    ship_info[id_].to_ = id;

    if (id == parkid_) {
        if (id != -1) {
            // std::cerr << "[IGNORED] Ship " << id_ << " from " << now_id
            //           << " left for " << id << " at frame " << current.code_
            //           << std::endl;
        }
        // 如果目的地和之前的一样，则无视这个指令
        return;
    }

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

    // std::cerr << "Ship " << id_ << " from " << now_id << " left for " << id
    //           << " at frame " << current.code_ << std::endl;
    // std::cerr << "Status: " << park[now_id].tend_ship.size() << "&&"
    //           << 1010 + park[now_id].time_ << "&&" << Park::tot_ban
    //           << std::endl;
    // if (now_id != -1 && park[now_id].tend_ship.size() == 0 &&
    //     std::min(park[now_id].min_time_, 500) + park[now_id].min_time_ + 1 >=
    //         15000 - current.code_ &&
    //     Park::tot_ban < 5) {
    //     // std::cerr << "at frame " << current.code_ << " banned park " <<
    //     // now_id
    //     //           << std::endl;
    //     park[now_id].is_ban = true;
    //     ++Park::tot_ban;
    // }
}