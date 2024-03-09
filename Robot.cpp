#include "Robot.h"

#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#include "Grid.h"

void Robot::input() {
    std::cin >> object_;
    pos_.input();
    std::cin >> status_;
}