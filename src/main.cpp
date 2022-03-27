#include <iostream>
#include <vector>
#include "board.h"


// Test, if mills are identified correctly
bool mill_test(unsigned char ring, unsigned char rel_pos, bool verbose = false)
{
    // Out of range
    if(ring > 3 || rel_pos > 7) return true;
    
    Board b;
    if(rel_pos % 2 == 1)
    {
        b.positions[rel_pos].occupation = 1;
        b.positions[rel_pos+8%24].occupation = 1;
        b.positions[rel_pos+16%24].occupation = 1;
    }


    bool ret_val = b.pos_is_mill(b.positions[ring*8+rel_pos]);

    if(verbose)
    {
        b.print_board();
        std::cout << "Mühle mit " << (int)ring <<"."<< (int)rel_pos << "? " << (ret_val ? "Ja" : "Nein") << '\n';
    }

    return ret_val;
}


void mill_test_suite()
{
    std::vector<std::array<unsigned char, 2>> tests {{1, 1}, {2, 5}, {4, 4}};

    for(auto array : tests)
    {
        mill_test(array[0], array[1], true);
    }

}


int main()
{
    mill_test_suite();

    return 0;
}
