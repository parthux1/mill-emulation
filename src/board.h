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

    // represents the current gamestate
    // TODO: implement as flag system so multiple states are possible. Usefull for adding turn-information and placement_count for place_stones
    enum State
    {
        place_stones = 0,
        move = 1,
        fly_one = 2, // player one has only 3 stones
        fly_two = 3, // player two has only 3 stones
        fly_both = 4, // both players have 3 stones
        winner_one = 5, // player one won the game
        winner_two = 6 // player two won the game
    };

    // Feedback for move_ functions so the player knows what happened
    enum Feedback
    {
        success,
        fail, 
        mill
    };

    State gamestate;

    std::array<Position, 24> positions;


    //////////////////////
    // private functions /
    //////////////////////

    // calculates the array-location of the Position value
    static inline unsigned char get_array_pos(const Position& pos)  noexcept;

    void update_state() noexcept;

public:
    // Creates a board with non-occupied positions
    Board();

    // Creates a board with the given positions-array
    // The positions may not be ill-formed and should be created using Board::get_new_position_array()
    Board(const std::array<Position, 24>& positions);    
   
    // For easy copying
    Board(const Board& b);

    ///////////
    // getter /
    ///////////

    // Returns the currently stored array -> gamestate
    std::array<Position, 24> get_array_copy() const noexcept;

    // Returns the current occupation on the given positiob
    unsigned char get_occupation_at(const Position& pos) const noexcept;
    
    //TODO test
    // Returns the last edited Position -> last-moved = 1
    // If there's no such value will return a Position with occupation = 0
    Position get_last_moved() const noexcept;

    // returns an initialized non-occupied positions-array
    static std::array<Position,24> get_new_position_array();

    //checks if the given position is part of a mill
    bool pos_is_mill(Position pos) const;
    
    // Returns the current gamestate of the board
    State get_gamestate() const noexcept;

    ///////////
    // setter /
    ///////////

    //TODO: test
    // Sets the current occupation to the value of the given object
    void set_occupation_at(Position pos, bool count_as_moved = true) noexcept;
    

    // TODO: test
    // tries to move a pice
    // \param pos_start: The starting position. only ring and rel_pos are needed
    // \param pos_target: The target position. only ring and rel_pos are needed
    // \param player_id: 0 for player 1, 1 for player 2. Used for giving feedback
    // \return Feedback, see enum for more information
    Board::Feedback move_piece(Position pos_start, Position pos_target, bool player_id) noexcept;
    
    ////////////////////
    // ouput functions /
    ////////////////////

    // Prints every position in list-form
    void print_list();
    
    // Displays the board as a string (X.X)
    void print_board();
};
