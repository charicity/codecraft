#include "Grid.h"

#include <iostream>

void Grid::input() {
    for (int i = 0; i < kMAX_GRID; ++i) {
        for (int j = 0; j < kMAX_GRID; ++j) {
            char c;
            do {
                std::cin >> c;
            } while (c == ' ' && c == '\n');
            switch (c) {
                case '.': {
                    grid_[i][j] = Grid::empty;
                    break;
                }
                case '*': {
                    grid_[i][j] = Grid::ocean;
                    break;
                }
                case '#': {
                    grid_[i][j] = Grid::barrier;
                    break;
                }
                case 'A': {
                    grid_[i][j] = Grid::robot;
                    break;
                }
                case 'B': {
                    grid_[i][j] = Grid::park;
                    break;
                }
                default: {
                    std::cerr << "ERROR WHEN GETTING GRID" << std::endl;
                    break;
                }
            }
        }
    }
}