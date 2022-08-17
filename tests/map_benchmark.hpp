/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_benchmark.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:24:11 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/17 04:46:58 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_BENCHMARK_HPP
# define MAP_BENCHMARK_HPP

#include "utils_benchmark.hpp"
#include "tests.hpp"
#include "map.hpp"
#include <map>
#include <unistd.h>

template<class Map>
void	at_mapTest(Map& map, Map& map2)
{
	for (typename Map::iterator it = map.begin(); it != map.end(); it++)
		map.at((*it).first);
	for (typename Map::iterator it = map2.begin(); it != map2.end(); it++)
		map2.at((*it).first);
}

template<class Map>
void	brackets_mapTest(Map& map, Map& map2)
{
	for (typename Map::iterator it = map.begin(); it != map.end(); it++)
		map[(*it).first];
	for (typename Map::iterator it = map2.begin(); it != map2.end(); it++)
		map2[(*it).first];
}

template<class Map>
void	size_mapTest(Map& map, Map& map2)
{
	typename Map::size_type s = map.size();
	(void) s;
	(void) map2;
}

template<class Map>
void	empty_mapTest(Map& map, Map& map2)
{
	typename Map::size_type s = map.empty();
	(void) s;
	(void) map2;
}

template<class Map>
void	max_size_mapTest(Map& map, Map& map2)
{
	typename Map::size_type s = map.max_size();
	(void) s;
	(void) map2;
}

template<class Map>
void	begin_mapTest(Map& map, Map& map2)
{
	typename Map::iterator it = map.begin();
	typename Map::iterator it2 = map2.begin();
	(void) it;
	(void) it2;
}

template<class Map>
void	end_mapTest(Map& map, Map& map2)
{
	typename Map::iterator it = map.end();
	typename Map::iterator it2 = map2.end();
	(void) it;
	(void) it2;
}

template<class Map>
void	rbegin_mapTest(Map& map, Map& map2)
{
	typename Map::reverse_iterator it = map.rbegin();
	typename Map::reverse_iterator it2 = map2.rbegin();
	(void) it;
	(void) it2;
}

template<class Map>
void	rend_mapTest(Map& map, Map& map2)
{
	typename Map::reverse_iterator it = map.rend();
	typename Map::reverse_iterator it2 = map2.rend();
	(void) it;
	(void) it2;
}

template<class Map>
void	clear_mapTest(Map& map, Map& map2)
{
	map.clear();
	map2.clear();
}

template<class Map>
void	insertVal_mapTest(Map& map, Map& map2)
{
	Map	tmp, tmp2;
	for (typename Map::iterator it = map.begin(); it != map.end(); it++)
		tmp.insert(*it);
	for (typename Map::iterator it = map2.begin(); it != map2.end(); it++)
		tmp2.insert(*it);
}

template<class Map>
void	insertRange_mapTest(Map& map, Map& map2)
{
	Map	tmp, tmp2;

	tmp.insert(map.begin(), map.end());
	tmp2.insert(map2.begin(), map2.end());
}

// template<class Map>
// void	insertHint_mapTest(Map& map, Map& map2)
// {
// 	Map	tmp, tmp2;

// 	for (typename Map::iterator it = map2.begin(); it != map2.end(); it++)
// 	{
// 		map.insert(map.)
// 	}
	
// }

template<class Map>
void	erasePos_mapTest(Map& map, Map& map2)
{
	while (map.size())
		map.erase(map.begin());
	while (map2.size())
		map2.erase(map2.begin());
}

template<class Map>
void	eraseVal_mapTest(Map& map, Map& map2)
{
	while (map.size())
		map.erase((*map.begin()).first);
	while (map2.size())
		map2.erase((*map2.begin()).first);
}

template<class Map>
void	eraseRange_mapTest(Map& map, Map& map2)
{
	map.erase(map.begin(), ++map.begin());
	map.erase(map.begin(), --map.end());
	map2.erase(map2.begin(), ++map2.begin());
	map2.erase(map2.begin(), --map2.end());
}

template<class Map>
void	swap_mapTest(Map& map, Map& map2)
{
	map.swap(map2);
}

template<class Map>
void	count_mapTest(Map& map, Map& map2)
{
	for (typename Map::iterator it = map.begin(); it != map.end(); it++)
		map.count((*it).first);
	for (typename Map::iterator it = map2.begin(); it != map2.end(); it++)
		map2.count((*it).first);
}

