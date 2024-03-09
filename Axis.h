#ifndef AXIS_H
#define AXIS_H

struct Axis {
   public:
    int x_, y_;
    void input();
    Axis(int x__ = 0, int y__ = 0) {
        x_ = x__;
        y_ = y__;
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

const Axis kUP{-1, 0}, kRIGHT{0, 1}, kDOWN{1, 0}, kLEFT{0, -1}, kKEEP{0, 0};

#endif