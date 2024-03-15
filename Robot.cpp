#include "Robot.h"

#include <algorithm>
#include <cassert>
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
    cnt_good += tobePicked.value_;
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

// dis1为从机器人到货物的最短距离，dis2为从货物到泊位的最短距离 ,权值计算函数
double getw(int dis1, int dis2, int val, Frame& current) {
    // if (current.code_ <= 40) return val;
    return (double)val / (dis1 + dis2);
}

// 得到机器人到park[id]的最短路径的长度
int Robot::get_dis(int id) { return park[id].dis[pos_.x_][pos_.y_]; }

// 机器人有了货物后要去到的泊位的估值函数:优先去大的
double Robot::get_toship_w(int id, std::vector<std::vector<int>>& dis,
                           Frame& current) {  //
    int dis_to_ship = dis[park[id].pos_.x_][park[id].pos_.y_];
    auto park_good = park[id].goods_queue_;
    double sum = -dis_to_ship;
    if (park[id].is_ban) sum -= 100000;
    // if (park[id].time_ + 1010 >= 15000 - current.code_ && ) sum -= 100000;
    // if (park_good.size() <= 20)
    //     sum += park_good.size() * 10;  // 尽量搬来吧
    // else if (park_good.size() <= 50)  // 此时他还是有点物品的勉强可以搬来
    //     sum += park_good.size();
    // else
    //     sum -= 100;  // 此时他的附近基本没有物品了，不要再搬来了
    // 尽量叠加货物
    // int totle_val = 0, totle_cnt;
    // while (park_good.size()) {
    //     totle_val += park_good.front().value_;
    //     totle_cnt++;
    //     park_good.pop();
    // }
    // if (totle_cnt >= 5) {  // 有了5个样本后开始测其平均价值
    //     sum += (double)totle_val / totle_cnt * 2;
    // }

    // 如果有船的话则增加其贡献
    // for (int i = 0; i < kMAX_SHIP; i++) {
    //     if (current.ship[i].parkid_ == id) sum += 50;
    // }

    return sum;
}
// robot到哪里取货,以及要的货物的位置
std::pair<Axis, Axis> Robot::get_dir(std::set<Goods>& unpickedGoods,
                                     Frame& current) {  // 求出bfs矩阵
    std::vector<std::vector<int>> dis(kMAX_GRID,
                                      std::vector<int>(kMAX_GRID, INT_MAX / 2));
    std::vector<std::vector<Axis>> pre(
        kMAX_GRID, std::vector<Axis>(kMAX_GRID, Axis(-1, -1)));
    int x = pos_.x_, y = pos_.y_;
    dis[x][y] = 0;
    std::queue<Axis> q;
    q.push(pos_);
    std::vector<Axis> dir;
    dir.push_back({-1, 0});
    dir.push_back({0, -1});
    dir.push_back({0, 1});
    dir.push_back({1, 0});
    // 将其他9个机器人的5个点push进来,我这个机器人不走这些格子
    std::set<Axis> points;
    for (int i = 0; i < kMAX_ROBOT; i++) {
        if (i == id_) continue;
        auto& robot = current.robot[i];
        points.insert(robot.pos_);
        for (int k = 0; k < 4; k++) {
            int x = robot.pos_.x_ + dir[k].x_, y = robot.pos_.y_ + dir[k].y_;
            points.insert({x, y});
        }
    }
    // 存起来将整个图这些地方加锁
    std::vector<std::pair<Axis, int>> vec;
    for (auto t : points) {
        vec.push_back({t, grid[t.x_][t.y_].state_});
        grid[t.x_][t.y_].state_ = Grid::barrier;
    }

    // 随机bfs
    int cnt = 0;
    while (q.size()) {
        Axis u = q.front();
        q.pop();
        if (cnt >= 20000) break;
        // 随机
        int a = rand() % 4, b = rand() % 4;
        std::swap(dir[a], dir[b]);
        for (int i = 0; i < 4; i++) {
            int x = u.x_ + dir[i].x_, y = u.y_ + dir[i].y_;
            if (x < 0 || y < 0 || x >= kMAX_GRID || y >= kMAX_GRID) continue;
            if (grid[x][y].state_ == Grid::barrier ||
                grid[x][y].state_ == Grid::ocean)
                continue;
            if (dis[x][y] != INT_MAX / 2) continue;
            cnt++;
            q.push({x, y});
            dis[x][y] = dis[u.x_][u.y_] + 1;
            pre[x][y] = {u.x_, u.y_};
        }
    }
    // 恢复现场
    for (auto t : vec) {
        Axis pos = t.first;
        int state = t.second;
        grid[pos.x_][pos.y_].state_ = state;
    }

    // 机器人扛着物品
    if (object_ == 1) {
        int id = 0;
        for (int j = 1; j < kMAX_PARK; j++) {  // 10
            if (get_toship_w(j, dis, current) > get_toship_w(id, dis, current))
                id = j;
        }
        if (dis[park[id].pos_.x_][park[id].pos_.y_] == INT_MAX / 2)
            return {{0, 0}, {0, 0}};
        int x = park[id].pos_.x_, y = park[id].pos_.y_;
        while (pre[x][y] != pos_) {
            int tmpx = pre[x][y].x_;
            int tmpy = pre[x][y].y_;
            x = tmpx;
            y = tmpy;
        }

        return {{x - pos_.x_, y - pos_.y_}, {-1, -1}};
    }

    // return {{0, 0}, {0, 0}};

    // 枚举货物和泊位算最优权值解
    double maxw = -100;
    Goods maxgood;
    maxgood.pos_ = {-1, -1};
    int parkid = 0;
    for (auto goods : unpickedGoods) {
        // 机器人到货物的距离
        // assert(goods.pos_.x_ >= 0 && goods.pos_.y_ >= 0 &&
        //        goods.pos_.x_ < kMAX_GRID && goods.pos_.y_ < kMAX_GRID);
        int dis1 = dis[goods.pos_.x_][goods.pos_.y_];
        if (dis1 == INT_MAX / 2) continue;
        // 货物到泊位的距离
        for (int id = 0; id < kMAX_PARK; id++) {
            int dis2 = goods.get_dis(id);
            if (dis2 == INT_MAX / 2) continue;
            double w = getw(dis1, dis2, goods.value_, current);
            if (w > maxw) {
                maxw = w;
                parkid = id;
                maxgood = goods;
            }
        }
    }

    // 没得走
    if (maxw < 0) return {{0, 0}, {-1, -1}};
    // 如果货物就在脚下就直接拿起
    if (dis[maxgood.pos_.x_][maxgood.pos_.y_] == 0) {
        return {{0, 0}, pos_};
    }
    // 计算机器人到货物的路径（一定存在路径）
    assert(dis[maxgood.pos_.x_][maxgood.pos_.y_] != INT_MAX / 2);
    // assert(maxgood.pos_ != Axis(-1, -1));
    x = maxgood.pos_.x_, y = maxgood.pos_.y_;
    unpickedGoods.erase(maxgood);
    while (pre[x][y] != pos_) {
        int tmpx = pre[x][y].x_;
        int tmpy = pre[x][y].y_;
        x = tmpx;
        y = tmpy;
    }
    return {{x - pos_.x_, y - pos_.y_}, maxgood.pos_};
}