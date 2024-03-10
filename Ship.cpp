#include "Ship.h"

#include <iostream>

#include "global.h"

int Ship::capacity_ = 0;

void Ship::input() { std::cin >> status_ >> parkid_; }

void Ship::init() {
    std::cin >> Ship::capacity_;
    // std::cerr << "Capacity: " << capacity_ << std::endl;
}

//船装载货物
void Ship::load(){
    if (status_ == 0 || status_ == 2) return;
}

//船去哪里
int Ship::go(){
}