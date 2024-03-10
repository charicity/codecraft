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
        action_sequence.push("go " + ('0' + id_));
    } else {
        action_sequence.push("ship " + ('0' + id_) + ' ' + ('0' + id));
    }
}