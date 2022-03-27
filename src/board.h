#pragma once
#include <array>
#include <iostream>
#include <string>


/*Board structure
 *0-----1-----2
 *|     |     |
 *| 0---1---2 |   - 24 Fields
 *| |   |   | |   - max. 18 stones one the board
 *| | 0-1-2 | |   - 8 horizontal + 8 vertical = 16 ways to create a mill
 *| | |   | | |   
 *7-7-7   3-3-3   
 *| | |   | | |
 *| | 6-5-4 | |
 *| |   |   | |
 *| 6---5---4 |
 *|     |     |
 *6-----5-----4
*/

struct Position
{
    /*
     * ring:       00 - outer, 01 - middle, 11 - inner
     * rel_pos:    0-7 as shown in board-struct-Comment
     * occupation: 00 - none, 01 - player1, 11 - player2
    */
    unsigned char ring : 2, rel_pos : 4, occupation : 2;
};

class Board
{
private:
    enum State
    {
        place_stones = 0,
        move = 1,
        fly_one = 2, //one player has only 3 stones
        fly_two = 3 // both player have 3 stones
    };
public: //TODO: make private. currently public because of easy tests
    std::array<Position, 24> positions;

    //TODO test
    // Check if the given position is part of a mill
    bool pos_is_mill(Position pos) const;

public:
    Board();

    // Prints every position in list-form
    void print_list();

    // Displays the board as a string (X.X)
    void print_board();
};
