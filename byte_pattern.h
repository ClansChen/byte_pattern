﻿//Core code from Hooking.Patterns
//https://github.com/ThirteenAG/Hooking.Patterns

#pragma once
#include <Windows.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <chrono>
#include <filesystem>
#include <fstream>

class memory_pointer
{
public:
    memory_pointer() :_address(0) {}
    memory_pointer(const void* pointer) :_address(reinterpret_cast<std::intptr_t>(pointer)) {}
    explicit memory_pointer(std::intptr_t address) :_address(address) {}

    template <typename T = void>
    T* p(std::intptr_t offset = 0) const
    {
        return reinterpret_cast<T*>(i(offset));
    }

    std::intptr_t i(std::intptr_t offset = 0) const
    {
        return (_address + offset);
    }

    memory_pointer& operator=(const void* pointer)
    {
        _address = reinterpret_cast<std::intptr_t>(pointer);
        return *this;
    }

    memory_pointer& operator=(std::intptr_t address)
    {
        _address = address;
        return *this;
    }

    template <typename T>
    operator T* () const
    {
        return p<T>();
    }

    operator std::intptr_t() const
    {
        return _address;
    }

private:
    std::intptr_t _address;
};

class byte_pattern
{
    std::pair<std::intptr_t, std::intptr_t> _range;
    std::vector<std::uint8_t> _pattern;
    std::vector<std::uint8_t> _mask;
    std::vector<memory_pointer> _results;
    double _spent;
    std::string _literal;

    std::ptrdiff_t _bmbc[256];

    static std::ofstream& log_stream();

    static std::vector<std::string> split_pattern(const char* literal);
    static std::pair<uint8_t, uint8_t> parse_sub_pattern(const std::string& sub);
    void transform_pattern(const char* literal);

    void get_module_range(memory_pointer module);

    void bm_preprocess();
    void bm_search();

    static std::string make_bytes_literal(memory_pointer pointer, std::size_t length);
    void debug_output() const;

public:
    static void start_log(const wchar_t* log_name);
    static void shutdown_log();

    byte_pattern();

    byte_pattern& set_pattern(const char* pattern_literal);
    byte_pattern& set_pattern(const void* pattern_binary, std::size_t size);

    byte_pattern& reset_module();
    byte_pattern& set_module(memory_pointer module);
    byte_pattern& set_range(memory_pointer beg, memory_pointer end);

    byte_pattern& search();

    byte_pattern& find_pattern(const char* pattern_literal);
    byte_pattern& find_pattern(const void* pattern_binary, std::size_t size);

    memory_pointer get(std::size_t index) const;
    std::vector<memory_pointer> get() const;
    memory_pointer get_first() const;

    std::size_t count() const;
    bool has_size(std::size_t expected) const;
    bool empty() const;
    void clear();

    template <typename Fn>
    void for_each_result(Fn fn) const
    {
        for (memory_pointer p : this->_results)
        {
            fn(p);
        }
    }
};
