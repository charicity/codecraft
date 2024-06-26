#include "Grid.h"

#include <iostream>

#include "global.h"
Grid grid[kMAX_GRID][kMAX_GRID];

void Grid::place(const Goods& tobeplace) {
    goodHere = tobeplace;
    haveGood = true;
}
void Grid::remove() { haveGood = false; }

void Grid::init() {
    char c;
    do {
        std::cin >> c;
    } while (c == ' ' && c == '\n');
    switch (c) {
        case '.': {
            state_ = Grid::empty;
            ++cnt_ground;
            break;
        }
        case '*': {
            state_ = Grid::ocean;
            break;
        }
        case '#': {
            state_ = Grid::barrier;
            ++cnt_barriar;
            break;
        }
        case 'A': {
            state_ = Grid::robot;
            /*特殊处理，把机器人变成空地*/
            state_ = Grid::empty;
            ++cnt_ground;
            break;
        }
        case 'B': {
            state_ = Grid::park;
            break;
        }
        default: {
            std::cerr << "ERROR WHEN GETTING GRID" << std::endl;
            break;
        }
    }
}