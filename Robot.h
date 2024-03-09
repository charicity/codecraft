#ifndef ROBOT_H
#define ROBOT_H

#include "Axis.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
class Robot {
    public:

    bool object_;
    Axis pos_;
    bool status_;

    void input();
    std::vector<Axis> get_path(Axis);
};

#endif