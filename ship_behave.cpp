#include <cassert>

#include "Axis.h"
#include "Frame.h"
#include "Park.h"
#include "Robot.h"
#include "global.h"

// 船在curid排队时时选择id号泊位的估值函数[500为船移动的代价]，选择价值大那个。估值函数为：
double get_ship_go_w(Ship& ship, int id, int curid, Frame& current) {
    int cnt = park[id].goods_queue_.size();
    // 如果不选择移动
    if (id == curid) return cnt * 50;
    int sum = 0;
    for (int i = 0; i < kMAX_SHIP; i++) {
        if (ship.parkid_ == id) sum -= 1000;
    }
    sum += cnt * 20;
    return sum;
    // 移动到其他位置有500的时间
    // return park.goods_queue_.size()+
    // / park.ships_queue_.size() - ();
}
// 船在虚拟点时准备去那个泊位的估值函数，估值函数：泊位的物品价值
double get_ship_back_w(Ship& ship, int id, Frame& current) {
    auto que = park[id].goods_queue_;
    int sum = que.size();
    // 每有一艘船在这里就减200
    for (int i = 0; i < kMAX_SHIP; i++) {
        if (current.ship[i].parkid_ == id) sum -= 200;
    }
    // sum -= park[id].time_;
    return sum;
}
void ships_behave(Frame& current) {
    if (current.code_ <= 1) {
        for (int i = 0; i < kMAX_SHIP; ++i) {
            current.ship[i].go(i, current);
        }
        return;
    }
    // 维护last_
    for (int i = 0; i < kMAX_SHIP; i++) {
        auto& ship = current.ship[i];
        auto& info = ship_info[ship.id_];

        if (ship.status_ == 1 || ship.status_ == 2) {
            if (info.last_ != ship.parkid_) {
                std::cerr << "ship " << i << " reaches " << ship.parkid_
                          << " at frame" << current.code_ << std::endl;
            }
            info.last_ = ship.parkid_;
        }
        ship.last_ = info.last_;
        ship.done_ = info.done_;
    }
    // 其他的
    for (int i = 0; i < kMAX_SHIP; i++) {
        auto& ship = current.ship[i];
        auto& info = ship_info[ship.id_];

        // 逃生处理
        if (ship.done_ == 0) {
            if (ship.last_ != -1 &&
                15000 - current.code_ - 5 <= park[ship.last_].min_time_) {
                // 需要逃生
                if (park[ship.last_].min_time_ == park[ship.last_].time_) {
                    // 直接逃生
                    std::cerr << "Ship " << i << " escape to " << -1
                              << " at frame " << current.code_ << std::endl;
                    ship.go(-1, current);
                    info.done_ = 2;
                } else {
                    // 中转站逃生
                    if (ship.last_ != -1 && ship.status_ != 0) {
                        std::cerr << "Ship" << i << " escape to min-"
                                  << Park::min_id << " at frame "
                                  << current.code_ << std::endl;
                        ship.go(Park::min_id, current);
                        info.done_ = 1;
                    }
                }
                continue;
            }
        }

        if (ship.done_ == 1) {
            if (ship.parkid_ == Park::min_id &&
                (ship.status_ == 1 || ship.status_ == 2)) {
                ship.go(-1, current);
                info.done_ = 2;
            }
            continue;
        }

        if (ship.done_ == 2) {
            if (ship.status_ == 1 || ship.status_ == 2) {
                std::cerr << "Ship " << i << " finished escaping" << std::endl;
                info.done_ = 3;
            } else
                continue;
        }

        // 如果船在移动则不用管

        if (ship.status_ == 0) {
            continue;
        }
        // 先决定要不要go
        if (ship.status_ == 1) {       // 船在泊位或者虚拟点
            if (ship.parkid_ == -1) {  // 虚拟点
                double maxw = 0, id = 0;
                for (int i = 0; i < kMAX_PARK; i++) {
                    if (park[i].have_ship()) continue;
                    // if (park[i].is_ban) continue;
                    double w = get_ship_back_w(ship, i, current);
                    if (w > maxw) {
                        maxw = w;
                        id = i;
                    }
                }
                ship.go(id, current);
            }
            // 装满了或者装了超过15个直接出发去虚拟点,或者剩下的时间-需要的时间，榨干价值
            // 泊位没货物了也走
            else if (!ship.remain_capacity_ ||
                     ship.capacity_ - ship.remain_capacity_ >= 2000 ||
                     (15000 - current.code_ - park[ship.parkid_].time_ <= 10 &&
                      15000 - current.code_ - park[ship.parkid_].time_ >= 1)) {
                int id = -1;  // 去虚拟点
                for (int i = 0; i < kMAX_PARK; i++) {
                    if (park[i].time_ + 500 <
                        park[ship.parkid_].time_) {  // 先去别的泊位再去虚拟点
                        id = i;
                    }
                }
                ship.go(id, current);
            } else if (park[ship.parkid_].goods_queue_.size() ==
                       0) {  // 没货物则去别的地方
                int id = 0;
                for (int i = 0; i < kMAX_PARK; i++) {
                    if (park[i].have_ship()) continue;
                    if (get_ship_go_w(ship, i, ship.parkid_, current) >
                        get_ship_go_w(ship, id, ship.parkid_, current)) {
                        id = i;
                    }
                }
                if (id != ship.parkid_) ship.go(id, current);
            } else {  // 有货物则直接装
                // std::cerr << "Loading" << std::endl;
                park[ship.parkid_].load(ship);
            }

        } else {  // 船在排队
            if (15000 - current.code_ - park[ship.parkid_].time_ <= 10 &&
                15000 - current.code_ - park[ship.parkid_].time_ >= 1) {
                ship.go(-1, current);
                continue;
            }
            // 决定去哪个泊位
            double maxw = 0, id = 0;
            for (int i = 0; i < kMAX_PARK; i++) {
                if (park[i].have_ship()) continue;
                double w = get_ship_go_w(ship, i, ship.parkid_, current);
                if (w > maxw) {
                    maxw = w;
                    id = i;
                }
            }
            // 最终去id号泊位
            if (id != ship.parkid_) {
                ship.go(id, current);
            }
        }
    }
}
