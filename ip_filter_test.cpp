#define BOOST_TEST_MODULE ip_filter_test

#include "ip_filter.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ip_filter_test)

BOOST_AUTO_TEST_CASE(split_test) 
{
	std::vector<std::string> ref = {"1111", "2222", "3333", "4444"};
	std::string s = "1111\t2222\t3333\t4444";

	BOOST_CHECK(split(s,'\t') == ref);
}

BOOST_AUTO_TEST_CASE(split_test2) 
{
	std::vector<std::string> ref = {"11", "22", "33", "44"};
	std::string s = "11.22.33.44";

	BOOST_CHECK(split(s,'.') == ref);
}

BOOST_AUTO_TEST_CASE(parse_ip_test) 
{
	std::vector<int> ref = {11,22,33,44};
	auto res = parse_ip({"11", "22", "33", "44"});

	BOOST_CHECK(res == ref);
}

BOOST_AUTO_TEST_CASE(parse_ip_exception_test) 
{
	std::string ref = "Incorrect IP address 4444";
	std::string res = "";
	try 
	{
		parse_ip({"11", "22", "33", "4444"});
	}

	catch(const std::exception &e)
    {
        res = e.what();
    }

	BOOST_CHECK(res == ref);
}


BOOST_AUTO_TEST_CASE(filter_1st_byte_test) 
{
	std::vector<std::vector<int>> ip_pool = {
		{185,182,81,131},
		{68,45,152,8},
		{114,221,179,117},
		{185,89,100,249},
		{24,70,113,73},
		{188,68,0,38},
		{119,42,115,97},
		{194,106,108,214},
		{24,210,239,177},
		{166,88,193,116},
		{62,205,202,214},
		{188,166,87,191},
		{103,62,147,2},
		{95,181,177,197},
		{95,181,177,197},
		{149,107,0,27},
	};
	std::vector<std::vector<int>> ref = {
		{24,70,113,73},
		{24,210,239,177}
	};
	auto res = filter_1st_byte(ip_pool, 24);
	BOOST_CHECK(res == ref);
}

BOOST_AUTO_TEST_CASE(ffilter_1st_2nd_byte_test) 
{
	std::vector<std::vector<int>> ip_pool = {
		{185,182,81,131},
		{68,45,152,8},
		{114,221,179,117},
		{185,89,100,249},
		{24,70,113,73},
		{188,68,0,38},
		{119,42,115,97},
		{194,106,108,214},
		{24,210,239,177},
		{166,88,193,116},
		{62,205,202,214},
		{188,166,87,191},
		{103,62,147,2},
		{95,181,177,197},
		{95,181,177,197},
		{149,107,0,27},
	};
	std::vector<std::vector<int>> ref = {
		{24,70,113,73},
	};
	auto res = filter_1st_2nd_byte(ip_pool, 24,70);
	BOOST_CHECK(res == ref);
}

BOOST_AUTO_TEST_CASE(filter_any_byte_test) 
{
	std::vector<std::vector<int>> ip_pool = {
		{185,182,81,131},
		{68,45,152,8},
		{114,221,179,117},
		{185,89,100,249},
		{24,70,113,73},
		{188,68,0,38},
		{119,42,24,97},
		{194,106,108,214},
		{24,210,239,177},
		{166,88,193,116},
		{62,205,202,214},
		{188,166,87,191},
		{103,62,147,2},
		{95,181,177,197},
		{95,181,177,197},
		{149,107,0,24},
	};
	std::vector<std::vector<int>> ref = {
		{24,70,113,73},
		{119,42,24,97},
		{24,210,239,177},
		{149,107,0,24}
	};
	auto res = filter_any_byte(ip_pool, 24);
	BOOST_CHECK(res == ref);
}

BOOST_AUTO_TEST_SUITE_END()
