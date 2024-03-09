#ifndef ROBOT_H
#define ROBOT_H

#include "Axis.h"

class Robot {
   private:
    int object_;
    Axis pos_;
    bool status_;

    public:
    void input();
};

#endif