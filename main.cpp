#include "lib.h"

#include <iostream>
#include <vector>
#include <list>


template <typename T>
struct is_cont 
{
	static const bool value = false;
};

template <typename T, typename Alloc>
struct is_cont<std::vector<T,Alloc>> 
{
	static const bool value = true;
};

template <typename T, typename Alloc>
struct is_cont<std::list<T,Alloc>> 
{
	static const bool value = true;
};

template <typename T>
typename std::enable_if_t<std::is_integral_v<T>>
print_ip(T&& ip)
{
	uint8_t ip_arr[sizeof(ip)];
	auto size = sizeof(ip);
	uint8_t mask = 255;
	for (int i = size - 1; i >= 0; --i)
	{
		ip_arr[i] = ip & mask;
		ip = ip >> 8;
	}
	for (size_t i = 0; i < size - 1; ++i)
	{
		std::cout << std::to_string(ip_arr[i]) << '.';
	}
		std::cout << std::to_string(ip_arr[size - 1]) << std::endl;
}

template <typename T>
typename std::enable_if_t<std::is_same_v<T,std::string>>
print_ip(T&& ip)
{
    std::cout << ip << std::endl;
	// return "";
}

template <typename T>
typename std::enable_if_t<is_cont<T>::value>
print_ip(T&& ip)
{
	std::string msg;
	for (const auto& d : ip)
	{
		msg.append(std::to_string(d));
		msg.append(".");
		// std::cout << d << std::endl;

	}
	msg.pop_back();

    std::cout << msg << std::endl;
}


int main(int, char **) {

	// print_ip<std::string&>("alksdjalksdjalkjds");
	// std::cout << std::is_integral_v<uint64_t> << std::endl;
	print_ip( int8_t{-1} ); // 255
	print_ip( int16_t{0} ); // 0.0
	print_ip( int32_t{2130706433} ); // 127.0.0.1
	print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
	print_ip( std::string{"Hello, World!"} ); // Hello, World!
	print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
	print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
	// print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0

	// struct X { void f() {} };
    // X x;
    // X& rx = x;
    // test(x, &X::f);  // (1)
    // test(rx, &X::f); // (1), creates a copy of x
    // test(&x, &X::f); // (2)
    // test(42, 1337);  // (3)
	return 0;
}
