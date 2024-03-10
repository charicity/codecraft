#include "Ship.h"

#include <iostream>

#include "global.h"

int Ship::capacity_ = 0;

void Ship::input(int id) {
    std::cin >> status_ >> parkid_;
    id_ = id;
    if (status_ == 1 && parkid_ == -1) {
        remain_capacity_ = Ship::capacity_;
    }
}

void Ship::init() { std::cin >> Ship::capacity_; }

void Ship::go(int id) {
    if (id == -1) {
        std::string s = "go ";
        s += (char)('0' + id_);
        action_sequence.push(s);
    } else {
        std::string s = "ship ";
        s += (char)('0' + id_);
        s += (char)(' ');
        s += (char)('0' + id);
        action_sequence.push(s);
    }
}