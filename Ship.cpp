#include "Ship.h"

#include <iostream>

void Ship::input() { std::cin >> status_ >> parkid_ }

void Ship::init() { std::cin >> capacity_; }