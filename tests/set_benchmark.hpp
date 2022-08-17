/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_benchmark.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:24:11 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/17 08:44:56 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_BENCHMARK_HPP
# define SET_BENCHMARK_HPP

#include "utils_benchmark.hpp"
#include "tests.hpp"
#include "set.hpp"
#include <set>
#include <unistd.h>

template<class Set>
void	size_setTest(Set& set, Set& set2)
{
	typename Set::size_type s = set.size();
	(void) s;
	(void) set2;
}

template<class Set>
void	empty_setTest(Set& set, Set& set2)
{
	typename Set::size_type s = set.empty();
	(void) s;
	(void) set2;
}

template<class Set>
void	max_size_setTest(Set& set, Set& set2)
{
	typename Set::size_type s = set.max_size();
	(void) s;
	(void) set2;
}

template<class Set>
void	begin_setTest(Set& set, Set& set2)
{
	typename Set::iterator it = set.begin();
	typename Set::iterator it2 = set2.begin();
	(void) it;
	(void) it2;
}

template<class Set>
void	end_setTest(Set& set, Set& set2)
{
	typename Set::iterator it = set.end();
	typename Set::iterator it2 = set2.end();
	(void) it;
	(void) it2;
}

template<class Set>
void	rbegin_setTest(Set& set, Set& set2)
{
	typename Set::reverse_iterator it = set.rbegin();
	typename Set::reverse_iterator it2 = set2.rbegin();
	(void) it;
	(void) it2;
}

template<class Set>
void	rend_setTest(Set& set, Set& set2)
{
	typename Set::reverse_iterator it = set.rend();
	typename Set::reverse_iterator it2 = set2.rend();
	(void) it;
	(void) it2;
}

template<class Set>
void	clear_setTest(Set& set, Set& set2)
{
	set.clear();
	set2.clear();
}

template<class Set>
void	insertVal_setTest(Set& set, Set& set2)
{
	Set	tmp, tmp2;
	for (typename Set::iterator it = set.begin(); it != set.end(); it++)
		tmp.insert(*it);
	for (typename Set::iterator it = set2.begin(); it != set2.end(); it++)
		tmp2.insert(*it);
}

template<class Set>
void	insertRange_setTest(Set& set, Set& set2)
{
	Set	tmp, tmp2;

	tmp.insert(set.begin(), set.end());
	tmp2.insert(set2.begin(), set2.end());
}

// template<class Set>
// void	insertHint_setTest(Set& set, Set& set2)
// {
// 	Set	tmp, tmp2;

// 	for (typename Set::iterator it = set2.begin(); it != set2.end(); it++)
// 	{
// 		set.insert(set.)
// 	}
	
// }

template<class Set>
void	erasePos_setTest(Set& set, Set& set2)
{
	while (set.size())
		set.erase(set.begin());
	while (set2.size())
		set2.erase(set2.begin());
}

template<class Set>
void	eraseVal_setTest(Set& set, Set& set2)
{
	while (set.size())
		set.erase((*set.begin()));
	while (set2.size())
		set2.erase((*set2.begin()));
}

template<class Set>
void	eraseRange_setTest(Set& set, Set& set2)
{
	set.erase(set.begin(), ++set.begin());
	set.erase(set.begin(), --set.end());
	set2.erase(set2.begin(), ++set2.begin());
	set2.erase(set2.begin(), --set2.end());
}

template<class Set>
void	swap_setTest(Set& set, Set& set2)
{
	set.swap(set2);
}

template<class Set>
void	count_setTest(Set& set, Set& set2)
{
	for (typename Set::iterator it = set.begin(); it != set.end(); it++)
		set.count((*it));
	for (typename Set::iterator it = set2.begin(); it != set2.end(); it++)
		set2.count((*it));
}

template<class Set>
void	find_setTest(Set& set, Set& set2)
{
	for (typename Set::iterator it = set.begin(); it != set.end(); it++)
		set.find((*it));
	for (typename Set::iterator it = set2.begin(); it != set2.end(); it++)
		set2.find((*it));
}

template<class Set>
void	lower_bound_setTest(Set& set, Set& set2)
{
	for (typename Set::iterator it = set.begin(); it != set.end(); it++)
		set.lower_bound((*it));
	for (typename Set::iterator it = set2.begin(); it != set2.end(); it++)
		set2.lower_bound((*it));
}

template<class Set>
void	upper_bound_setTest(Set& set, Set& set2)
{
	for (typename Set::iterator it = set.begin(); it != set.end(); it++)
		set.upper_bound((*it));
	for (typename Set::iterator it = set2.begin(); it != set2.end(); it++)
		set2.upper_bound((*it));
}

template<class Set>
void	equal_range_setTest(Set& set, Set& set2)
{
	for (typename Set::iterator it = set.begin(); it != set.end(); it++)
		set.equal_range((*it));
	for (typename Set::iterator it = set2.begin(); it != set2.end(); it++)
		set2.equal_range((*it));
}

template<class Set>
std::list<typename Set::value_type>	constructList(typename Set::key_type* vTab, size_t size)
{
	std::list<typename Set::key_type> lst;

	for (size_t i = 0; i < size; i++)
		lst.push_back(typename Set::key_type(vTab[i]));
	return lst;
}

