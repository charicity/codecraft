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
    for (int i = 0; i < kMAX_SHIP; ++i) {
        std::cerr << ship_info[i].last_ << std::endl;
    }
    std::cerr << "cnt_good=" << cnt_good << std::endl;
    return 0;
}