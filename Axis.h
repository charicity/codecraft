#ifndef AXIS_H
#define AXIS_H
#include <climits>
class Axis {
   public:
    int x_, y_;
    void input();
    Axis() {
        x_ = 0;
        y_ = 0;
    }
    Axis(int x, int y) {
        x_ = x;
        y_ = y;
    }
    Axis operator+(Axis offset) const {
        Axis res(x_ + offset.x_, y_ + offset.y_);
        return res;
    }
    Axis operator-(Axis offset) const {
        Axis res(x_ - offset.x_, y_ - offset.y_);
        return res;
    }
    bool operator==(Axis offset) const {
        return x_ == offset.x_ && y_ == offset.y_;
    }
    bool operator!=(Axis offset) const {
        return x_ != offset.x_ || y_ != offset.y_;
    }
};

int get_distance(Axis a,Axis b){
    return abs(a.x_ - b.x_) + abs(a.y_ - b.y_);
}

#endif