template<class Map>
void	find_mapTest(Map& map, Map& map2)
{
	for (typename Map::iterator it = map.begin(); it != map.end(); it++)
		map.find((*it).first);
	for (typename Map::iterator it = map2.begin(); it != map2.end(); it++)
		map2.find((*it).first);
}

template<class Map>
void	lower_bound_mapTest(Map& map, Map& map2)
{
	for (typename Map::iterator it = map.begin(); it != map.end(); it++)
		map.lower_bound((*it).first);
	for (typename Map::iterator it = map2.begin(); it != map2.end(); it++)
		map2.lower_bound((*it).first);
}

template<class Map>
void	upper_bound_mapTest(Map& map, Map& map2)
{
	for (typename Map::iterator it = map.begin(); it != map.end(); it++)
		map.upper_bound((*it).first);
	for (typename Map::iterator it = map2.begin(); it != map2.end(); it++)
		map2.upper_bound((*it).first);
}

template<class Map>
void	equal_range_mapTest(Map& map, Map& map2)
{
	for (typename Map::iterator it = map.begin(); it != map.end(); it++)
		map.equal_range((*it).first);
	for (typename Map::iterator it = map2.begin(); it != map2.end(); it++)
		map2.equal_range((*it).first);
}

template<class Map>
std::list<typename Map::value_type>	constructList(typename Map::key_type* kTab, typename Map::mapped_type* vTab, size_t size)
{
	std::list<typename Map::value_type> lst;

	for (size_t i = 0; i < size; i++)
		lst.push_back(typename Map::value_type(kTab[i], vTab[i]));
	return lst;
}

template <class Map>
void	fullMapTest(typename Map::key_type* kTab, typename Map::mapped_type* vTab, size_t size,
					typename Map::key_type* kTab2, typename Map::mapped_type* vTab2, size_t size2)
{
	std::list<typename Map::value_type> lst = constructList<Map>(kTab, vTab, size);
	std::list<typename Map::value_type> lst2 = constructList<Map>(kTab2, vTab2, size2);

	Map	map(lst.begin(), lst.end());
	Map	map2(lst2.begin(), lst2.end());

	/* Element Access */
	containerBenchmark(map, map2, at_mapTest<Map>, "map::at");
	containerBenchmark(map, map2, brackets_mapTest<Map>, "map::[]");

	/* Capacity */
	containerBenchmark(map, map2, size_mapTest<Map>, "map::size");
	containerBenchmark(map, map2, empty_mapTest<Map>, "map::empty");
	containerBenchmark(map, map2, max_size_mapTest<Map>, "map::max_size");

	/* Iterator */
	containerBenchmark(map, map2, begin_mapTest<Map>, "map::begin");
	containerBenchmark(map, map2, end_mapTest<Map>, "map::end");
	containerBenchmark(map, map2, rbegin_mapTest<Map>, "map::rbegin");
	containerBenchmark(map, map2, rend_mapTest<Map>, "map::rend");

	/* Modifiers */
	containerBenchmark(map, map2, clear_mapTest<Map>, "map::clear");
	containerBenchmark(map, map2, insertVal_mapTest<Map>, "map::insert(val)");
	containerBenchmark(map, map2, insertRange_mapTest<Map>, "map::insert(first, last)");
	// containerBenchmark(map, map2, insertHint_mapTest<Map>, "map::insert(hint, value)");
	containerBenchmark(map, map2, eraseVal_mapTest<Map>, "map::erase(key)");
	containerBenchmark(map, map2, erasePos_mapTest<Map>, "map::erase(pos)");
	containerBenchmark(map, map2, eraseRange_mapTest<Map>, "map::erase(first, last)");
	containerBenchmark(map, map2, swap_mapTest<Map>, "map::swap");

	/* LookUp */
	containerBenchmark(map, map2, count_mapTest<Map>, "map::count");
	containerBenchmark(map, map2, find_mapTest<Map>, "map::find");
	containerBenchmark(map, map2, lower_bound_mapTest<Map>, "map::lower_bound");
	containerBenchmark(map, map2, upper_bound_mapTest<Map>, "map::upper_bound");
	containerBenchmark(map, map2, equal_range_mapTest<Map>, "map::equal_range");
}

