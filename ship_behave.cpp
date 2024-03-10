#include "Axis.h"
#include "Frame.h"
#include "Park.h"
#include "Robot.h"
#include "global.h"
// 船在等待时选择id号泊位的估值函数，估值函数为：货物数量*time/等待船数量 -
double get_ship_go_w(Ship& ship, int id) {
    int cnt = park[id].goods_queue_.size();
    return cnt * 1000;
    // return park.goods_queue_.size()+
    // / park.ships_queue_.size() - ();
}
double get_ship_back_w(Ship& ship, int id) {
    int cnt = park[id].goods_queue_.size();
    return cnt * 1000;
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
            // 装满了或者装了超过100个直接出发去虚拟点
            else if (!ship.remain_capacity_ ||
                     ship.capacity_ - ship.remain_capacity_ >= 2) {
                ship.go(-1);
            } else {
                // std::cerr << "Loading" << std::endl;
                park[ship.parkid_].load(ship);
            }

        } else {  // 船在排队
            // 决定去哪个泊位
            double maxw = 0, id = 0;
            for (int i = 0; i < kMAX_PARK; i++) {
                double w = get_ship_go_w(ship, i);
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
