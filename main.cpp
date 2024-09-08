#include "ip_filter.h"
#include <exception>
#include <iostream>
#include <algorithm>

namespace
{
bool comp(std::vector<int> left,std::vector<int> right)
{
    for (size_t i = 0; i < left.size(); ++i)
    {
        if (left[i] > right[i])
            return true;
        else if (left[i] < right[i])
            return false;
    }
    return false;
}
} //namespace

int main()
{
    try
    {
        std::vector<std::vector<int>> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(parse_ip(split(v.at(0), '.')));
        }

        // reverse lexicographically sort
		std::sort(ip_pool.begin(), ip_pool.end(), comp); 

		print_ips(ip_pool);
        print_ips(filter_1st_byte(ip_pool, 1));
        print_ips(filter_1st_2nd_byte(ip_pool, 46, 70));
        print_ips(filter_any_byte(ip_pool, 46));
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
