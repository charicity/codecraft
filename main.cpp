#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>

#include "Frame.h"
#include "Goods.h"
#include "Grid.h"
#include "Step.h"
#include "global.h"

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    ControlLogic step;
    step.init_input();
    step.init_initialize();

    while (true) {
        Frame current;
        if (step.frame_input(current) == false) {
            break;
        }
        step.frame_process(current);
        step.frame_output(current);
    }
    std::cerr << "Ship:" << std::endl;
    for (int i = 0; i < kMAX_SHIP; ++i) {
        std::cerr << ship_info[i].last_ << " ";
    }
    std::cerr << std::endl;

    std::cerr << "Park:" << std::endl;
    for (int i = 0; i < kMAX_PARK; ++i) {
        std::cerr << park[i].is_ban << " ";
    }
    std::cerr << std::endl;

    std::cerr << "[tot_picked, final_score]=[" << cnt_good << "," << final_score
              << "]" << std::endl;
}