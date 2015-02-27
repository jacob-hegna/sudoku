#include <array>
#include <iostream>

#include "sudoku.h"

int main(int argc, char *argv[]) {
    std::array<int, 81> game = {
        8,0,0, 0,0,0, 0,0,0,
        0,0,3, 6,0,0, 0,0,0,
        0,7,0, 0,9,0, 2,0,0,

        0,5,0, 0,0,7, 0,0,0,
        0,0,0, 0,4,5, 7,0,0,
        0,0,0, 1,0,0, 0,3,0,
        
        0,0,1, 0,0,0, 0,6,8,
        0,0,8, 5,0,0, 0,1,0,
        0,9,0, 0,0,0, 4,0,0
    };

    solve_sudoku(game, &game);
    if(verify_sudoku(game)) {
        print_sudoku(game);
    } else {
        std::cout << "I couldn't solve it :/" << std::endl;
    }

    return 0;
}