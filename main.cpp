#include <bits/stdc++.h>

#include "Frame.h"
#include "Grid.h"
#include "Step.h"

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
        step.frame_output();
    }
}