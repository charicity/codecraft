#include "Goods.h"

std::set<Goods> allGoods;

#include <iostream>

void Goods::input() {
    pos_.input();
    std::cin >> value_;
}