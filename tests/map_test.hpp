/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:25:28 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/09 20:21:03 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TESTS_HPP
# define MAP_TESTS_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <list>
#include <map>
#include <utility>
#include "map.hpp"
#include "utility.hpp"
#include "tests.hpp"

#define STDMAP typename std::map<K, T, std::less<K>, std::allocator<std::pair<const K, T> > >
#define FTMAP typename ft::map<K, T>

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
void capacityTest(const K* ktab, T* vtab, size_t size)
{
	FTMAP				ftmap;
	STDMAP				stdmap;
	bool				isSizeOk = true;
	bool				isEmptyOk = true;
	bool				isMaxSizeOk = true;
	FTMAP::size_type	ftMax = ftmap.max_size();
	STDMAP::size_type	stdMax = stdmap.max_size();

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

template <typename K, typename T>
void mapTest(K* ktab, T* vtab, size_t size)
{

	printTitle("MAP", STR_MAGENTA, 1);

	printTitle("capacity", STR_BLUE, 0);
	capacityTest<K, T>(ktab, vtab, size);
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