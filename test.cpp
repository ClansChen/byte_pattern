#include "byte_pattern.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>

int main(int argc, char **argv)
{
    std::vector<char> buffer;
    byte_pattern pat;
    std::ifstream ifs("gta-vc.bin", std::ios::binary);

    if (!ifs)
        return 0;

    buffer.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

    byte_pattern::start_log(L"test");

    pat.set_range(buffer.data(), buffer.data() + buffer.size());

    pat.find_pattern("8D 04 85 00 00 00 00 01 C8 83 C0 30");
    pat.find_pattern("8B 0C 8D ? ? ? ? 89 4C 95 30");
    pat.find_pattern("01 ? 83 C? 30");
    pat.find_pattern("89 ? ? 30");
    pat.find_pattern("01 71 70 01 71 74");

    byte_pattern::shutdown_log();

    return 0;
}
