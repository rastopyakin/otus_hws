#include "ip_filter.hpp"

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE ip_filter_tests

BOOST_AUTO_TEST_CASE(split_test)
{
    BOOST_REQUIRE(
	split(std::string{""}, '.') == std::vector<std::string>{""});
    BOOST_REQUIRE(
	split(std::string{"11"}, '.') == std::vector<std::string>{"11"});
    BOOST_REQUIRE(
	split(std::string{".."}, '.') == std::vector<std::string>({"", "", ""}));
    BOOST_REQUIRE(
	split(std::string{"11."}, '.') == std::vector<std::string>({"11", ""}));
    BOOST_REQUIRE(
	split(std::string{".11"}, '.') == std::vector<std::string>({"", "11"}));
    BOOST_REQUIRE(
	split(std::string{"11.22"}, '.') == std::vector<std::string>({"11", "22"}));
}

BOOST_AUTO_TEST_CASE(match_test)
{
    BOOST_REQUIRE(match(ip_t({2, 0, 3}), 2));
    BOOST_REQUIRE(!match(ip_t({1, 2, 3}), 2));
    BOOST_REQUIRE(match(ip_t({1, 2, 3}), 1, 2));
    BOOST_REQUIRE(match(ip_t({1, 2, 3}), 1, 2));
    BOOST_REQUIRE(!match(ip_t({0, 2, 3}), 1, 2));
}

BOOST_AUTO_TEST_CASE(str2ip_test)
{
    BOOST_REQUIRE(str2ip("1.2.3.4") == ip_t({1, 2, 3, 4}));
}
