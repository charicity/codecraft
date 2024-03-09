#ifndef STEP_H
#define STEP_H
#include "Frame.h"
#include "Grid.h"
#include "Park.h"
#include "Ship.h"
#include "iostream"

class ControlLogic {
   public:
    // 最开始的输入
    void init_input() {
        for (int i = 0; i < kMAX_GRID; ++i) {
            for (int j = 0; j < kMAX_GRID; ++j) {
                grid[i][j].init();
            }
        }

        for (int i = 0; i < kMAX_PARK; ++i) {
            park[i].init();
        }

        Ship::init();
    }

    // 初始化处理
    void init_initialize() {
        ;
        std::cout << "OK" << std::endl;
    }

    // 输入一帧
    void frame_input(Frame &current) {
        current.input();
        ;
    }

    // 对那一帧进行
    void frame_output() {
        ;
        std::cout << "OK" << std::endl;
    }
};
#endif