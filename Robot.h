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
    //robot去哪个点的路径
    std::vector<Axis> get_path(Axis);
    //robot去哪拿哪个货物再去哪个
     get_which_good_and_ship();
};

#endif