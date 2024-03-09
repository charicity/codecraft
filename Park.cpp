#include "Park.h"

#include <iostream>

#include "Axis.h"

void Park::init() {
    Axis tmp;
    pos_.input();
    std::cin >> time_ >> velocity_;
}