#include <algorithm>
#include <climits>
#include <iostream>
#include <random>

#include "Axis.h"
#include "Frame.h"
#include "Robot.h"
#include "global.h"

// 10个机器人的行走策略以及捡起和放下货物的动作
void robots_behave(Frame& current) {
    // 预计最优方向
    std::vector<Axis> dir(kMAX_ROBOT, Axis(0, 0));
    // 实际方向
    std::vector<Axis> cur_dir(kMAX_ROBOT, Axis(0, 0));
    // 要找的货物的位置
    std::vector<Axis> maxgood_pos(kMAX_ROBOT, Axis(0, 0));

    for (int i = 0; i < kMAX_ROBOT; i++) {
        auto t = current.robot[i].get_dir();
        dir[i] = t.first;
        maxgood_pos[i] = t.second;
    }
    int dx[5] = {-1, 0, 0, 1, 0}, dy[5] = {0, -1, 1, 0, 0};
    for (int i = 0; i < kMAX_ROBOT; i++) {
        // 他的位置是否被占领
        bool isbe_jump = 0;
        for (int j = 0; j < i; j++) {
            // 别人跳到他的位置则他只能选择跳走
            if (current.robot[i].pos_ == current.robot[j].pos_ + cur_dir[i]) {
                isbe_jump = 1;
            }
        }
        // 如果他的位置被别人占领，则他随机一个方向走
        int ran_num = random();
        if (isbe_jump) {
            cur_dir[i] = Axis(dx[ran_num] % 4, dy[ran_num] % 4);
            continue;
        }

        // 没有跳到别人去的地方
        bool jump_to_other = 0;
        for (int j = 0; j < i; j++) {
            if (current.robot[i].pos_ + dir[i] ==
                current.robot[j].pos_ + cur_dir[j]) {
                jump_to_other = 1;
            }
        }
        // 如果跳过去的地方没有人，则直接跳过去
        if (!jump_to_other) {
            cur_dir[i] = dir[i];
        } else  // 随机一个方向
        {
            cur_dir[i] = Axis(dx[ran_num] % 5, dy[ran_num] % 5);
        }
    }

    // 机器人的行走，如果state为0表示恢复，则不能行走
    for (int i = 0; i < kMAX_ROBOT; i++) {
        // 不能行走
        if (!current.robot[i].status_ == 0) continue;

        if (cur_dir[i] == Axis(0, 0))
            continue;
        else if (cur_dir[i] == Axis(0, 1)) {
            current.robot[i].move(Robot::RIGHT);
        } else if (cur_dir[i] == Axis(0, -1)) {
            current.robot[i].move(Robot::LEFT);
        } else if (cur_dir[i] == Axis(1, 0)) {
            current.robot[i].move(Robot::UP);
        } else {
            current.robot[i].move(Robot::DOWN);
        }

        // 运动完的位置
        int x = current.robot[i].pos_.x_, y = current.robot[i].pos_.y_;
        if (current.robot[i].object_ == 0 && maxgood_pos[i] == Axis(x, y)) {
            current.robot[i].pickUp();
        }
    }
}