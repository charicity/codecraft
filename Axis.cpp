#include "Axis.h"

#include <iostream>
void Axis::input() {
    std::cin >> x_ >> y_;
    // std::cerr << x_ << " " << y_ << " ";
}

int get_distance(Axis a, Axis b) {
    return std::abs(a.x_ - b.x_) + std::abs(a.y_ - b.y_);
}