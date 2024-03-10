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
    void init_input();

    // 初始化处理
    void init_initialize();

    // 输入一帧
    bool frame_input(Frame &current);

    void frame_process(Frame &current);

    // 对那一帧进行操作
    void frame_output(Frame &current);
};
#endif