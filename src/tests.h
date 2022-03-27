#pragma once
#include "board.h"


namespace tests
{

    // Test if a board is possible
    // TODO: check amount of occupations 2 or more mills -> there must be less occupations
    bool board_is_legal();

    // Generate a random board
    // TODO
    Board random_board();


    //
    // Test suites
    //

    // test different boards for mills
    // TODO
    void mill_detection(bool verbose);
}
