/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_benchmark.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:24:11 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/16 04:09:08 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_BENCHMARK_HPP
# define MAP_BENCHMARK_HPP

#include "utils_benchmark.hpp"
#include "tests.hpp"
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



#endif