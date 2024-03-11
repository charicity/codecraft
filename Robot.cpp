#include "Robot.h"

#include <assert.h>

#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <utility>
#include <vector>

#include "Axis.h"
#include "Frame.h"
#include "Grid.h"
#include "Park.h"
#include "global.h"

// 捡起当前位置的货物
void Robot::pickUp() {
    if (grid[pos_.x_][pos_.y_].haveGood == false) {
        std::cerr << "in Robot::pickUp() -> there is no Goods!" << std::endl;
        return;
    }

    Goods tobePicked = grid[pos_.x_][pos_.y_].goodHere;
    grid[pos_.x_][pos_.y_].remove();

    carrying = tobePicked;
    std::string s = "get ";
    s += (char)('0' + id_);
    action_sequence.push(s);
    unpickedGoods.erase(tobePicked);
}

void Robot::move(int state) {
    switch (state) {
        case Robot::LEFT: {
            pos_.y_--;
            break;
        }
        case Robot::RIGHT: {
            pos_.y_++;
            break;
        }
        case Robot::UP: {
            pos_.x_--;
            break;
        }
        case Robot::DOWN: {
            pos_.x_++;
            break;
        }
        default: {
            std::cerr << "in Robot::move() -> error moving code" << std::endl;
            return;
        }
    }
    std::string s = "move ";
    s += ('0' + id_);
    s += ' ';
    s += ('0' + state);

    action_sequence.push(s);
}

void Robot::placeDown() {
    if (!object_) {
        std::cerr << "in Robot::placeDown() -> Not carrying goods!"
                  << std::endl;
        return;
    }
    for (int i = 0; i < kMAX_PARK; ++i) {
        if (park[i].inPark(pos_)) {
            carrying.pos_ = pos_;  // 用作debug
            park[i].put(carrying);
            object_ = 0;

            std::string s1 = "pull ";
            s1 += (char)('0' + id_);
            action_sequence.push(s1);
            return;
        }
    }
    std::cerr << "in Robot::placeDown() -> there is no Park!" << std::endl;
}

void Robot::input(int id) {
    std::cin >> object_;
    pos_.input();
    id_ = id;
    std::cin >> status_;
}

// // 得到从机器人到park[id]的最短路径
// std::vector<Axis> Robot::get_path(int id) {
//     int curx = pos_.x_, cury = pos_.y_;
//     std::vector<Axis> path;
//     if (park[id].dis[curx][cury] == INT_MAX / 2) {
//         return path;
//     }
//     // std::cerr << "HH" << std::endl;
//     int x = pos_.x_, y = pos_.y_;
//     path.push_back({x, y});
//     while (park[id].pre[x][y] != Axis(-1, -1)) {
//         int tmpx = park[id].pre[x][y].x_;
//         int tmpy = park[id].pre[x][y].y_;
//         x = tmpx;
//         y = tmpy;
//         path.push_back({x, y});
//     }
//     // std::cerr << path.size() << " " << std::endl;
//     return path;
// }

// dis1为从机器人到货物的最短距离，dis2为从货物到泊位的最短距离 ,权值计算函数
double getw(int dis1, int dis2, int val) { return (double)val / (dis1 + dis2); }

// 得到机器人到park[id]的最短路径的长度
int Robot::get_dis(int id) { return park[id].dis[pos_.x_][pos_.y_]; }

