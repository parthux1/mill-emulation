#include "tests.h"

bool tests::board_is_legal(const Board& b) noexcept
{
    return false;
}

Board tests::random_board() noexcept
{
    // standard board
    Board b = Board();
    
    //flip some occupations


    return b;
}


// Test-suites


void tests::mill_detection(unsigned int amount, bool verbose) {
    std::cout << "[TEST] Starting " << amount << " mill_detection_tests\n";
    for(unsigned int run = 0; run < amount; run++)
    {
        // Generate Board
        Board b = tests::random_board();
        // check for mills

        bool flag = false;
        for(Position pos : tests::mill_min_positions)
        {
            b.get_occupation_at(pos);
            if(pos.occupation != 0) flag = b.pos_is_mill(pos);

            if(flag && verbose) std::cout << pos.ring << '.' << pos.rel_pos << " is part of a mill\n";
        }
    }
}

void tests::size_check()
{
    std::cout << "[TEST] size_check()\n";
    std::cout << "Position size: " << sizeof(Position) << '\n';
    std::cout << "Board size   : " << sizeof(Board) << '\n';
}
