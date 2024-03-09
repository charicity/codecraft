#ifndef GOODS_H
#define GOODS_H

#include "Axis.h"
class Goods {
   private:
    Axis pos_{0, 0};
    int value_{0};

   public:
    void input();
};
#endif