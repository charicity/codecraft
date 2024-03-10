#include "Goods.h"

std::set<Goods&> allGoods;

#include <iostream>

#include "Park.h"
#include "global.h"

void Goods::input() {
    pos_.input();
    std::cin >> value_;
}

// 得到从该货物到park[id]的最短路径
std::vector<Axis> Goods::get_path(int id) {
    int curx = pos_.x_, cury = pos_.y_;
    std::vector<Axis> path;
    if (park[id].dis[curx][cury] == INT_MAX / 2) {
        return path;
    }
    int x = park[id].pos_.x_, y = park[id].pos_.y_;
    path.push_back({x, y});
    while (park[id].pre[x][y] != Axis(-1, -1)) {
        x = park[id].pre[x][y].x_, y = park[id].pre[x][y].y_;
        path.push_back({x, y});
    }
    return path;
}
// 得到从该货物到park[id]的最短路径的长度
int Goods::get_dis(int id) { return park[id].dis[pos_.x_][pos_.y_]; }