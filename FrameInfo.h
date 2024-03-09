#ifndef FRAMEINFO_H
#define FRAMEINFO_H

#include <vector>

#include "Axis.h"
#include "Goods.h"

class FrameInfo {
   private:
    int FrameCode_, CurrentMoney_{0};
    int NewGoodsCount_;
    std::vector<Goods> GoodPos_;
};
#endif