template <typename K, typename T>
void	fullBothMapTest(K* kTab, T* vTab, size_t size, K* kTab2, T* vTab2, size_t size2)
{
	std::cout << STR_MAGENTA << "Test" << std::setw(46) << "ft Time" << std::setw(13)
			  << "std Time" << std::setw(10) << "Ratio" << STR_RESET << std::endl;

	std::list<typename std::map<K, T>::value_type> lst = constructList<std::map<K, T> >(kTab, vTab, size);
	std::list<typename std::map<K, T>::value_type> lst2 = constructList<std::map<K, T> >(kTab2, vTab2, size2);
	std::list<typename ft::map<K, T>::value_type> lft = constructList<ft::map<K, T> >(kTab, vTab, size);
	std::list<typename ft::map<K, T>::value_type> lft2 = constructList<ft::map<K, T> >(kTab2, vTab2, size2);

	std::map<K, T>	stdm(lst.begin(), lst.end());
	std::map<K, T>	stdm2(lst2.begin(), lst2.end());
	ft::map<K, T>	ftm(lft.begin(), lft.end());
	ft::map<K, T>	ftm2(lft2.begin(), lft2.end());

	/* Element Access */
	std::cout << std::setfill('-') << std::setw(73) << std::left << "Element Access" << std::setfill(' ') << std::endl;
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, at_mapTest<std::map<K, T> >, at_mapTest<ft::map<K, T> >, "map::at");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, brackets_mapTest<std::map<K, T> >, brackets_mapTest<ft::map<K, T> >, "map::[]");

	/* Capacity */
	std::cout << std::setfill('-') << std::setw(73) << std::left << "Capacity" << std::setfill(' ') << std::endl;
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, size_mapTest<std::map<K, T> >, size_mapTest<ft::map<K, T> >, "map::size");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, empty_mapTest<std::map<K, T> >, empty_mapTest<ft::map<K, T> >, "map::empty");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, max_size_mapTest<std::map<K, T> >, max_size_mapTest<ft::map<K, T> >, "map::max_size");

	/* Iterator */
	std::cout << std::setfill('-') << std::setw(73) << std::left << "Iterator" << std::setfill(' ') << std::endl;
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, begin_mapTest<std::map<K, T> >, begin_mapTest<ft::map<K, T> >, "map::begin");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, end_mapTest<std::map<K, T> >, end_mapTest<ft::map<K, T> >, "map::end");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, rbegin_mapTest<std::map<K, T> >, rbegin_mapTest<ft::map<K, T> >, "map::rbegin");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, rend_mapTest<std::map<K, T> >, rend_mapTest<ft::map<K, T> >, "map::rend");

	/* Modifiers */
	std::cout << std::setfill('-') << std::setw(73) << std::left << "Modifiers" << std::setfill(' ') << std::endl;
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, clear_mapTest<std::map<K, T> >, clear_mapTest<ft::map<K, T> >, "map::clear");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, insertVal_mapTest<std::map<K, T> >, insertVal_mapTest<ft::map<K, T> >, "map::insert(val)");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, insertRange_mapTest<std::map<K, T> >, insertRange_mapTest<ft::map<K, T> >, "map::insert(first, last)");
	// containerCompareBenchmark(stdm, stdm2, ftm, ftm2, insertHint_mapTest<std::map<K, T> >, insertHint_mapTest<ft::map<K, T> >, "map::insert(hint, value)");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, eraseVal_mapTest<std::map<K, T> >, eraseVal_mapTest<ft::map<K, T> >, "map::erase(key)");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, erasePos_mapTest<std::map<K, T> >, erasePos_mapTest<ft::map<K, T> >, "map::erase(pos)");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, eraseRange_mapTest<std::map<K, T> >, eraseRange_mapTest<ft::map<K, T> >, "map::erase(first, last)");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, swap_mapTest<std::map<K, T> >, swap_mapTest<ft::map<K, T> >, "map::swap");

	/* LookUp */
	std::cout << std::setfill('-') << std::setw(73) << std::left << "LookUp" << std::setfill(' ') << std::endl;
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, count_mapTest<std::map<K, T> >, count_mapTest<ft::map<K, T> >, "map::count");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, find_mapTest<std::map<K, T> >, find_mapTest<ft::map<K, T> >, "map::find");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, lower_bound_mapTest<std::map<K, T> >, lower_bound_mapTest<ft::map<K, T> >, "map::lower_bound");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, upper_bound_mapTest<std::map<K, T> >, upper_bound_mapTest<ft::map<K, T> >, "map::upper_bound");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, equal_range_mapTest<std::map<K, T> >, equal_range_mapTest<ft::map<K, T> >, "map::equal_range");
	std::cout << std::endl;
}
#endif