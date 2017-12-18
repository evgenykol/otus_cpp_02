#pragma once

#include <vector>
#include <string>
#include <cstdint>


std::vector<std::string> split(const std::string &str, char d);
std::uint32_t ip_to_int(std::vector<std::string> ip_str);
std::string ip_to_str(std::uint32_t ip_int);

/*template<typename Filter>
std::vector<std::uint32_t> filter(std::vector<std::uint32_t> src, Filter flt);*/
