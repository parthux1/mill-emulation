#include <iostream>
#include <vector>
#include "board.h"
#include "tests.h"



int main()
{
    std::cout << "executing\n";
    tests::size_check();
    tests::mill_detection(5, true);
    return 0;
}
