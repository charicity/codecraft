#include <algorithm>
#include <climits>
#include <iostream>

#include "Frame.h"
#include "Robot.h"
#include "global.h"
// 机器人选择物品与泊位的估值函数
int getdis(Axis a, Axis b) { return abs(a.x_ - b.x_) + abs(a.y_ - b.y_); }
int getw(Robot& robot, Goods& goods, Park& park) {
    // int val = goods.value_;
    // int dis1 = getdis()
}
// 返回十个机器人的行动方向返回长度为10的{dx,dy}数组dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};
std::vector<Axis> get_robot_behave(Frame& current) {
    // 第i个机器人
    std::vector<Axis> dir(kMAX_ROBOT, Axis(0, 0));
    for (int i = 0; i < kMAX_ROBOT; i++) {  // 10
        Robot& robot = current.robot[i];
        // 如果robot已经扛着物品，则直接找最近的泊位
        if (robot.object_ == 1) {
            int minlen = INT_MAX / 2;
            std::vector<Axis> path;
            for (int id = 0; id < kMAX_PARK; id++) {  // 10
                auto v = robot.get_path(id);          // n
                if (v.size() == 0) continue;
                if (v.size() < minlen) {
                    minlen = v.size();
                    path = v;
                }
            }
            int dx = path[1].x_ - path[0].x_, dy = path[1].y_ - path[0].y_;
            dir[i] = {dx, dy};
        } else {  // 没有扛着物品则先枚举物品再找最近的泊位
            for (auto good : allGoods) {
            }
        }
    }

    return dir;
}