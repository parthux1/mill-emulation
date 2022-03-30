#include "position.h"

Position::Position()
{
    ring = 0;
    rel_pos = 0;
    occupation = 0;
    last_moved = 0;
}

Position::Position(unsigned char byte)
{
    //TODO: implement (see .h)
}

Position::Position(unsigned char ring, unsigned char rel_pos, unsigned char occupation, unsigned char last_moved)
{
    ring = ring;
    rel_pos = rel_pos;
    occupation = occupation;
    last_moved = last_moved;
}

