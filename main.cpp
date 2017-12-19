#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <tuple>
#include <algorithm>

#include "ip_filter.h"

void print_ips(std::vector<std::uint32_t> &ip)
{
    for(auto i : ip)
    {
        std::cout << ip_to_str(i) << std::endl;
    }
}


int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::uint32_t> ip_pool;

#ifdef NDEBUG
        for(std::string line; std::getline(std::cin, line);)
#else
        std::fstream f;
        f.open("ip_filter.tsv", std::fstream::in);

        if (!f.is_open())
        {
            std::cout << "File opening error" << std::endl;
        }

        for(std::string line; std::getline(f, line);)
#endif
        {
            std::vector<std::string> v = split(line, '\t');
            auto ip = ip_to_int(split(v.at(0), '.'));
            ip_pool.push_back(ip);
        }

        //reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<std::uint32_t>());

        print_ips(ip_pool);

        auto filter_by_first = [](const std::uint32_t &ip)
        {
            return ((ip & 0xFF000000) == 0x01000000);
        };
        auto v1 = filter(ip_pool, filter_by_first);
        print_ips(v1);

        auto filter_by_first_and_second = [](const std::uint32_t &ip)
        {
            return ((ip & 0xFFFF0000) == 0x2e460000);
        };
        auto v2 = filter(ip_pool, filter_by_first_and_second);
        print_ips(v2);

        auto filter_by_any = [](const std::uint32_t &ip)
        {
            return ((ip & 0xFF000000) == 0x2e000000) ||
                   ((ip & 0xFF0000) == 0x2e0000) ||
                   ((ip & 0xFF00) == 0x2e00) ||
                   ((ip & 0xFF) == 0x2e);
        };
        auto v3 = filter(ip_pool, filter_by_any);
        print_ips(v3);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
