#include <algorithm>
#include <climits>
#include <iostream>

#include "Frame.h"
#include "Robot.h"
#include "global.h"
// 机器人选择物品与泊位的估值函数
double getw(Robot& robot, Goods& goods, Park& park) {
    int val = goods.value_;
    int dis = getdis(robot.pos_, goods.pos_) + getdis(goods.pos_, park.pos_);
    if (dis == 0) return INT_MAX / 2;
    return val / (double)dis;
}
// 返回十个机器人的行动方向返回长度为10的{dx,dy}数组dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};
std::vector<Axis> get_robot_behave(Frame& current) {
    // 第i个机器人
    std::vector<Axis> dir(kMAX_ROBOT, Axis(0, 0));
    for (int i = 0; i < kMAX_ROBOT; i++) {  // 10
        Robot& robot = current.robot[i];
        // 如果robot已经扛着物品，则直接找最近的泊位
        if (robot.object_ == 1) {
            int id = 0;
            for (int j = 0; j < kMAX_PARK; j++) {  // 10
                if (robot.get_dis(j) < robot.get_dis(id)) id = j;
            }
            auto path=robot.get_path(id);
            //如果无路可走则原地不动
            if (path.size() == 0) dir[i] = {0, 0};
            else { 
                int dx = path[1].x_ - path[0].x_, dy = path[1].y_ - path[0].y_;
                dir[i] = {dx, dy};
            }
        } else {  // 没有扛着物品则先枚举物品再找最近的泊位
            double maxw = 0;
            Goods select_goods;
            int select_id;
            for (auto goods : allGoods) {  // 枚举货物 150 
                for (int id = 0; id < kMAX_PARK; id++) {  // 10
                    double w = getw(robot, goods, park[id]);
                    if(w>maxw){
                        maxw = w;
                
                    }
                }
            }
        }
    }

    return dir;
}