// 机器人有了货物后要去到的泊位的估值函数:当前港口的货物数量*10/到他的距离，大的优先去
double Robot::get_toship_w(int id,
                           std::vector<std::vector<int>>& dis) {  //
    int dis_to_ship = dis[park[id].pos_.x_][park[id].pos_.y_];
    int park_good = park[id].goods_queue_.size();
    return (double)park_good / dis_to_ship;
}
// robot到哪里取货,以及要的货物的位置
std::pair<Axis, Axis> Robot::get_dir(std::set<Goods>& unpickedGoods,
                                     Frame& current) {
    // 求出bfs矩阵
    std::vector<std::vector<int>> dis(kMAX_GRID,
                                      std::vector<int>(kMAX_GRID, INT_MAX / 2));
    std::vector<std::vector<Axis>> pre(
        kMAX_GRID, std::vector<Axis>(kMAX_GRID, Axis(0, 0)));
    int x = pos_.x_, y = pos_.y_;
    dis[x][y] = 0;
    std::queue<Axis> q;
    q.push(pos_);
    std::vector<Axis> dir;
    dir.push_back({-1, 0});
    dir.push_back({0, -1});
    dir.push_back({0, 1});
    dir.push_back({1, 0});
    // std::random_device rd;
    // std::mt19937 g(rd());
    // 随机bfs
    while (q.size()) {
        Axis u = q.front();
        q.pop();
        std::random_shuffle(dir.begin(), dir.end());
        int dx[4], dy[4];
        for (int i = 0; i < 4; i++) {
            dx[i] = dir[i].x_;
            dy[i] = dir[i].y_;
        }
        for (int i = 0; i < 4; i++) {
            int x = u.x_ + dx[i], y = u.y_ + dy[i];
            if (x < 0 || y < 0 || x >= kMAX_GRID || y >= kMAX_GRID) continue;
            if (grid[x][y].state_ == Grid::barrier ||
                grid[x][y].state_ == Grid::ocean)
                continue;
            if (dis[x][y] != INT_MAX / 2) continue;
            q.push({x, y});
            dis[x][y] = dis[u.x_][u.y_] + 1;
            pre[x][y] = {u.x_, u.y_};
        }
    }

    // 机器人扛着物品,影响他的运输的有泊位货物个数以及dis，向货物个数/dis最大的那个走
    if (object_ == 1) {
        int id = 0;
        for (int j = 1; j < kMAX_PARK; j++) {  // 10
            if (get_toship_w(j, dis) > get_toship_w(id, dis)) id = j;
        }
        if (dis[park[id].pos_.x_][park[id].pos_.y_] == INT_MAX / 2)
            return {{0, 0}, {0, 0}};
        // 如果距离该泊位在kval帧内，并且在这个范围内有他前面的robot，则他选择停止
        int kval = 5;
        if (dis[park[id].pos_.x_][park[id].pos_.y_] <= kval) {
            for (int i = 0; i < id_; i++) {
                int x = current.robot[i].pos_.x_, y = current.robot[i].pos_.y_;
                if (std::abs(park[id].pos_.x_ - x) +
                        std::abs(park[id].pos_.y_ - y) <=
                    kval) {
                    return {{0, 0}, {0, 0}};
                }
            }
            // std::vector<Axis> points;
            // int x = park[id].pos_.x_, y = park[id].pos_.y_;
            // for (int dx = 0; dx <= 3; dx++) {
            //     for (int dy = 0; dy <= 3; dy++) {
            //         points.push_back({x + dx, y + dy});
            //     }
            // }
            // int ran_num = rand() % 16;
            // x = points[ran_num].x_, y = points[ran_num].y_;
            // std::queue<int> q1;
        }
        // 距离比较远则直接向泊位走
        int x = park[id].pos_.x_, y = park[id].pos_.y_;
        while (pre[x][y] != Axis(pos_.x_, pos_.y_)) {
            int tmpx = pre[x][y].x_;
            int tmpy = pre[x][y].y_;
            x = tmpx;
            y = tmpy;
        }

        return {{x - pos_.x_, y - pos_.y_}, {0, 0}};
    }

    // return {{0, 0}, {0, 0}};

    // 枚举货物和泊位算最优权值解
    double maxw = -100;
    Goods maxgood;
    int parkid = 0;
    for (auto goods : unpickedGoods) {
        // 机器人到货物的距离
        int dis1 = dis[goods.pos_.x_][goods.pos_.y_];
        if (dis1 == INT_MAX / 2) continue;
        // 货物到泊位的距离
        for (int id = 0; id < kMAX_PARK; id++) {
            int dis2 = goods.get_dis(id);
            if (dis2 == INT_MAX / 2) continue;
            double w = getw(dis1, dis2, goods.value_);
            if (w > maxw) {
                maxw = w;
                parkid = id;
                maxgood = goods;
            }
        }
    }

    // 没得走
    if (maxw < 0) return {{0, 0}, {0, 0}};

    // 计算机器人到货物的路径（一定存在路径）
    assert(dis[maxgood.pos_.x_][maxgood.pos_.y_] != INT_MAX / 2);
    x = maxgood.pos_.x_, y = maxgood.pos_.y_;
    unpickedGoods.erase(maxgood);
    while (pre[x][y] != Axis(pos_.x_, pos_.y_)) {
        int tmpx = pre[x][y].x_;
        int tmpy = pre[x][y].y_;
        x = tmpx;
        y = tmpy;
    }
    return {{x - pos_.x_, y - pos_.y_}, maxgood.pos_};
}