#include "tests.h"

bool tests::board_is_legal(const Board& b) noexcept
{
    return false;
}

Board tests::random_board(unsigned char min_amount = 0) noexcept
{
    srand(time(NULL));

    // standard board
    std::array<Position, 24> positions = Board::get_new_position_array();

    // flip some occupations
    // amount of stones to place
    const unsigned char amount = rand() % (24-min_amount) + min_amount; // min-amount - 23 TODO: check if this is correct

    for(unsigned int current = 0; current < amount; current++)
    {
        //TODO: select random empty pos

        positions[current].occupation = rand()%2+1; // 1-2
        
    }

    return Board(positions);
}


// Test-suites


void tests::mill_detection(unsigned int amount, bool verbose) {
    std::cout << "[TEST] Starting " << amount << " mill_detection_tests\n";
    for(unsigned int run = 0; run < amount; run++)
    {
        // Generate Board
        Board b = tests::random_board(10);
        // check for mills
        
        if(verbose)
        {
            std::cout << "mill detection test: " << run+1 << '\n';
            b.print_board();
        }
        bool flag = false;
        for(Position pos : tests::mill_min_positions)
        {
            b.get_occupation_at(pos);
            if(pos.occupation != 0) flag = b.pos_is_mill(pos);

            if(flag && verbose) std::cout << (int)pos.ring << '.' << (int)pos.rel_pos << " is part of a mill\n";
        }
    }
}

void tests::size_check()
{
    std::cout << "[TEST] size_check()\n";
    std::cout << "Position size: " << sizeof(Position) << '\n';
    std::cout << "Board size   : " << sizeof(Board) << '\n';
}
