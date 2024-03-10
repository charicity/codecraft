#include "Goods.h"
#include "global.h"

void goods_expire(int current_frame) {  // 处理过期货物
    // return;
    // std::cerr << "goods_expire(): before=" << unpickedGoods.size() << " | ";
    while (!unpickedGoods.empty() &&
           unpickedGoods.begin()->happened_frame_ + Goods::kMAX_EXPIRE <
               current_frame) {
        unpickedGoods.erase(unpickedGoods.begin());
    }
    // std::cerr << "after=" << unpickedGoods.size() << std::endl;
}
