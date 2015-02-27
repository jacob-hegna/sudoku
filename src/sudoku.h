#ifndef __SUDOKU_H_
#define __SUDOKU_H_

#include <array>

bool solve_sudoku(std::array<int, 81>, std::array<int, 81>*);

bool verify_sudoku(std::array<int, 81>);

void print_sudoku(std::array<int, 81>);
std::array<int, 81> parse_sudoku();

#endif