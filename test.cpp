#include "byte_pattern.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>

int main(int argc, char **argv)
{
    std::vector<char> buffer;
    byte_pattern pat;
    std::ifstream ifs("libcef.dll", std::ios::binary);

    if (!ifs)
        return 0;

    buffer.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

    byte_pattern::start_log(L"test");
    pat.set_range(buffer.data(), buffer.data() + buffer.size());
    pat.set_pattern("This program cannot be run in DOS mode.", 39);
    pat.search();

    std::cout << pat.count() << std::endl;

    return 0;
}
