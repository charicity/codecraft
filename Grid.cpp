#include "Grid.h"

#include <iostream>

void Grid::init() {
    char c;
    do {
        std::cin >> c;
    } while (c == ' ' && c == '\n');
    switch (c) {
        case '.': {
            state_ = Grid::empty;
            break;
        }
        case '*': {
            state_ = Grid::ocean;
            break;
        }
        case '#': {
            state_ = Grid::barrier;
            break;
        }
        case 'A': {
            state_ = Grid::robot;
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