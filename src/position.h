#pragma once

struct Position
{
    // Init everything with 0
    Position();

    // TODO implement, check for lsb or msb
    Position(unsigned char byte);

    Position(unsigned char ring, unsigned char rel_pos, unsigned char occupation, unsigned char  last_moved);



    /*
     * ring      : 00 - outer, 01 - middle, 11 - inner
     * rel_pos   : 0-7 as specified int board layout (board.h, left-upper corner = 0, clockwise)
     * occupation: 00 - none, 01 - player 1, 11 - player 2
     * last_moved: 0 or 1
    */

    unsigned char ring : 2, rel_pos : 3, occupation : 2, last_moved : 1;

};
