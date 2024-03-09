#ifndef STEP_H
#define STEP_H
#include <cassert>

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

        // for (int i = 0; i < kMAX_GRID; ++i) {
        //     for (int j = 0; j < kMAX_GRID; ++j) {
        //         std::cerr << grid[i][j].state_;
        //     }
        //     std::cerr << std::endl;
        // }

        // std::cerr << "Parks: " << std::endl;
        for (int i = 0; i < kMAX_PARK; ++i) {
            int id;
            std::cin >> id;
            // std::cerr << "id - " << id << std::endl;
            park[id].init();
        }

        // std::cerr << "Ships: " << std::endl;
        Ship::init();

        std::string s;
        std::cin >> s;

        // std::cerr << "[EXPECTED OK]: " << s << std::endl;
    }

    // 初始化处理
    void init_initialize() {
        // std::cerr << "[PRINTED OK] " << std::endl;
        ;
        std::cout << "OK" << std::endl;
        std::cout.flush();
    }

    // 输入一帧
    bool frame_input(Frame &current) {
        // std::cerr << "getting a frame:" << std::endl;
        bool f = current.input();
        // std::cerr << "f=" << f << std::endl;
        if (f == false) return false;
        std::string s;
        std::cin >> s;
        // std::cerr << "[EXPECTED OK]: " << s << std::endl;
        return true;
    }

    // 对那一帧进行操作
    void frame_output() {
        // std::cout << "ship 0 0" << std::endl;
        std::cout << "OK" << std::endl;
        std::cout.flush();
    }
};
#endif