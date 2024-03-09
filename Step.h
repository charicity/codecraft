#ifndef STEP_H
#define STEP_H
#include "Frame.h"
#include "Grid.h"
#include "Park.h"
#include "Ship.h"
#include "global.h"
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

        std::string s;
        std::cin >> s;
        std::cerr << "OK VS " << s << std::endl;
    }

    // 初始化处理
    void init_initialize() {
        ;
        std::cout << "OK" << std::endl;
        std::cout.flush();
    }

    // 输入一帧
    bool frame_input(Frame &current) {
        bool f = current.input();
        if (f == false) return false;
        std::string s;
        std::cin >> s;
        std::cerr << "OK VS " << s << std::endl;
        return true;
    }

    // 对那一帧进行操作
    void frame_output() {
        for (int i = 0; i < 4; ++i) {
            std::cout << "ship 0 0" << std::endl;
        }
        std::cout << "OK" << std::endl;
        std::cout.flush();
    }
};
#endif