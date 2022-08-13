/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:25:28 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/13 23:17:43 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TESTS_HPP
# define MAP_TESTS_HPP

#include "tests.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <list>
#include <map>
#include <utility>
#include "map.hpp"
#include "utility.hpp"

#define STDMAP std::map<K, T>
#define FTMAP ft::map<K, T>

template <typename K, typename T>
bool mapEqual(const ft::map<K, T>& mft, const std::map<K, T>& mstd)
{
	if (mft.size() != mstd.size())
		return false;

	typename ft::map<K, T>::const_iterator ift = mft.begin();
	typename std::map<K, T>::const_iterator istd = mstd.begin();

	for (typename std::map<K, T>::const_iterator it = mstd.begin() ; it != mstd.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	while (ift != mft.end() && istd != mstd.end())
	{
		if ((*istd).first != (*ift).first || (*istd).second != (*ift).second)
			return false;
		ift++;
		istd++;
	}
	return true;
}

template<typename K, typename T, class map>
map	constructMap(const K* ktab, const T* vtab, size_t size)
{
	map m;
	for (size_t i = 0; i < size; i++)
		m.insert(typename map::value_type(ktab[i], vtab[i]));
	return m;
}

template< class T1, class T2 >
std::ostream &operator<<(std::ostream &os, const std::pair<T1,T2>& rhs )
{
	os << "(" << rhs.first << ", " << rhs.second << ")";
	return os;
}

template <class M>
void	print(const M& m)
{
	for (typename M::const_iterator i = m.begin(); i != m.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	std::cout << "size    :" << m.size() << std::endl;
	std::cout << "empty   :" << m.empty() << std::endl;
	std::cout << "maxSize :" << m.max_size() << std::endl;
}

template <typename K, typename T>
void printMaps(const STDMAP& stdm, const FTMAP& ftm)
{
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "ft  : ";
	print(ftm);
	std::cout << "std : ";
	print(stdm);
	std::cout << "--------------------------------------------------" << std::endl;
}

void	printTest(std::string str, bool ok)
{
	std::cout << std::setw(30) << STR_BLUE + str + ":" << (ok ? OK : NOTOK) << STR_RESET << std::endl;
}

template <typename K, typename T>
void capacityTest(const K* ktab, const T* vtab, size_t size)
{
	FTMAP				ftmap;
	STDMAP				stdmap;
	bool				isSizeOk = true;
	bool				isEmptyOk = true;
	bool				isMaxSizeOk = true;
	typename FTMAP::size_type	ftMax = ftmap.max_size();
	typename STDMAP::size_type	stdMax = stdmap.max_size();

	for (size_t i = 0; i < size && isSizeOk && isEmptyOk && isMaxSizeOk; i++)
	{
		stdmap.insert(std::pair<K, T>(ktab[i], vtab[i]));
		ftmap.insert(ft::pair<K, T>(ktab[i], vtab[i]));
		if (ftmap.size() != stdmap.size())
			isSizeOk = false;
		if (ftmap.empty() != stdmap.empty())
			isEmptyOk = false;
		if (ftmap.max_size() != ftMax || stdmap.max_size() != stdMax)
			isMaxSizeOk = false;
	}
	for (size_t i = 0; i < size && isSizeOk && isEmptyOk && isMaxSizeOk; i++)
	{
		stdmap.erase(stdmap.begin());
		ftmap.erase(ftmap.begin());
		if (ftmap.size() != stdmap.size())
			isSizeOk = false;
		if (ftmap.empty() != stdmap.empty())
			isEmptyOk = false;
		if (ftmap.max_size() != ftMax || stdmap.max_size() != stdMax)
			isMaxSizeOk = false;
	}
	if (!(isSizeOk && isEmptyOk && isMaxSizeOk))
		printMaps(stdmap, ftmap);
	printTest("size", isSizeOk);
	printTest("empty", isEmptyOk);
	printTest("MaxSize", isMaxSizeOk);
}

template<typename MAPSTD, typename MAPFT>
bool clearTest(MAPSTD& stdmap, MAPFT& ftmap)
{
	stdmap.clear();
	ftmap.clear();
	return true;
}

template <typename K, typename T, class F>
void doTest(const K* ktab, const T* vtab, size_t size, F* f, std::string test_name)
{
	bool isOk = true;
	{
		FTMAP				ftmap;
		STDMAP				stdmap;

		for (size_t i = 0; isOk && i < size; i++)
		{
			stdmap.insert(std::pair<K, T>(ktab[i], vtab[i]));
			ftmap.insert(ft::pair<K, T>(ktab[i], vtab[i]));
			isOk = f(stdmap, ftmap);
			if (!mapEqual(ftmap, stdmap))
				isOk = false;
		}
	}
	{
		FTMAP				ftmap = constructMap<K, T, FTMAP>(ktab, vtab, size);
		STDMAP				stdmap = constructMap<K, T, STDMAP>(ktab, vtab, size);

		f(stdmap, ftmap);
		if (!mapEqual(ftmap, stdmap))
			isOk = false;
	}
	printTest(test_name, isOk);
}

template <typename K, typename T, class F>
void doConstTest(const K* ktab, const T* vtab, size_t size, F* f, std::string test_name)
{
	bool isOk = true;
	{
		const FTMAP				ftmap;
		const STDMAP				stdmap;

		for (size_t i = 0; isOk && i < size; i++)
		{
			stdmap.insert(std::pair<K, T>(ktab[i], vtab[i]));
			ftmap.insert(ft::pair<K, T>(ktab[i], vtab[i]));
			isOk = f(stdmap, ftmap);
			if (!mapEqual(ftmap, stdmap))
				isOk = false;
		}
	}
	{
		const FTMAP					ftmap = constructMap<K, T, FTMAP>(ktab, vtab, size);
		const STDMAP				stdmap = constructMap<K, T, STDMAP>(ktab, vtab, size);

		f(stdmap, ftmap);
		if (!mapEqual(ftmap, stdmap))
			isOk = false;
	}
	printTest(test_name, isOk);
}

template <typename K, typename T>
void mapTest(const K* ktab, const T* vtab, size_t size)
{

	printTitle("MAP", STR_MAGENTA, 1);

	printTitle("capacity", STR_BLUE, 0);
	capacityTest<K, T>(ktab, vtab, size);
	printTitle("modifiers", STR_BLUE, 0);
	doTest<K, T>(ktab, vtab, size, clearTest<STDMAP, FTMAP>, "clear");
	// modifiersTest<K, T>(ktab, vtab, size);
	
	// std::cout << "===================================================================" <<std::endl
	// 		  << "====                        Modifiers                          ====" <<std::endl
	// 		  << "===================================================================" <<std::endl;
	// constructVector<ft::vector<T>, std::vector<T>, T>(
	// 	vectorTest_clear< ft::vector<T>, std::vector<T> >, tab, size, "clear(" + type + ")");
	// constructVector<ft::vector<T>, std::vector<T>, T>(
	// 	vectorTest_insertVal< ft::vector<T>, std::vector<T> >, tab, size, "insert 1 el(" + type + ")");


	// std::cout << "===================================================================" <<std::endl
	// 		  << "====                     Reverse Iterator                      ====" <<std::endl
	// 		  << "===================================================================" <<std::endl;
	// constructVector<ft::vector<T>, std::vector<T>, T>(
	// 	vectorTest_reverseIterator< ft::vector<T>, std::vector<T> >, tab, size, "reverse_iterator(" + type + ")");
	
}

#endif