#include "byte_pattern.h"
#include <iostream>

int main(int argc, char **argv)
{
    byte_pattern pat;

    pat.find_pattern("    11   1 1? ?? ?   aa bb cc dd ee ff    ");
    std::cout << pat.has_size(9) << std::endl;

    return 0;
}
