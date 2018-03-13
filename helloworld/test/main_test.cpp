#include "hw.hpp"

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE hw_tests

BOOST_AUTO_TEST_CASE(version_test)
{
	BOOST_REQUIRE(version() > "0.0.0");
}
