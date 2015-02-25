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
    bool solve(void);

    std::array<int, 81> get_state(void);

    friend std::istream& operator>>(std::istream&, Sudoku&);
    friend std::ostream& operator<<(std::ostream&, const Sudoku&);

private:
    bool verify(void);
    bool verify_cmp(int, std::function<int(int, int)>);
    bool verify_inc(int, std::function<int(int, int)>);
    static int grp(int i, int j) {return ((i/3)*9)+i%3 + ((j%3)*3)+(j/3)*27;}
    static int row(int i, int j) {return j*9 + i;}
    static int col(int i, int j) {return i*9 + j;}

    std::array<int, 81> state;
};

#endif