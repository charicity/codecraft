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
double getw(int robotid, int dis1, int dis2, int val, int expire_time,
            Frame& current) {
    // if (robotid == 0) return 1.0/(dis1 + dis2);
    // if(robotid%3==0)return (double)val / (dis1 + dis2);
    // if(robotid%3==1)return (double)(val*val) / (dis1 + dis2);
    // return (double)(val*val*val) / (dis1 + dis2);
    if (dis1 + dis2 == 0) return 10000000;
    // return (double)(val * 10 + 1000 - expire_time) / (dis1);
    // 小于25的不捡了
    //  return 0;
    //  都为1/4概率
    //  总共16种情况
    //  double d = (dis1 + dis2);
    //  double w = 0;
    //  int time = (1000 - expire_time);  // 已经使用的时间越大越紧急
    //  if (time >= 750)
    //      w = 4;
    //  else if (time >= 500)
    //      w = 3;
    //  else if (time >= 200)
    //      w = 2;
    //  else
    //      w = 1;
    //  double ans = (double)val / 200 * (1.0 - (double)(dis1 + dis2) / 1000) *
    //               ((double)time / 1000);
    //  return ans;
    //  if (val >= 150) {
    //      if (time >= 750)
    //          return (double)(val * 10 + time * 5) / d;
    //      else if (time >= 500)
    //          return (double)(val * 10 + time * 5) / d;
    //      else if (time >= 250)
    //          return (double)(val * 10 + time * 2) / d;
    //      else
    //          return (double)(val * 10 + time * 2) / d;
    //  }
    //  if (val >= 100) {
    //      if (time >= 750)
    //          return (double)(val * 10 + time * 5) / d;
    //      else if (time >= 500)
    //          return (double)(val * 10 + time * 5) / d;
    //      else if (time >= 250)
    //          return (double)(val * 10 + time * 2) / d;
    //      else
    //          return (double)(val * 10 + time * 2) / d;
    //  }
    //  if (val >= 50) {
    //      if (time >= 750)
    //          return (double)(val * 10 + time * 2) / d;
    //      else if (time >= 500)
    //          return (double)(val * 10 + time * 2) / d;
    //      else if (time >= 250)
    //          return (double)(val * 10 + time * 1) / d;
    //      else
    //          return (double)(val * 10 + time * 1) / d;
    //  } else {
    //      return (double)((val * 10) + time) / d;
    //  }
    if (is_map_open()) {  // 243246
        if (val >= 175)
            return (double)(val * 10 + (1000 - expire_time) * 5) /
                   (dis1 + dis2);
        if (val >= 150)
            return (double)(val * 10 + (1000 - expire_time) * 4) /
                   (dis1 + dis2);
        if (val >= 125)
            return (double)(val * 10 + (1000 - expire_time) * 3) /
                   (dis1 + dis2);
        if (val >= 100)
            return (double)(val * 10 + (1000 - expire_time) * 2) /
                   (dis1 + dis2);
        if (val >= 75)
            return (double)(val * 10 + (1000 - expire_time) * 1) /
                   (dis1 + dis2);
        if (val >= 50)
            return (double)(val * 10 + 1000 - expire_time) / (dis1 + dis2);
        return 0;
    } else if (is_map_close()) {
        if (dis1 == 0) return 100000;
        double d = dis1;
        if (val >= 175)
            return (double)(val * 10 + (1000 - expire_time) * 8) / d;
        if (val >= 150)
            return (double)(val * 10 + (1000 - expire_time) * 7) / d;
        if (val >= 125)
            return (double)(val * 10 + (1000 - expire_time) * 6) / d;
        if (val >= 100)
            return (double)(val * 10 + (1000 - expire_time) * 5) / d;
        if (val >= 75) return (double)(val * 10 + (1000 - expire_time) * 4) / d;
        if (val >= 50) return (double)(val * 10 + (1000 - expire_time)*3) / d;
        if (val >= 25) return (double)(val * 10 + (1000 - expire_time)*2) / d;
        return 0;

    } else {  // 239383
        if (dis1 == 0) return 100000;
        double d = dis1;
        if (val >= 175)
            return (double)(val * 10 + (1000 - expire_time) * 6) / d;
        if (val >= 150)
            return (double)(val * 10 + (1000 - expire_time) * 5) / d;
        if (val >= 125)
            return (double)(val * 10 + (1000 - expire_time) * 4) / d;
        if (val >= 100)
            return (double)(val * 10 + (1000 - expire_time) * 3) / d;
        if (val >= 75) return (double)(val * 10 + (1000 - expire_time) * 2) / d;
        if (val >= 50) return (double)(val * 10 + 1000 - expire_time) / d;
        if (val >= 25) return (double)(val * 10 + 1000 - expire_time) / d;
        return 0;
    }
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
    // if (park[id].is_ban > current.code_) sum -= 100000;
    // if (park_good.size() <= 10)
    //     sum += park_good.size() * 4;  // 尽量搬来吧
    // else if (park_good.size() <= 20)
    //     sum += park_good.size() * 3;
    // else if (park_good.size() <= 40)  // 此时他还是有点物品的勉强可以搬来
    //     sum += park_good.size() * 2;
    // else
    //     sum -= 100;  // 此时他的附近基本没有物品了，不要再搬来了
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
            if (x >= 0 && x < kMAX_GRID && y >= 0 && y < kMAX_GRID)
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
    const int INF = INT_MAX / 2;
    // 手写队列
    dis[x][y] = 0;
    Axis que[kMAX_GRID * kMAX_GRID * 2];
    int hh = 0, tt = 0;
    que[0] = {x, y};
    int cnt = 0;
    while (hh <= tt) {
        Axis u = que[hh++];
        if (cnt >= 25000) break;
        // 随机
        int a = rand() % 4, b = rand() % 4;
        std::swap(dir[a], dir[b]);
        for (int i = 0; i < 4; i++) {
            int x = u.x_ + dir[i].x_, y = u.y_ + dir[i].y_;
            if (x < 0 || y < 0 || x >= kMAX_GRID || y >= kMAX_GRID) continue;
            if (grid[x][y].state_ == Grid::barrier ||
                grid[x][y].state_ == Grid::ocean)
                continue;
            if (dis[x][y] != INF) continue;
            cnt++;
            que[++tt] = {x, y};
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
        // id = id_; //每个机器人负责一个港口
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
    double maxw = -100000;
    Goods maxgood;
    maxgood.pos_ = {-1, -1};
    // maxgood.value_ = -10000;
    int parkid = 0;
    for (auto goods : unpickedGoods) {
        if (dis[goods.pos_.x_][goods.pos_.y_] >=
            goods.expire_frame(current.code_))
            continue;
        bool flag = 0;
        for (int i = 0; i < kMAX_ROBOT;
             i++) {  // 这个物品为上个人的瞄准对象我就不瞄准了
            if (choose[i] == goods.code_ && i != id_) flag = 1;
        }
        if (flag) continue;
        // 机器人到货物的距离
        // assert(goods.pos_.x_ >= 0 && goods.pos_.y_ >= 0 &&
        //        goods.pos_.x_ < kMAX_GRID && goods.pos_.y_ < kMAX_GRID);
        int dis1 = dis[goods.pos_.x_][goods.pos_.y_];
        if (dis1 == INT_MAX / 2) continue;
        // 货物到泊位的距离
        for (int id = 0; id < kMAX_PARK; id++) {
            int dis2 = goods.get_dis(id);
            if (dis2 == INT_MAX / 2) continue;
            double w = getw(id_, dis1, dis2, goods.value_,
                            goods.expire_frame(current.code_), current);
            if (w > maxw) {
                maxw = w;
                parkid = id;
                maxgood = goods;
            }
        }
    }
    // std::cerr << "in" << std::endl;
    // 没得走
    choose[id_] = 0;
    if (maxw < 0) return {{0, 0}, {-1, -1}};
    // 如果货物就在脚下就直接拿起
    // assert(maxgood.pos_.x_ >= 0);
    if (dis[maxgood.pos_.x_][maxgood.pos_.y_] == 0) {
        pickUp();
        choose[id_] = 0;
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
    choose[id_] = maxgood.code_;
    // std::cerr << "out" << std::endl;
    return {{x - pos_.x_, y - pos_.y_}, maxgood.pos_};
}