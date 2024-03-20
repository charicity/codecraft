#include "Goods.h"

#include <iostream>
#include <set>

#include "Park.h"
#include "global.h"

std::set<Goods> unpickedGoods;  // 所有的没有被拿起过且存在的货物
std::set<Goods> safeGoods;  // 所有被拿起过的且还在场上（没被运走）的货物

void Goods::input(int current_frame) {
    pos_.input();
    std::cin >> value_;
    happened_frame_ = current_frame;
    static int cnt = 0;
    code_ = ++cnt;
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

void Goods::showoff() {
    // std::cerr << "Goods #" << code_ << " will show in (" << pos_.x_ << ","
    //           << pos_.y_ << ")" << std::endl;
    // std::cerr << std::cin.eof() << " " << std::cin.fail() << std::endl;
    if (grid[pos_.x_][pos_.y_].haveGood == true) {
        // std::cerr << "in showoff(): Error-STACKED" << std::endl;
        return;
    }
    unpickedGoods.insert(*this);

    grid[pos_.x_][pos_.y_].place(*this);
}