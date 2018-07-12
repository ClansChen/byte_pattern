//Core code from Hooking.Patterns
//https://github.com/ThirteenAG/Hooking.Patterns

#pragma once
#include <windows.h>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <filesystem>
#include <functional>
#include <chrono>

class memory_pointer
{
    union
    {
        void *Pointer;
        std::uintptr_t Address;
    };

public:
    memory_pointer()
        :Pointer{}
    {

    }

    memory_pointer(void *p)
        : Pointer(p)
    {
    }

    memory_pointer(std::uintptr_t i)
        : Address(i)
    {
    }

    std::uintptr_t address(std::ptrdiff_t offset = 0) const
    {
        return (this->Address + offset);
    }

    template<typename T = void>
    T *pointer(std::ptrdiff_t offset = 0) const
    {
        return reinterpret_cast<T *>(this->address(offset));
    }

    operator std::uintptr_t() const
    {
        return this->address();
    }
};

class byte_pattern
{
    std::pair<std::uintptr_t, std::uintptr_t> _range;
    std::vector<std::uint8_t> _pattern;
    std::vector<std::uint8_t> _mask;
    std::vector<memory_pointer> _results;
    double _spent;
    std::string _literal;

    std::ptrdiff_t _bmbc[256];

    static std::ofstream &log_stream();

    static std::vector<std::string> split_pattern(const char *literal);
    std::pair<uint8_t, uint8_t> parse_sub_pattern(const std::string &sub);
    void transform_pattern(const char *literal);

    void get_module_range(memory_pointer module);

    void bm_preprocess();
    void bm_search();

    void debug_output() const;

public:
    static void start_log(const wchar_t *module_name);
    static void shutdown_log();

    byte_pattern();

    byte_pattern &set_pattern(const char *pattern_literal);
    byte_pattern &set_pattern(const std::uint8_t *pattern_binary, size_t size);

    byte_pattern &reset_module();
    byte_pattern &set_module(memory_pointer module);
    byte_pattern &set_range(memory_pointer beg, memory_pointer end);

    byte_pattern &search();

    byte_pattern &find_pattern(const char *pattern_literal);
    byte_pattern &find_pattern(const std::uint8_t *pattern_binary, size_t size);

    memory_pointer get(std::size_t index) const;
    memory_pointer get_first() const;

    std::size_t count() const;
    bool has_size(std::size_t expected) const;
    bool empty() const;
    void clear();

    void for_each_result(std::function<void(memory_pointer)> Pr) const;
};
