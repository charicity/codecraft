#include "Step.h"

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

void ControlLogic::frame_process(Frame &current) {
    final_score = std::max(final_score, current.currentMoney_);
    if (current.code_ % 1000 == 0)
        std::cerr << "processing frame #" << current.code_
                  << "| Money=" << current.currentMoney_ << " good_val="<<cnt_good<<std::endl;
    // 处理过期问题
    goods_expire(current.code_);
    // 先进行机器人的操作
    robots_behave(current);
    // 再执行船的操作
    ships_behave(current);
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