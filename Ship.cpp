#include "Ship.h"

#include <iostream>

#include "global.h"

int Ship::capacity_ = 0;

void Ship::input() { std::cin >> status_ >> parkid_; }

void Ship::init() { std::cin >> Ship::capacity_; }