#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>

#include "Frame.h"
#include "Goods.h"
#include "Grid.h"
#include "Ship.h"
#include "Step.h"
#include "global.h"

void print_debug() {
    std::cerr << "Ship:" << std::endl;
    std::cerr << "capacity:" << Ship::capacity_ << std::endl;
    for (int i = 0; i < kMAX_SHIP; ++i) {
        std::cerr << i << " stay=" << ship_info[i].last_
                  << " goto=" << ship_info[i].to_
                  << " done=" << ship_info[i].done_ << std::endl;
    }
    std::cerr << std::endl;

    std::cerr << "Park:" << std::endl;
    std::cerr << "minid=" << Park::min_id << std::endl;
    for (int i = 0; i < kMAX_PARK; ++i) {
        std::cerr << i << ":"
                  << " parktime=" << park[i].time_
                  << " mintime=" << park[i].min_time_
                  << " isban=" << park[i].is_ban
                  << " need_shortcut()=" << park[i].need_shortcut()
                  << std::endl;
    }
    std::cerr << std::endl;
    std::cerr << "[tot_picked, final_score]=[" << cnt_good << "," << final_score
              << "]" << std::endl;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    ControlLogic step;
    step.init_input();
    step.init_initialize();
    print_debug();
    while (true) {
        Frame current;
        if (step.frame_input(current) == false) {
            break;
        }
        step.frame_process(current);
        step.frame_output(current);
    }

    print_debug();
}