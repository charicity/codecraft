#include "Step.h"

#include <algorithm>
#include <cstring>
#include <queue>

#include "global.h"

std::queue<std::string> action_sequence;

void ControlLogic::init_input() {
    for (int i = 0; i < kMAX_GRID; ++i) {
        for (int j = 0; j < kMAX_GRID; ++j) {
            grid[i][j].init();
        }
    }
    // for (int i = 0; i < kMAX_GRID; ++i) {
    //     for (int j = 0; j < kMAX_GRID; ++j) {
    //         std::cerr << grid[i][j].state_;
    //     }
    //     std::cerr << std::endl;
    // }

    for (int i = 0; i < kMAX_PARK; ++i) {
        int id;
        std::cin >> id;
        park[id].init(i);
    }

    Ship::init();

    std::string s;
    std::cin >> s;
    // std::cerr << "[EXPECTED OK]: " << s << std::endl;
}

// 初始化处理
void ControlLogic::init_initialize() {
    for (int i = 0; i < kMAX_PARK; ++i) {
        park[i].preprocess_bfs();
    }
    Park::preprocess_mintime();
    std::cout << "OK" << std::endl;
    std::cout.flush();
}

// 输入一帧
bool ControlLogic::frame_input(Frame &current) {
    bool f = current.input();
    if (f == false) return false;

    for (auto &i : current.goodInfo) {
        i.showoff();
    }

    std::string s;
    std::cin >> s;
    return true;
}

bool cmp(std::pair<int, int> a, std::pair<int, int> b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
}

void ControlLogic::frame_process(Frame &current) {
    final_score = std::max(final_score, current.currentMoney_);
    if (current.code_ % 1000 == 0)
        std::cerr << "processing frame #" << current.code_
                  << "| Money=" << current.currentMoney_
                  << " good_val=" << cnt_good << std::endl;
    // 处理过期问题
    goods_expire(current.code_);
    // 先进行机器人的操作
    robots_behave(current);
    // 再执行船的操作
    ships_behave(current);

    static bool is_first = true;
    if (is_first == true && current.code_ + 4 * Park::max_back >= 15000) {
        if (is_map_open() || is_map_unknown()) {
            std::cerr << "banning at frame " << current.code_ << std::endl;
            is_first = false;
            std::vector<std::pair<int, int>> pii;
            for (int i = 0; i < kMAX_PARK; ++i) {
                pii.push_back({park[i].min_time_, i});
            }
            sort(pii.begin(), pii.end(), cmp);

            for (int i = 0; i < kMAX_PARK; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (i == pii[j].second) {
                        std::cerr << "banned " << i << std::endl;
                        park[i].is_ban = true;
                    }
                }
            }
        }
    }
}

// 对那一帧进行操作
void ControlLogic::frame_output(Frame &current) {
    while (!action_sequence.empty()) {
        auto &s = action_sequence.front();
        std::cout << s << std::endl;
        // std::cerr << s << std::endl;
        action_sequence.pop();
    }
    std::cout << "OK" << std::endl;
    // std::cerr << "OK" << std::endl;
    std::cout.flush();
}