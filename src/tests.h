#pragma once

#include <stdlib.h> // for rand
#include <time.h> // seed for srand
#include "board.h"


namespace tests
{

    // Test if a board is possible
    // TODO: check amount of occupations 2 or more mills -> there must be less occupations
    bool board_is_legal(const Board& b) noexcept;

    // Generate a random board
    // TODO
    Board random_board(unsigned char min_amount = 0) noexcept;

    const std::array<const Position, 12> mill_min_positions = {
        // 1 in ring 0, 1 , 2
        Position(0, 1, 0, 0),
        {1, 1, 0, 0},
        {2, 1, 0, 0},
        // 3 in ring 0, 1, 2
        {0, 3, 0, 0},
        {1, 3, 0, 0},
        {2, 3, 0, 0},
        // 5 in ring 0, 1, 2p
        {0, 5, 0, 0},
        {1, 5, 0, 0},
        {2, 5, 0, 0},
        // 7 in ring 0, 1, 2
        {0, 7, 0, 0},
        {1, 7, 0, 0},
        {2, 7, 0, 0}
        };

    //
    // Test suites
    //

    // test (reandom, if verbose) boards for mills
    // currently only implemented for verbose==true
    // TODO: implement silent, real tests
    void mill_detection(unsigned int amount, bool verbose);

    // Prints the sizes of all custom types
    void size_check();
}
