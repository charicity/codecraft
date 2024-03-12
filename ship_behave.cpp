#include "Axis.h"
#include "Frame.h"
#include "Park.h"
#include "Robot.h"
#include "global.h"
// 船在curid排队时时选择id号泊位的估值函数[500为船移动的代价]，选择价值大那个。估值函数为：
double get_ship_go_w(Ship& ship, int id, int curid) {
    int cnt = park[id].goods_queue_.size();
    // 如果不选择移动
    if (id == curid) return cnt * 100;
    // 移动到其他位置有500的时间
    return cnt * 10 - 500;
    // return park.goods_queue_.size()+
    // / park.ships_queue_.size() - ();
}
// 船在虚拟点时准备去那个泊位的估值函数，估值函数：泊位的物品价值
double get_ship_back_w(Ship& ship, int id) {
    auto que = park[id].goods_queue_;
    int sum = 0;
    while (que.size()) {
        auto good = que.front();
        que.pop();
        sum += good.value_;
    }
    return sum;
}
void ships_behave(Frame& current) {
    for (int i = 0; i < kMAX_SHIP; i++) {
        // 如果船在移动则不用管
        auto& ship = current.ship[i];
        if (ship.status_ == 0) continue;

        // 先决定要不要go
        if (ship.status_ == 1) {  // 船在泊位或者虚拟点

            if (ship.parkid_ == -1) {  // 虚拟点
                double maxw = 0, id = 0;
                for (int i = 0; i < kMAX_PARK; i++) {
                    double w = get_ship_back_w(ship, i);
                    if (w > maxw) {
                        maxw = w;
                        id = i;
                    }
                }
                ship.go(id);
            }
            // 装满了或者装了超过15个直接出发去虚拟点,或者剩下的时间-需要的时间，榨干价值
            // 泊位没货物了也走
            else if (!ship.remain_capacity_ ||
                     ship.capacity_ - ship.remain_capacity_ >= 50 ||
                     15000 - current.code_ - park[ship.parkid_].time_ <= 10) {
                ship.go(-1);
            } else {
                // std::cerr << "Loading" << std::endl;
                park[ship.parkid_].load(ship);
            }

        } else {  // 船在排队
            // 决定去哪个泊位
            double maxw = 0, id = 0;
            for (int i = 0; i < kMAX_PARK; i++) {
                double w = get_ship_go_w(ship, i, ship.parkid_);
                if (w > maxw) {
                    maxw = w;
                    id = i;
                }
            }
            // 最终去id号泊位
            if (id != ship.parkid_) {
                ship.go(id);
            }
        }
    }
}
