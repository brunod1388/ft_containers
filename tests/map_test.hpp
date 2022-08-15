/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:25:28 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/15 02:39:58 by brunodeoliv      ###   ########.fr       */
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

template <class P1, class P2>
bool operator==(const P1& pstd, const P2& pft)
{
	return pstd.first == pft.first && pstd.second == pft.second;
}

template <typename K, typename T>
bool mapEqual(const std::map<K, T>& mstd, const ft::map<K, T>& mft)
{
	if (mft.size() != mstd.size())
		return false;

	typename ft::map<K, T>::const_iterator ift = mft.begin();
	typename std::map<K, T>::const_iterator istd = mstd.begin();

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
void printMaps(const STDMAP& stdm, const FTMAP& ftm, const STDMAP* stdtmp = NULL, const FTMAP* fttmp = NULL)
{
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "ft  : ";
	print(ftm);
	std::cout << "std : ";
	print(stdm);
	if (stdtmp)
	{
		std::cout << STR_YELLOW << "stdtmp : " << STR_RESET;
		print(*stdtmp);
	}
	if (fttmp)
	{
		std::cout << STR_YELLOW << "fttmp : " << STR_RESET;
		print(*fttmp);
	}
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
	MAPSTD	tmpstd = stdmap;
	MAPFT	tmpft = ftmap;

	tmpstd.clear();
	tmpft.clear();
	if (mapEqual(tmpstd, tmpft))
		return true;
	printMaps(stdmap, ftmap, &tmpstd, &tmpft);
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool bracketsTest(MAPSTD& stdmap, MAPFT& ftmap)
{
	MAPSTD	tmpstd = stdmap;
	MAPFT	tmpft = ftmap;
	bool	isOk = true;

	typename MAPSTD::const_iterator	istd = stdmap.begin();
	typename MAPFT::const_iterator	ift = ftmap.begin();

	for (size_t i = 0; isOk && i < stdmap.size(); i++)
	{
		if (tmpstd[(*(istd++)).first] != tmpft[(*(ift++)).first])
			isOk = false;
	}
	istd = stdmap.begin();
	ift = ftmap.begin();
	for (size_t i = 0; isOk && i < stdmap.size(); i++)
	{
		tmpstd[(*(istd)).first] = stdmap[(*stdmap.begin()).first];
		tmpft[(*(ift)).first] = ftmap[(*ftmap.begin()).first];
		if (tmpstd[(*(istd++)).first] != tmpft[(*(ift++)).first])
			isOk = false;
	}
	if (isOk)
		return true;
	printMaps(stdmap, ftmap, &tmpstd, &tmpft);
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool atTest(MAPSTD& stdmap, MAPFT& ftmap)
{
	MAPSTD	tmpstd = stdmap;
	MAPFT	tmpft = ftmap;
	bool	isOk = true;

	typename MAPSTD::const_iterator	istd = tmpstd.begin();
	typename MAPFT::const_iterator	ift = tmpft.begin();

	for (size_t i = 0; isOk && i < tmpstd.size(); i++)
	{
		if (tmpstd.at((*(istd++)).first) != tmpft.at((*(ift++)).first))
			isOk = false;
	}
	istd = tmpstd.begin();
	ift = tmpft.begin();
	for (size_t i = 0; isOk && i < stdmap.size(); i++)
	{
		tmpstd.at((*(istd)).first) = stdmap.at((*stdmap.begin()).first);
		tmpft.at((*(ift)).first) = ftmap.at((*ftmap.begin()).first);
		if (tmpstd.at((*(istd++)).first) != tmpft.at((*(ift++)).first))
			isOk = false;
	}
	if (isOk)
		return true;
	printMaps(stdmap, ftmap, &tmpstd, &tmpft);
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool atConstTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	const MAPSTD	tmpstd = stdmap;
	const MAPFT		tmpft = ftmap;
	bool	isOk = true;

	typename MAPSTD::const_iterator	istd = tmpstd.begin();
	typename MAPFT::const_iterator	ift = tmpft.begin();

	for (size_t i = 0; isOk && i < tmpstd.size(); i++)
	{
		if (tmpstd.at((*(istd++)).first) != tmpft.at((*(ift++)).first))
			isOk = false;
	}
	if (isOk)
		return true;
	printMaps(stdmap, ftmap, &tmpstd, &tmpft);
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool beginTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	bool							isOk = true;
	typename MAPFT::const_iterator	ftit = ftmap.begin();
	typename MAPSTD::const_iterator stdit = stdmap.begin();

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
		if (!(*stdit == *ftit))
			isOk = false;

	if (isOk)
		return true;
	printMaps(stdmap, ftmap);
	std::cout << "ft::begin()-- : " << *ftit << std::endl;
	std::cout << "std::begin()-- : " << *stdit << std::endl;
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool endTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	bool							isOk = true;
	typename MAPFT::const_iterator	ftit = ftmap.end();
	typename MAPSTD::const_iterator stdit = stdmap.end();

	if (stdmap.size())
	{
		ftit--; stdit--;
	}
	for (; isOk && ftit != ftmap.begin() && stdit != stdmap.begin(); stdit--, ftit--)
		if (!(*stdit == *ftit))
			isOk = false;

	if (isOk)
		return true;
	printMaps(stdmap, ftmap);
	std::cout << "ft::end()-- : " << *ftit << std::endl;
	std::cout << "std::end()-- : " << *stdit << std::endl;
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool beginConstTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	if (stdmap.begin() == stdmap.end() &&
		ftmap.begin() == ftmap.end())
		return true;

	if (*stdmap.begin() == *ftmap.begin())
		return true;
	printMaps(stdmap, ftmap);
	std::cout << "ft::begin() const : " << *ftmap.begin() << std::endl;
	std::cout << "std::begin() const : " << *stdmap.begin() << std::endl;
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool endConstTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	if (stdmap.begin() == stdmap.end() &&
		ftmap.begin() == ftmap.end())
		return true;

	if (*(--stdmap.end()) == *(--ftmap.end()))
		return true;
	printMaps(stdmap, ftmap);
	std::cout << "ft::end() const : " << *(--ftmap.end()) << std::endl;
	std::cout << "std::end() const : " << *(--stdmap.end()) << std::endl;
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool rbeginTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	bool							isOk = true;
	typename MAPFT::const_reverse_iterator	ftit = ftmap.rbegin();
	typename MAPSTD::const_reverse_iterator stdit = stdmap.rbegin();

	for (; isOk && ftit != ftmap.rend() && stdit != stdmap.rend(); stdit++, ftit++)
		if (!(*stdit == *ftit))
			isOk = false;

	if (isOk)
		return true;
	printMaps(stdmap, ftmap);
	std::cout << "ft::rbegin()++ : " << *ftit << std::endl;
	std::cout << "std::rbegin()++ : " << *stdit << std::endl;
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool rendTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	bool							isOk = true;
	typename MAPFT::const_reverse_iterator	ftit = ftmap.rend();
	typename MAPSTD::const_reverse_iterator stdit = stdmap.rend();

	if (stdmap.size())
	{
		ftit--; stdit--;
	}
	for (; isOk && ftit != ftmap.rbegin() && stdit != stdmap.rbegin(); stdit--, ftit--)
		if (!(*stdit == *ftit))
			isOk = false;

	if (isOk)
		return true;
	printMaps(stdmap, ftmap);
	std::cout << "ft::rend()-- : " << *ftit << std::endl;
	std::cout << "std::rend()-- : " << *stdit << std::endl;
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool rbeginConstTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	if (stdmap.rbegin() == stdmap.rend() &&
		ftmap.rbegin() == ftmap.rend())
		return true;

	if (*stdmap.rbegin() == *ftmap.rbegin())
		return true;
	printMaps(stdmap, ftmap);
	std::cout << "ft::rbegin() const : " << *ftmap.rbegin() << std::endl;
	std::cout << "std::rbegin() const : " << *stdmap.rbegin() << std::endl;
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool rendConstTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	if (stdmap.rbegin() == stdmap.rend() &&
		ftmap.rbegin() == ftmap.rend())
		return true;

	if (*(--stdmap.rend()) == *(--ftmap.rend()))
		return true;
	printMaps(stdmap, ftmap);
	std::cout << "ft::rend() const : " << *(--ftmap.rend()) << std::endl;
	std::cout << "std::rend() const : " << *(--stdmap.rend()) << std::endl;
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool countTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	bool						isOk = true;
	typename MAPFT::const_iterator	ftit = ftmap.begin();
	typename MAPSTD::const_iterator	stdit = stdmap.begin();

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
		if (stdmap.count((*stdit).first) != ftmap.count((*ftit).first))
			isOk = false;
	if (stdmap.count(typename MAPSTD::key_type()) != ftmap.count(typename MAPFT::key_type()))
		isOk = false;
	if (isOk)
		return true;
	printMaps(stdmap, ftmap);
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool findTest(MAPSTD& stdmap, MAPFT& ftmap)
{
	bool							isOk = true;
	typename MAPFT::const_iterator	ftit = ftmap.begin();
	typename MAPSTD::const_iterator	stdit = stdmap.begin();
	typename MAPFT::const_iterator	retit;
	typename MAPSTD::const_iterator	retstd;

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		retit = ftmap.count((*ftit).first);
		retstd = stdmap.find((*stdit).first);
		if (retit != retstd)
			isOk = false;
	}
	if (stdmap.find(typename MAPSTD::key_type()) != ftmap.find(typename MAPFT::key_type()))
		isOk = false;
	if (isOk)
		return true;
	printMaps(stdmap, ftmap);
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool constFindTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	bool							isOk = true;
	typename MAPFT::const_iterator	ftit = ftmap.begin();
	typename MAPSTD::const_iterator	stdit = stdmap.begin();

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
		if (stdmap.find((*stdit).first) != ftmap.count((*ftit).first))
			isOk = false;
	if (stdmap.find(typename MAPSTD::key_type()) != ftmap.find(typename MAPFT::key_type()))
		isOk = false;
	if (isOk)
		return true;
	printMaps(stdmap, ftmap);
	return false;
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
			isOk = f(stdmap, ftmap);
			if (!mapEqual(stdmap, ftmap))
				isOk = false;
			stdmap.insert(std::pair<K, T>(ktab[i], vtab[i]));
			ftmap.insert(ft::pair<K, T>(ktab[i], vtab[i]));
		}
	}
	printTest(test_name, isOk);
}

template <typename K, typename T, class F>
void doConstTest(const K* ktab, const T* vtab, size_t size, F* f, std::string test_name)
{
	bool isOk = true;
	{
		std::list<std::pair<K, T> >	lst;
		std::list<ft::pair<K, T> >	lft;

		for (size_t i = 0; i < size; i++)
			lst.push_back(std::pair<K, T>(ktab[i], vtab[i]));
		for (size_t i = 0; i < size; i++)
			lft.push_back(ft::pair<K, T>(ktab[i], vtab[i]));

		for (size_t i = 0; isOk && i < size; i++)
		{
			const std::map<K, T>	stdmap(lst.begin(), lst.end());
			const ft::map<K, T>		ftmap(lft.begin(), lft.end());
			isOk = f(stdmap, ftmap);
			if (!mapEqual(stdmap, ftmap))
				isOk = false;
		}
	}
	printTest(test_name, isOk);
}

template <typename K, typename T>
void mapTest(const K* ktab, const T* vtab, size_t size)
{
	printTitle("MAP", STR_MAGENTA, 1);

	printTitle("Element access", STR_BLUE, 0);
	doTest<K, T>(ktab, vtab, size, clearTest<STDMAP, FTMAP>, "clear");
	doTest<K, T>(ktab, vtab, size, bracketsTest<STDMAP, FTMAP>, "brackets");
	doTest<K, T>(ktab, vtab, size, atTest<STDMAP, FTMAP>, "at");
	doConstTest<K, T>(ktab, vtab, size, atConstTest<STDMAP, FTMAP>, "at const");

	printTitle("Iterators", STR_BLUE, 0);
	doTest<K, T>(ktab, vtab, size, beginTest<STDMAP, FTMAP>, "begin");
	doTest<K, T>(ktab, vtab, size, endTest<STDMAP, FTMAP>, "end");
	doConstTest<K, T>(ktab, vtab, size, beginConstTest<STDMAP, FTMAP>, "begin const");
	doConstTest<K, T>(ktab, vtab, size, endConstTest<STDMAP, FTMAP>, "end const");
	doTest<K, T>(ktab, vtab, size, rbeginTest<STDMAP, FTMAP>, "rbegin");
	doTest<K, T>(ktab, vtab, size, rendTest<STDMAP, FTMAP>, "rend");
	doConstTest<K, T>(ktab, vtab, size, rbeginConstTest<STDMAP, FTMAP>, "rbegin const");
	doConstTest<K, T>(ktab, vtab, size, rendConstTest<STDMAP, FTMAP>, "rend const");

	printTitle("capacity", STR_BLUE, 0);
	capacityTest<K, T>(ktab, vtab, size);

	printTitle("LookUp", STR_BLUE, 0);
	doTest<K, T>(ktab, vtab, size, countTest<STDMAP, FTMAP>, "count");
	doTest<K, T>(ktab, vtab, size, findTest<STDMAP, FTMAP>, "find");
	doConstTest<K, T>(ktab, vtab, size, constFindTest<STDMAP, FTMAP>, "find");

}

#endif