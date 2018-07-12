#include "byte_pattern.h"
#include <iostream>

int main(int argc, char **argv)
{
    byte_pattern::start_log(L"test");
    byte_pattern pat;
    pat.find_pattern("    11   1 1? ?? ?   aa bb cc dd ee ff    ");
    std::cout << pat.count() << std::endl;

    return 0;
}
