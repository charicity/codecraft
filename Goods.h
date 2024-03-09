#ifndef GOODS_H
#define GOODS_H
#include <set>

#include "Axis.h"

class Goods {
 public:
  Axis pos_{0, 0};
  int value_{0};

  void input();
};

std::set<Goods> allGoods;

#endif