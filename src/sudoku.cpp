#include "sudoku.h"

#include <stdint.h>
#include <cmath>

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

void Sudoku::solve(void) {
    
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
        if(!verify_grp(i)) return false;
        if(!verify_row(i)) return false;
        if(!verify_col(i)) return false;
    }
    return true;
}

bool Sudoku::verify_grp(int grp) {
    uint16_t verify = 0;
    for(int i = 0; i < 9; ++i) {
        verify = verify | ((uint16_t)pow(2, state.at(((i/3)*9)+i%3 + ((grp%3)*3)+(grp/3)*27)) >> 1);
    }
    return (verify == 511);
}

bool Sudoku::verify_row(int row) {
    uint16_t verify = 0;
    for(int i = 0; i < 9; ++i) {
        verify = verify | ((uint16_t)pow(2, state.at(row*9 + i)) >> 1);
    }
    return (verify == 511);
}

bool Sudoku::verify_col(int col) {
    uint16_t verify = 0;
    for(int i = 0; i < 9; ++i) {
        verify = verify | ((uint16_t)pow(2, state.at(i*9 + col)) >> 1);
    }
    return (verify == 511);
}
