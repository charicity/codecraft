#include "Park.h"

#include <iostream>

#include "Axis.h"

void Park::init() {
    Axis tmp;
    pos_.input();
    std::cin >> time_ >> velocity_;

    // 预处理出从该泊位到达每个位置的bfs路径
    std::queue<Axis> q;
    q.push(pos_);
    const int inf = 1e9;
    for (int i = 0; i < kMAX_GRID; i++) {
        for (int j = 0; j < kMAX_GRID; j++) {
            pre[i][j] = {-1, -1};
            dis[i][j] = inf;
        }
    }
    int dx[4] = {-1, 0, 0, 1}, dy[4] = {0, -1, 1, 0};
    dis[pos_.x_][pos_.y_] = 0;
    while (q.size()) {
        Axis u = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x = u.x_ + dx[i], y = u.y_ + dy[i];
            if (x < 0 || y < 0 || x >= kMAX_GRID || y >= kMAX_GRID) continue;
            if (grid[x][y].state_ == Grid::barrier ||
                grid[x][y].state_ == Grid::ocean)
                continue;
            if (dis[x][y] != inf) continue;
            q.push({x, y});
            dis[x][y] = dis[u.x_][u.y_] + 1;
            pre[x][y] = {u.x_, u.y_};
        }
    }
}