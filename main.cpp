#include "custom_allocator.h"

#include <iostream>
#include <map>
#include <boost/math/special_functions/factorials.hpp>

// + создание экземпляра std::map<int, int>
// + заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
// + создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10 элементами
// + заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
// + вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
// - создание экземпляра своего контейнера для хранения значений типа int
// - заполнение 10 элементами от 0 до 9
// - создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,
// ограниченным 10 элементами
// - заполнение 10 элементами от 0 до 9
// - вывод на экран всех значений, хранящихся в контейнере


void fillMap(std::map<int,int> & map_)
{
	for (size_t i = 0; i < 10; ++i)
		map_.emplace(i, boost::math::factorial<double>(i));
}

void printMap(const std::map<int, int> & map_, const std::string & name)
{
	std::cout << "--==--==--==--" << std::endl;
	std::cout << name << std::endl;
	for (size_t i = 0; i < 10; ++i)
		std::cout<< "Key: " << i << ", value: " << map_.at(i) << std::endl;
}

int main(int, char **) 
{
	// std::map<int,int> map_without_alloc;
	// fillMap(map_without_alloc);
	// printMap(map_without_alloc, "Without custom alloc");
	{
		std::map<int, int, std::less<int>, otus::alloc<std::pair<const int, int>>> map_with_alloc;
		for (size_t i = 0; i < 10; ++i)
			map_with_alloc.emplace(i, boost::math::factorial<double>(i));

		std::cout << "--==--==--==--" << std::endl;
		std::cout << "With custom alloc" << std::endl;
		for (size_t i = 0; i < 10; ++i)
			std::cout<< "Key: " << i << ", value: " << map_with_alloc.at(i) << std::endl;
		std::cout << "end" << std::endl;
	}
	std::cout << "end2" << std::endl;
	// fillMap(map_with_alloc);
	// printMap(map_with_alloc, "With custom alloc");
	return 0;
}
