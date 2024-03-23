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
    if (park[id].have_ship()) return -100000;
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
    if (park[id].have_ship()) return -100000;
    return sum;
}
void ships_behave(Frame& current) {
    bool is_special_frame = false;  // 在特判的第一帧
    if (current.code_ <= 1) {
        for (int i = 0; i < kMAX_SHIP; ++i) {
            current.ship[i].go(i, current);
        }
        is_special_frame = true;
    }

    if (current.code_ == 15000 - 500 - 2 - 2 * Park::max_back) {
        // 特判半空帧
        for (int i = 0; i < kMAX_SHIP; ++i) {
            if (ship_info[i].last_ != -1) current.ship[i].go(-1, current);
        }
        is_special_frame = true;
    }

    // if (current.code_ == 15000 - 10 - 2 * Park::max_back) {
    //     // 特判半空帧
    //     for (int i = 0; i < kMAX_SHIP; ++i) {
    //         if (ship_info[i].last_ != -1) current.ship[i].go(-1, current);
    //     }
    //     is_special_frame = true;
    // }

    // if (current.code_ == 15000 - Park::max_back - 8) {
    //     // 特判半空帧
    //     for (int i = 0; i < kMAX_SHIP; ++i) {
    //         if (ship_info[i].last_ != -1) current.ship[i].go(-1, current);
    //     }
    //     is_special_frame = true;
    // }
    // 维护ship_info -> 读取
    for (int i = 0; i < kMAX_SHIP; i++) {
        auto& ship = current.ship[i];
        auto& info = ship_info[ship.id_];

        if (ship.status_ == Ship::arrived || ship.status_ == Ship::waiting) {
            if (info.last_ != ship.parkid_) {
                if (ship.parkid_ == -1) {
                    // 到了虚拟点，解除强制返回限制
                    ship.returning_ = false;
                }
                std::cerr << "Ship " << i << " reaches " << ship.parkid_
                          << " at frame" << current.code_ << std::endl;
                if (info.done_ == 1) info.done_ = 2;
            }
            info.last_ = ship.parkid_;
        }
        ship.last_ = info.last_;
        ship.done_ = info.done_;
        ship.to_ = info.to_;
    }
    if (is_special_frame) return;
    // 其他的
    for (int i = 0; i < kMAX_SHIP; i++) {
        auto& ship = current.ship[i];
        auto& info = ship_info[ship.id_];

        // 下一个优化点：完全不需要逃生，只需要在arrive和waiting状态判断是否需要离开即可
        //  逃生处理
        if (ship.done_ == 0) {
            if (ship.last_ != -1 &&
                15000 - current.code_ <= park[ship.last_].min_time_ + 2) {
                // 需要逃生
                ship.returning_ = true;
                if (park[ship.last_].min_time_ == park[ship.last_].time_) {
                    // 直接逃生
                    // std::cerr << "Ship " << i << " escape to " << -1
                    //           << " at frame " << current.code_
                    //           << " when it was in " << ship.parkid_
                    //           << std::endl;
                    ship.go(-1, current);
                    info.done_ = 1;
                } else {
                    // 中转站逃生
                    if (ship.last_ != -1 && ship.status_ != Ship::moving) {
                        // std::cerr << "Ship" << i << " escape to min1-"
                        //           << Park::min_id << " at frame "
                        //           << current.code_ << std::endl;
                        ship.go(Park::min_id, current);
                        info.done_ = 1;
                    }
                }
                continue;
            }
        }
        // 如果船在移动则不用管

        if (ship.status_ == Ship::moving) {
            continue;
        }
        if (ship.returning_ == true) {
            // 有这个状态且到岸，一定是在中转点，直接回去就行
            ship.go(-1, current);
        }

        // 先决定要不要go
        if (ship.status_ == Ship::arrived) {  // 船在泊位或者虚拟点
            if (ship.parkid_ == -1) {         // 虚拟点
                double maxw = 0,
                       id = -1;  // id默认得是-1，走不了就留下来呗~
                for (int i = 0; i < kMAX_PARK; i++) {
                    if (park[i].have_ship()) continue;
                    if (park[i].canback_from_virtual(current) ==
                        Park::impossible)
                        continue;  // 从虚拟点

                    double w = get_ship_back_w(ship, i, current);
                    if (w > maxw) {
                        maxw = w;
                        id = park[i].canback_from_virtual(current);
                    }
                }
                if (id != -1) ship.go(id, current);
            }
            // 装满了或者装了超过INF个直接出发去虚拟点，逃生已经单独处理
            // 泊位没货物了也走
            else if (!ship.remain_capacity_ ||
                     ship.capacity_ - ship.remain_capacity_ >=
                         2000) {  // 在泊位
                // std::cerr << "FILLED";
                assert(ship.parkid_ != -1);
                if (park[ship.parkid_].can_return(current)) {
                    // 如果还回得来，则走
                    ship.returning_ = true;
                    if (ship.parkid_ != Park::min_id &&
                        park[ship.parkid_].need_shortcut()) {
                        ship.go(Park::min_id, current);
                    } else {
                        ship.go(-1, current);
                    }
                }
                // 否则也得走，如果是超过20个的话就把这里注释掉

                ship.returning_ = true;
                if (ship.parkid_ != Park::min_id &&
                    park[ship.parkid_].need_shortcut()) {
                    ship.go(Park::min_id, current);
                } else {
                    ship.go(-1, current);
                }

            } else {
                assert(ship.parkid_ != -1);
                if (park[ship.parkid_].goods_queue_.size() ==
                    0) {  // 没货物则去别的地方
                    int id = ship.parkid_;
                    for (int i = 0; i < kMAX_PARK; i++) {
                        if (park[i].have_ship()) continue;
                        if (i == ship.parkid_) continue;
                        if (park[i].canback_from_other(current) ==
                            Park::impossible)
                            continue;
                        if (get_ship_go_w(ship, i, ship.parkid_, current) >
                            get_ship_go_w(ship, id, ship.parkid_, current)) {
                            id = i;
                        }
                    }
                    if (id != ship.parkid_) {
                        ship.go(id, current);
                    }
                } else {  // 有货物则直接装
                    // std::cerr << "Loading" << std::endl;
                    assert(ship.parkid_ != -1);
                    park[ship.parkid_].load(ship);
                }
            }
        } else {  // 船在排队
            // 决定去哪个泊位
            double maxw = 0, id = -1;
            for (int i = 0; i < kMAX_PARK; i++) {
                if (park[i].have_ship()) continue;
                if (park[i].canback_from_other(current) == Park::impossible)
                    continue;
                double w = get_ship_go_w(ship, i, ship.parkid_, current);
                if (w > maxw) {
                    maxw = w;
                    id = park[i].canback_from_other(current);
                }
            }
            // 最终去id号泊位
            if (id != ship.parkid_) {
                if (id == -1) {
                    assert(ship.parkid_ != -1);
                    if (park[ship.parkid_].can_return(current)) {
                        ship.returning_ = true;
                        if (ship.parkid_ != Park::min_id &&
                            park[ship.parkid_].need_shortcut()) {
                            ship.go(Park::min_id, current);
                        } else {
                            ship.go(-1, current);
                        }
                    }
                } else {
                    ship.go(id, current);
                }
            }
        }
    }
}
