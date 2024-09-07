#pragma once
#include <vector>
#include <string>

std::vector<std::string> split(const std::string &str, char d);
std::vector<int> parse_ip(const std::vector<std::string>& ip);
void print_ips(const std::vector<std::vector<int>> & ip_pool);
std::vector<std::vector<int>> filter_1st_byte(const std::vector<std::vector<int>> & ip_pool, int byte);
std::vector<std::vector<int>> filter_1st_2nd_byte(const std::vector<std::vector<int>> & ip_pool, int byte1, int byte2);
std::vector<std::vector<int>> filter_any_byte(const std::vector<std::vector<int>> & ip_pool, int byte_);
