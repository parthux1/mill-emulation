#include "tests_board.h"

void tests_board::run_all()
{
    mill_detection(1, false);
    size_check();
    edit_check();
}

bool tests_board::board_is_legal(const Board& b) noexcept
{
    return false;
}

Board tests_board::random_board(unsigned char min_amount) noexcept
{
    srand(time(0));

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

//
// Test-suites
//

void tests_board::mill_detection(unsigned int amount, bool verbose) {
    std::cout << "[TEST] Starting " << amount << " mill_detection_tests_board\n";
    for(unsigned int run = 0; run < amount; run++)
    {
        // Generate Board
        Board b = tests_board::random_board(10);
        // check for mills
        
        if(verbose)
        {
            std::cout << "mill detection test: " << run+1 << '\n';
            b.print_board();
        }
        bool flag = false;
        for(Position pos : b.get_array_copy())
        {
            b.get_occupation_at(pos);
            if(pos.occupation != 0) flag = b.pos_is_mill(pos);

            if(flag && verbose)std::cout << (int)pos.ring << "." << (int)pos.rel_pos << " is part of a mill\n";
            flag = false;
        }
    }
}

void tests_board::size_check()
{
    std::cout << "[TEST] size_check()\n";
    std::cout << "Position size: " << sizeof(Position) << '\n';
    std::cout << "Board size   : " << sizeof(Board) << '\n';
}

void tests_board::edit_check()
{
    Board b;

    srand(time(0));

    std::cout << "[TEST] edit_check()\n";

    // check set_occupation_at
    unsigned char test_amount = 10;
    unsigned char run_success = 0;

    const std::vector<std::pair<Board, Position>> run_error;

    for(unsigned char run = 0; run < test_amount; run++)
    {
       Position p{rand()%3, rand()%8, rand()%2, 0};
       b.set_occupation_at(p, false);

        // Save state if test fails
        if(b.get_occupation_at(p) == p.occupation) run_success++;
        else run_error.push_back(std::make_pair<Board, Position>(b, p));
    }

    // Output
    std::cout << "[TEST_RES] set_occupation_at [" << (int) run_success << "/" << test_amount << "]\n";

    if(run_success != test_amount)
    {
        std::cout << "[        ] failed tests_board:\n";
        for(auto[board, pos] : run_error)
        {
            std::cout << "[FAILED  ] Position " << (int) pos.ring << '.' << (int) pos.rel_pos << " occupation: " << (int) pos.occupation << "\n";
            std::cout << "[FAILED] Boadstate:\n";
            board.print_board();
        }
    }

    // check get_last_moved
    std::cout << "[TEST_RES] get_last_moved: not implemented (edit_check())\n";
}