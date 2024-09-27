#define BOOST_TEST_MODULE test_MyMap

#include "MyMap.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_MyMap)

BOOST_AUTO_TEST_CASE(test_emplace_key_value) {
	MyMap<int, int> my_map;
    my_map.emplace(1,1);
	BOOST_CHECK(my_map.size() == 1);
}

BOOST_AUTO_TEST_CASE(test_get_value) {
    MyMap<int, int> my_map;
    my_map.emplace(1,65);
	BOOST_CHECK(my_map.at(1) == 65);
}

BOOST_AUTO_TEST_CASE(test_change_value) {
    MyMap<int, int> my_map;
    my_map.emplace(1,65);
    my_map.emplace(1,38);
	BOOST_CHECK(my_map.at(1) == 38);
}

BOOST_AUTO_TEST_CASE(test_out_of_range) {
    try
    {
        MyMap<int, int> my_map;
    }
    catch(const std::out_of_range& e)
    {
        BOOST_CHECK(true);
    }
    catch (...){}

    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_SUITE_END()
