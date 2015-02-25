#ifndef __SUDOKU_H_
#define __SUDOKU_H_

#include <array>
#include <iostream>

class Sudoku {
public:
    Sudoku(void);
    Sudoku(std::array<int, 81>);
    ~Sudoku(void);

    void init(std::array<int, 81>);
    void solve(void);

    std::array<int, 81> get_state(void);

    friend std::istream& operator>>(std::istream&, Sudoku&);
    friend std::ostream& operator<<(std::ostream&, const Sudoku&);

private:
    bool verify(void);
    bool verify_grp(int);
    bool verify_row(int);
    bool verify_col(int);

    std::array<int, 81> state;
};

#endif