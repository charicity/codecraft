#include "Park.h"

#include <climits>
#include <iostream>

#include "Axis.h"
#include "global.h"

Park park[kMAX_PARK];
int Park::tot_ban = 0;         // 被封禁了几个港口
int Park::min_back = INT_MAX;  // 回去时间最小的港口用时
int Park::min_id = -1;         // 回去时间最小的港口id
int Park::max_back = INT_MIN;

void Park::init(int id) {
    Axis tmp;
    pos_.input();
    id_ = id;
    std::cin >> time_ >> velocity_;
    // std::cerr << time_ << std::endl;
}

// 在当前时间去往虚拟点后，能否再回来做出贡献
// 是的话返回yes，否的话返回false
bool Park::can_return(Frame& current) {
    int rest_frame = 15000 - current.code_;
    int min_time = 1 + min_time_ + Park::min_back;

    return rest_frame >= min_time;
}

bool Park::have_ship() {
    if (id_ == Park::min_id) return false;  // 如果是中转用港口，则永远可以过去
    return tend_ship.size();
}

// 是否能从虚拟点到这个点、装完货之后再回来
// 否的话返回Park::impossible，否则返回要去往的park.id_
int Park::canback_from_virtual(Frame& current) {
    int rest_frame = 15000 - current.code_;
    int min_time = 2 * min_time_;
    if (min_time + 1 <= rest_frame) {  // 至少留一帧装货吧...
        if (this->need_shortcut()) return Park::min_id;
        return id_;
    }
    return Park::impossible;
}

// 是否能从别的泊位到这个点、装完货之后再回来
// 否的话返回Park::impossible，否则返回要去往的park.id_
int Park::canback_from_other(Frame& current) {
    int rest_frame = 15000 - current.code_;
    int min_time = 500 + min_time_;
    if (min_time + 1 <= rest_frame) {  // 至少留一帧装货吧...
        if (this->need_shortcut()) return Park::min_id;
        return id_;
    }
    return Park::impossible;
}

void Park::put(const Goods& tobePut) { goods_queue_.push(tobePut); }

void Park::load(Ship& current_ship) {
    int tmp = velocity_;
    while (tmp && !goods_queue_.empty() && current_ship.remain_capacity_) {
        current_ship.remain_capacity_--;
        tmp--;
        goods_queue_.pop();
    }
}

void Park::preprocess_mintime() {
    for (int i = 0; i < kMAX_PARK; ++i) {
        if (park[i].time_ < Park::min_back) {
            Park::min_back = park[i].time_;
            Park::min_id = i;
        }
        Park::max_back = std::max(Park::max_back, park[i].time_);
    }
    for (int i = 0; i < kMAX_PARK; ++i) {
        park[i].min_time_ = std::min(park[i].time_, Park::min_back + 500);
    }
}

void Park::preprocess_bfs() {
    // 预处理出从该泊位到达每个位置的bfs路径
    std::queue<Axis> q;
    q.push(pos_);
    for (int i = 0; i < kMAX_GRID; i++) {
        for (int j = 0; j < kMAX_GRID; j++) {
            pre[i][j] = {-1, -1};
            dis[i][j] = INT_MAX / 2;
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
            if (dis[x][y] != INT_MAX / 2) continue;
            q.push({x, y});
            dis[x][y] = dis[u.x_][u.y_] + 1;
            pre[x][y] = {u.x_, u.y_};
        }
    }
}