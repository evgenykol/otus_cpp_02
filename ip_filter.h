#pragma once

#include <vector>
#include <string>
#include <cstdint>

std::vector<std::string> split(const std::string &str, char d);
std::uint32_t ip_to_int(std::vector<std::string> ip_str);
std::string ip_to_str(std::uint32_t ip_int);

template <typename T>
auto filter(std::vector<std::uint32_t> ip_pool, T filt)
{
    decltype(ip_pool) filtered;

    for(auto ip : ip_pool)
    {
        if(filt(ip))
        {
            filtered.push_back(ip);
        }
    }
    return filtered;
}
