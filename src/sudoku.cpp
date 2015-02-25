#include "sudoku.h"

#include <stdint.h>
#include <cmath>
#include <algorithm>
#include <vector>

Sudoku::Sudoku(void) {

}

Sudoku::Sudoku(std::array<int, 81> state) {
    init(state);
}

Sudoku::~Sudoku(void) {

}

void Sudoku::init(std::array<int, 81> state) {
    this->state = state;
}

bool Sudoku::solve(void) {
    return verify();
}

std::array<int, 81> Sudoku::get_state(void) {
    return this->state;
}

std::istream& operator>>(std::istream& i, Sudoku& s) {
    return i;
}

std::ostream& operator<<(std::ostream& o, const Sudoku& s) {
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            int a = s.state.at(i*9 + j);
            o << ((a != 0) ? std::to_string(a) : ".");

            if((j+1) % 3 == 0 && j != 8) {
                o << "|";
            }
        }
        o << std::endl;

        if((i+1) % 3 == 0 && i != 8) {
            o << "---+---+---" << std::endl;
        }
    }
    return o;
}

bool Sudoku::verify(void) {
    for(int i = 0; i < 9; ++i) {
        if(!verify_cmp(i, grp)) return false;
        if(!verify_cmp(i, row)) return false;
        if(!verify_cmp(i, col)) return false;
    }
    return true;
}

// Verify complete
bool Sudoku::verify_cmp(int j, std::function<int(int, int)> f) {
    uint16_t verify = 0;
    for(int i = 0; i < 9; ++i) {
        verify = verify | ((uint16_t)pow(2, state.at(f(i, j))) >> 1);
    }
    return (verify == 511);
}

// Verify incomplete
bool Sudoku::verify_inc(int j, std::function<int(int, int)> f) {
    std::vector<int> list;
    for(int i = 0; i < 9; ++i) {
        if(state.at(f(i, j)) != 0)
            list.push_back(state.at(f(i, j)));
    }
    auto last = std::unique(list.begin(), list.end());
    return (last == list.end());
}