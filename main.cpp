#include <bits/stdc++.h>

#include "Frame.h"
#include "Goods.h"
#include "Grid.h"
#include "Step.h"
#include "global.h"

int main() {
    // std::ios::sync_with_stdio(0);
    // std::cin.tie(0);
    // std::cout.tie(0);

    ControlLogic step;
    step.init_input();
    step.init_initialize();
    Frame current;

    while (true) {
        if (step.frame_input(current) == false) {
            return 0;
        }
        step.frame_process(current);
        step.frame_output(current);
    }
}