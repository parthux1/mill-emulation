#include "board.h"

Board::Board()
{
    positions = Board::get_new_position_array();
}

Board::Board(const std::array<Position, 24>& positions)
    : positions(positions)
{

}


bool Board::pos_is_mill(Position pos) const
{
    /*
     *     A position is a mill if 2 other conected pices in a straight row are of the same occupation
     *     every piece has 2 mill-options, we need to run 2 checks.
     * (1) for pos 1, 3, 5, 7 the first check is for the same numbers on the other ring
     *                        the second check will be on the same ring for the numbers +- 1
     * (2) pos 0, 2, 4, 6 are in a corner and will only be checked against values in the same ring. The first check will be against the next 2 greater numbers +1 +2
     *                        the second check will be on the next 2 smaller numbers -1 -2
     *                        Because this values can be 0 or 7 we need to mod8
    */
    
    // return if position is not occupied
    if(!pos.occupation) return false;

    // calculate the position of this piece in the array
    const unsigned char array_index = pos.ring*8+pos.rel_pos;
    

    // (1)
    if(pos.rel_pos % 2 == 1)
    {
        // check 1 - in the array the pieces are 8 apart
        if(positions[pos.rel_pos].occupation == positions[pos.rel_pos+8].occupation == positions[pos.rel_pos+16].occupation) return true;

        // check 2 - one below, one above
        return (positions[array_index-1].occupation == positions[array_index+1].occupation == pos.occupation);
    }

    // (2)
    // check 1 - next 2 greater values
    const unsigned char next = (pos.rel_pos+1)%8;
    const unsigned char nextnext = (pos.rel_pos+2)%8;

    if(positions[(pos.ring*8)+next].occupation == positions[(pos.ring*8)+nextnext].occupation == positions[array_index].occupation) return true;
    
    // check 2 . next 2 lesser values
    const unsigned char prev = (pos.rel_pos-1)%8;
    const unsigned char prevprev = (pos.rel_pos-2)%8;

    return (positions[(pos.ring*8)+prev].occupation == positions[(pos.ring*8)+prevprev].occupation == positions[array_index].occupation);
}

// getter

inline unsigned char Board::get_array_pos(const Position& pos) const noexcept
{
    return pos.ring*8+pos.rel_pos;
}

void Board::get_occupation_at(Position& pos) const noexcept
{
    pos.occupation = positions[get_array_pos(pos)].occupation;
}

std::array<Position, 24> Board::get_new_position_array()
{
    std::array<Position, 24> ret_array;

    // Init all 24 stones
    Position p_default;
    p_default.occupation = 0;

    // Ring iteration
    for(unsigned char i = 0; i < 3; i++)
    {
        p_default.ring = i;

        // relative_pos iteration
        for(unsigned char j = 0; j < 8; j++)
        {
            p_default.rel_pos = j;
            ret_array[i*8+j] = p_default;
        }
    }

    return ret_array;
}

// setter
void Board::set_occupation_at(Position pos) noexcept
{
    positions[get_array_pos(pos)].occupation = pos.occupation;
}

// Output functions

void Board::print_list()
{
    for(Position pos : positions)
    {
        std::cout << "Ring: " << (int)pos.ring << " rel_pos: " << (int)pos.rel_pos << " occupation:" << (int)pos.occupation << '\n';
    }
}

void Board::print_board()
{
    std::array<std::string, 24> ocp; // occupation characters for all positions
    
    for(unsigned char i = 0; i < 24; i++) ocp[i] = (positions[i].occupation == 0 ? " " : (positions[i].occupation == 1 ? "X" : "O"));

    // Don't look at this abomination..

    const std::string ret_val = ocp[0] + "-----" + ocp[1] + "-----" + ocp[2] 
                        + "\n|     |     |"
                        + "\n| " + ocp[8] + "---" + ocp[9] + "---" + ocp[10] + " |"
                        + "\n| |   |   | |"
                        + "\n| | " + ocp[16] + "-" + ocp[17] + "-" + ocp[18] + " | |"
                        + "\n| | |   | | |\n"
                        +       ocp[7] + "-" + ocp[15] + "-" + ocp[23] + "   " + ocp[19] + "-" + ocp[11] + "-" + ocp[3]
                        + "\n| | |   | | |"
                        + "\n| | " + ocp[22] + "-" + ocp[21] + "-" + ocp[20] + " | |"
                        + "\n| |   |   | |"
                        + "\n| " + ocp[14] + "---" + ocp[13] + "---" + ocp[12] + " |"
                        + "\n|     |     |\n"
                        +       ocp[6] + "-----" + ocp[5] + "-----" + ocp[4] + "\n";

    std::cout << ret_val;
}
