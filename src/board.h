#pragma once
#include "position.h"
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
    std::array<Position, 24> positions;


    //////////////////////
    // private functions /
    //////////////////////

    // calculates the array-location of the Position value
    static inline unsigned char get_array_pos(const Position& pos)  noexcept;

public:
    // Creates a board with non-occupied positions
    Board();

    // Creates a board with the given positions-array
    // The positions may not be ill-formed and should be created using Board::get_new_position_array()
    Board(const std::array<Position, 24>& positions);    
    
    ///////////
    // getter /
    ///////////

    // Returns the currently stored array -> gamestate
    std::array<Position, 24> get_array_copy() const noexcept;

    // Copies the current occupation into the given object
    void get_occupation_at(Position& pos) const noexcept;
    
    //TODO test
    // Returns the last edited Position -> last-moved = 1
    // If there's no such value will return a Position with occupation = 0
    Position get_last_moved() const noexcept;

    // returns an initialized non-occupied positions-array
    static std::array<Position,24> get_new_position_array();

    //TODO test    
    //checks if the given position is part of a mill
    bool pos_is_mill(Position pos) const;
    
    ///////////
    // setter /
    ///////////

    // Sets the current occupation to the value of the given object
    void set_occupation_at(Position pos) noexcept;
    
    //TODO
    // "move a piece" - may toggle a mill
    void set();

    ////////////////////
    // ouput functions /
    ////////////////////

    // Prints every position in list-form
    void print_list();
    
    // Displays the board as a string (X.X)
    void print_board();
};
