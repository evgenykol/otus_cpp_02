#include "ip_filter.h"

#define BOOST_TEST_MODULE ip_filter_tests

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(split_suite)

BOOST_AUTO_TEST_CASE(check_split)
{
    // ("",  '.') -> [""]
    // ("11", '.') -> ["11"]
    // ("..", '.') -> ["", "", ""]
    // ("11.", '.') -> ["11", ""]
    // (".11", '.') -> ["", "11"]
    // ("11.22", '.') -> ["11", "22"]
    //std::vector<std::string> split(const std::string &str, char d)

    std::vector<std::string> v1 = split("",  '.');
    BOOST_CHECK(v1.size() == 1);
    BOOST_CHECK(v1.at(0) == "");

    std::vector<std::string> v2 = split("11",  '.');
    BOOST_CHECK(v2.size() == 1);
    BOOST_CHECK(v2.at(0) == "11");

    std::vector<std::string> v3 = split("..", '.');
    BOOST_CHECK(v3.size() == 3);
    BOOST_CHECK(v3.at(0) == "");
    BOOST_CHECK(v3.at(1) == "");
    BOOST_CHECK(v3.at(2) == "");

    std::vector<std::string> v4 = split("11.", '.');
    BOOST_CHECK(v4.size() == 2);
    BOOST_CHECK(v4.at(0) == "11");
    BOOST_CHECK(v4.at(1) == "");

    std::vector<std::string> v5 = split(".11", '.');
    BOOST_CHECK(v5.size() == 2);
    BOOST_CHECK(v5.at(0) == "");
    BOOST_CHECK(v5.at(1) == "11");

    std::vector<std::string> v6 = split("11.22", '.');
    BOOST_CHECK(v6.size() == 2);
    BOOST_CHECK(v6.at(0) == "11");
    BOOST_CHECK(v6.at(1) == "22");
}

BOOST_AUTO_TEST_SUITE_END()
