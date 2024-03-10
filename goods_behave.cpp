#include "Goods.h"
#include "global.h"

void goods_expire(int current_frame) {  // 处理过期货物
    while (!unpickedGoods.empty() &&
           unpickedGoods.begin()->happened_frame_ + Goods::kMAX_EXPIRE >
               current_frame) {
        unpickedGoods.erase(unpickedGoods.begin());
    }
}
