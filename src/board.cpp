#include "board.h"

//////////
// Board /
//////////

Board::Board()
{
    positions = Board::get_new_position_array();
    gamestate = Board::State::place_stones;
}

Board::Board(const std::array<Position, 24>& positions)
    : positions(positions)
{
    gamestate = Board::State::place_stones;
}

Board::Board(const Board& b)
{
    positions = b.get_array_copy();
    gamestate = b.get_gamestate();
}


///////////
// getter /
///////////


std::array<Position, 24> Board::get_array_copy() const noexcept
{
    return positions;
}

//TODO move - this is not a public getter
inline unsigned char Board::get_array_pos(const Position& pos) noexcept
{
    return pos.ring*8+pos.rel_pos;
}

unsigned char  Board::get_occupation_at(const Position& pos) const noexcept
{
    return positions[get_array_pos(pos)].occupation;
}

Position Board::get_last_moved() const noexcept
{   
    
    for(const Position& pos : positions)
    {
        if(pos.last_moved) return pos;
    }

    // return a value with moved=1 and occupation=0
    const Position pos = {0, 0, 0, 1}; //TODO would 0b1 work?
    return pos;
}

std::array<Position, 24> Board::get_new_position_array()
{
    std::array<Position, 24> ret_array;

    // Init all 24 positions
    Position p_default;
    p_default.occupation = 0;
    p_default.last_moved = 0;

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
    const unsigned char array_index = get_array_pos(pos);

    // the value we check against
    const unsigned char compare_occ = positions[array_index].occupation;   

    // (1)
    if(pos.rel_pos % 2 == 1)
    {
        // check 1 - in the array the pieces are 8 apart
        if(positions[pos.rel_pos].occupation == positions[pos.rel_pos+8].occupation && positions[pos.rel_pos].occupation ==  positions[pos.rel_pos+16].occupation) return true;

        // check 2 - one below, one above
        // this won't be oob, because the value is odd.
        // TODO in (2) check1 & 2 we navigate using get_array_pos(). use this here too?
        return (compare_occ == positions[array_index-1].occupation && compare_occ == positions[array_index+1].occupation);
    }

    // (2)
    // we use the fact, that each bitfield member has its own overflow-handling
    
    // check 1
    // array-positions of the next 2 values
    pos.rel_pos +=1;
    const unsigned char next = get_array_pos(pos);
    pos.rel_pos += 1;
    const unsigned char nextnext = get_array_pos(pos);

    if(compare_occ == positions[next].occupation && compare_occ == positions[nextnext].occupation) return true;
    
    // check 2
    // position of the 2 previous values
    pos.rel_pos -= 3;
    const unsigned char prev = get_array_pos(pos);
    pos.rel_pos -= 1;
    const unsigned char prevprev = get_array_pos(pos);
    
    return (positions[prev].occupation == positions[array_index].occupation && positions[prevprev].occupation == positions[array_index].occupation);
}

Board::State Board::get_gamestate() const noexcept
{
    return gamestate;
}

///////////
// setter /
///////////

void Board::set_occupation_at(Position pos, bool count_as_moved) noexcept
{
    Position& edit_pos = positions[get_array_pos(pos)];
    edit_pos.occupation = pos.occupation;
    
    if(count_as_moved)
    {
        // remove existing last_moved
        for(Position& pos : positions)
        {
            if(pos.last_moved)
            {
                pos.last_moved = false;
                break;
            }
        }

        edit_pos.last_moved = true;
    }
    
}

Board::Feedback Board::move_piece(Position pos_start, Position pos_target, bool player_id) noexcept
{
    Position& start = positions[get_array_pos(pos_start)];
    Position& target = positions[get_array_pos(pos_target)];

    // start-pos isn't owned by the player?
    if(start.occupation != ((unsigned char)player_id+1)) return Feedback::fail;

    // target pos is already occupied?
    // if start == target this will return 
    if(target.occupation) return Feedback::fail;

    // target pos not reachable?

    // TODO: check if player is allowed to fly
    const bool player_can_fly = player_id ? (gamestate == State::fly_two) : (gamestate == State::fly_one);
    if(!player_can_fly && !(gamestate == State::fly_both))
    {
        // is relative neighbors on same ring
        const bool relative_flag = (start.rel_pos -1 <= target.rel_pos && start.rel_pos >= target.rel_pos) // neighbor of start (+-1 away)
                                    && 
                                   (start.ring = target.ring); // same ring
        
        // in case of pos 1, 3, 5, 7 up to 2 more moves are possible
        const bool ring_overlap_flag = (start.rel_pos % 2 == 1 && start.rel_pos == target.rel_pos) // odd position and same pos on other ring
                                        &&
                                        (std::abs(start.ring - target.ring) == 1); // neighbor ring

        if(!relative_flag && !ring_overlap_flag) return Feedback::fail;
    }
    
    // everything okay. Move piece
    target.occupation = start.occupation;
    start.occupation = 0;

    if(pos_is_mill(target)) return Feedback::mill;
    
    return Feedback::success;
}

/////////////////////
// output functions /
/////////////////////

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
