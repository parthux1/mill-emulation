#pragma once
#include "board.h"


namespace tests
{

    // Test if a board is possible
    // TODO: check amount of occupations 2 or more mills -> there must be less occupations
    bool board_is_legal(const Board& b) noexcept;

    // Generate a random board
    // TODO
    Board random_board() noexcept;

    const std::array<const Position, 12> mill_min_positions = {
        // 1 in ring 0, 1 , 2
        0b00000100,
        0b01000100,
        0b11000100,
        // 3 in ring 0, 1, 2
        0b00001100,
        0b01001100,
        0b11001100,
        // 5 in ring 0, 1, 2
        0b00010100,
        0b01010100,
        0b11010100,
        // 7 in ring 0, 1, 2
        0b00011100,
        0b01011100,
        0b11011100
        };

    //
    // Test suites
    //

    // test different boards for mills
    // TODO
    void mill_detection(unsigned int amount, bool verbose);

    // Prints the sizes of all custom types
    void size_check();
}
