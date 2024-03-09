#ifndef AXIS_H
#define AXIS_H

struct Axis {
    int x_, y_;
    void input();
    Axis(int x__, int y__) {
        x_ = x__;
        y_ = y__;
    }
    Axis operator+(Axis offset) const {
        Axis res(x_ + offset.x_, y_ + offset.y_);
        return res;
    }
};

#endif