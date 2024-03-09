#include "Robot.h"

#include <climits>
#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#include "Grid.h"
#include "Park.h"
#include "global.h"

void Robot::input() {
    std::cin >> object_;
    pos_.input();
    std::cin >> status_;
}

std::vector<Axis> Robot::get_path(int id) {
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