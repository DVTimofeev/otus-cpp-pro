#include "ip_filter.h"

#include <exception>
#include <iostream>

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

std::vector<int> parse_ip(const std::vector<std::string>& ip)
{
    std::vector<int> res;
    for (const auto& num_str :ip)
    {
        unsigned int num_int = std::stoi(num_str);
        if (num_int > 255)
			throw std::invalid_argument("Incorrect IP address " + num_str);
        res.push_back(std::move(num_int));
    }
    return res;
}

void print_ips(const std::vector<std::vector<int>> & ip_pool)
{
    for (const auto& ip : ip_pool)
    {
        for (size_t i = 0; i < ip.size(); ++i)
        {
            if (i > 0)
                std::cout << ".";

            std::cout << ip[i];

        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> filter_1st_byte(const std::vector<std::vector<int>> & ip_pool, int byte)
{
    std::vector<std::vector<int>> res;
    for (const auto& ip : ip_pool)
    {
        if (ip[0] == byte)
            res.emplace_back(ip);
    }
    return res;
}

std::vector<std::vector<int>> filter_1st_2nd_byte(const std::vector<std::vector<int>> & ip_pool, int byte1, int byte2)
{
    std::vector<std::vector<int>> res;
    for (const auto& ip : ip_pool)
    {
        if (ip[0] == byte1 && ip[1] == byte2)
            res.emplace_back(ip);
    }
    return res;
}

std::vector<std::vector<int>> filter_any_byte(const std::vector<std::vector<int>> & ip_pool, int byte_)
{
    std::vector<std::vector<int>> res;
    for (const auto& ip : ip_pool)
    {
        for (const auto& byte : ip)
            if (byte == byte_)
            {
                res.emplace_back(ip);
                break;
            }
    }
    return res;
}