template <class Set>
void	fullSetTest(typename Set::key_type* vTab, size_t size,
					typename Set::key_type* vTab2, size_t size2)
{
	std::list<typename Set::key_type> lst = constructList<Set>(vTab, size);
	std::list<typename Set::key_type> lst2 = constructList<Set>(vTab2, size2);

	Set	set(lst.begin(), lst.end());
	Set	set2(lst2.begin(), lst2.end());

	/* Capacity */
	containerBenchmark(set, set2, size_setTest<Set>, "set::size");
	containerBenchmark(set, set2, empty_setTest<Set>, "set::empty");
	containerBenchmark(set, set2, max_size_setTest<Set>, "set::max_size");

	/* Iterator */
	containerBenchmark(set, set2, begin_setTest<Set>, "set::begin");
	containerBenchmark(set, set2, end_setTest<Set>, "set::end");
	containerBenchmark(set, set2, rbegin_setTest<Set>, "set::rbegin");
	containerBenchmark(set, set2, rend_setTest<Set>, "set::rend");

	/* Modifiers */
	containerBenchmark(set, set2, clear_setTest<Set>, "set::clear");
	containerBenchmark(set, set2, insertVal_setTest<Set>, "set::insert(val)");
	containerBenchmark(set, set2, insertRange_setTest<Set>, "set::insert(first, last)");
	// containerBenchmark(set, set2, insertHint_setTest<Set>, "set::insert(hint, value)");
	containerBenchmark(set, set2, eraseVal_setTest<Set>, "set::erase(key)");
	containerBenchmark(set, set2, erasePos_setTest<Set>, "set::erase(pos)");
	containerBenchmark(set, set2, eraseRange_setTest<Set>, "set::erase(first, last)");
	containerBenchmark(set, set2, swap_setTest<Set>, "set::swap");

	/* LookUp */
	containerBenchmark(set, set2, count_setTest<Set>, "set::count");
	containerBenchmark(set, set2, find_setTest<Set>, "set::find");
	containerBenchmark(set, set2, lower_bound_setTest<Set>, "set::lower_bound");
	containerBenchmark(set, set2, upper_bound_setTest<Set>, "set::upper_bound");
	containerBenchmark(set, set2, equal_range_setTest<Set>, "set::equal_range");
}

template <typename T>
void	fullBothSetTest(T* vTab, size_t size, T* vTab2, size_t size2)
{
	std::cout << STR_MAGENTA << "Test" << std::setw(46) << "ft Time" << std::setw(13)
			  << "std Time" << std::setw(10) << "Ratio" << STR_RESET << std::endl;

	std::list<typename std::set<T>::value_type> lst = constructList<std::set<T> >(vTab, size);
	std::list<typename std::set<T>::value_type> lst2 = constructList<std::set<T> >(vTab2, size2);
	std::list<typename ft::set<T>::value_type> lft = constructList<ft::set<T> >(vTab, size);
	std::list<typename ft::set<T>::value_type> lft2 = constructList<ft::set<T> >(vTab2, size2);

	std::set<T>	stdm(lst.begin(), lst.end());
	std::set<T>	stdm2(lst2.begin(), lst2.end());
	ft::set<T>	ftm(lft.begin(), lft.end());
	ft::set<T>	ftm2(lft2.begin(), lft2.end());

	/* Capacity */
	std::cout << std::setfill('-') << std::setw(73) << std::left << "Capacity" << std::setfill(' ') << std::endl;
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, size_setTest<std::set<T> >, size_setTest<ft::set<T> >, "set::size");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, empty_setTest<std::set<T> >, empty_setTest<ft::set<T> >, "set::empty");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, max_size_setTest<std::set<T> >, max_size_setTest<ft::set<T> >, "set::max_size");

	/* Iterator */
	std::cout << std::setfill('-') << std::setw(73) << std::left << "Iterator" << std::setfill(' ') << std::endl;
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, begin_setTest<std::set<T> >, begin_setTest<ft::set<T> >, "set::begin");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, end_setTest<std::set<T> >, end_setTest<ft::set<T> >, "set::end");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, rbegin_setTest<std::set<T> >, rbegin_setTest<ft::set<T> >, "set::rbegin");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, rend_setTest<std::set<T> >, rend_setTest<ft::set<T> >, "set::rend");

	/* Modifiers */
	std::cout << std::setfill('-') << std::setw(73) << std::left << "Modifiers" << std::setfill(' ') << std::endl;
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, clear_setTest<std::set<T> >, clear_setTest<ft::set<T> >, "set::clear");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, insertVal_setTest<std::set<T> >, insertVal_setTest<ft::set<T> >, "set::insert(val)");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, insertRange_setTest<std::set<T> >, insertRange_setTest<ft::set<T> >, "set::insert(first, last)");
	// containerCompareBenchmark(stdm, stdm2, ftm, ftm2, insertHint_setTest<std::set<T> >, insertHint_setTest<ft::set<T> >, "set::insert(hint, value)");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, eraseVal_setTest<std::set<T> >, eraseVal_setTest<ft::set<T> >, "set::erase(key)");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, erasePos_setTest<std::set<T> >, erasePos_setTest<ft::set<T> >, "set::erase(pos)");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, eraseRange_setTest<std::set<T> >, eraseRange_setTest<ft::set<T> >, "set::erase(first, last)");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, swap_setTest<std::set<T> >, swap_setTest<ft::set<T> >, "set::swap");

	/* LookUp */
	std::cout << std::setfill('-') << std::setw(73) << std::left << "LookUp" << std::setfill(' ') << std::endl;
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, count_setTest<std::set<T> >, count_setTest<ft::set<T> >, "set::count");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, find_setTest<std::set<T> >, find_setTest<ft::set<T> >, "set::find");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, lower_bound_setTest<std::set<T> >, lower_bound_setTest<ft::set<T> >, "set::lower_bound");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, upper_bound_setTest<std::set<T> >, upper_bound_setTest<ft::set<T> >, "set::upper_bound");
	containerCompareBenchmark(stdm, stdm2, ftm, ftm2, equal_range_setTest<std::set<T> >, equal_range_setTest<ft::set<T> >, "set::equal_range");
	std::cout << std::endl;
}
#endif