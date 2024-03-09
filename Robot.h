#ifndef ROBOT_H
#define ROBOT_H

#include "Axis.h"

class Robot {
    public:

    bool object_;
    Axis pos_;
    bool status_;

    void input();

};

#endif