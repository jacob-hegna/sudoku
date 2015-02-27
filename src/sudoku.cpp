#include "sudoku.h"

#include <iostream>
#include <stdint.h>
#include <cmath>
#include <algorithm>
#include <vector>

int grp(int i, int j) {return ((i/3)*9)+i%3 + ((j%3)*3)+(j/3)*27;}
int row(int i, int j) {return j*9 + i;}
int col(int i, int j) {return i*9 + j;}

int get_row(int i) {return i/9;}
int get_col(int i) {return i%9;}
int get_grp(int i) {return (get_row(i)/3)*3+get_col(i)/3;}

bool verify_complete(std::array<int, 81> state, std::function<int(int, int)> f, int j) {
    uint16_t verify = 0;
    for(int i = 0; i < 9; ++i) {
        verify = verify | ((uint16_t)pow(2, state.at(f(i, j))) >> 1);
    }
    return (verify == 511);
}

bool verify_sudoku(std::array<int, 81> state) {
    for(int i = 0; i < 9; ++i) {
        if(!verify_complete(state, grp, i)) return false;
        if(!verify_complete(state, row, i)) return false;
        if(!verify_complete(state, col, i)) return false;
    }
    return true;
}

bool verify_incomplete(std::array<int, 81> state, std::function<int(int, int)> f, int j) {
    std::vector<int> list;
    for(int i = 0; i < 9; ++i) {
        if(state.at(f(i, j)) != 0)
            list.push_back(state.at(f(i, j)));
    }
    std::sort(list.begin(), list.end());
    auto last = std::unique(list.begin(), list.end());
    return (last == list.end());
}

bool safe_sudoku(std::array<int, 81> state, int i) {
    return (
        verify_incomplete(state, grp, get_grp(i)) &&
        verify_incomplete(state, col, get_col(i)) && 
        verify_incomplete(state, row, get_row(i))
    );
}

bool solve_sudoku(std::array<int, 81> start, std::array<int, 81> *end) {
    for(int i = 0; i < 81; ++i) {
        if(start.at(i) == 0) {
            for(int j = 1; j < 10; ++j) {
                start[i] = j;
                if(safe_sudoku(start, i)) {
                    if(solve_sudoku(start, end))
                        return true;
                    start[i] = 0;
                }
            }
            return false;
        }
    }
    *end = start;
    return true;
}

void print_sudoku(std::array<int, 81> state) {
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            int a = state.at(i*9 + j);
            std::cout << ((a != 0) ? std::to_string(a) : ".");

            if((j+1) % 3 == 0 && j != 8) {
                std::cout << "|";
            }
        }
        std::cout << std::endl;

        if((i+1) % 3 == 0 && i != 8) {
            std::cout << "---+---+---" << std::endl;
        }
    }
}