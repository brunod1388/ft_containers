/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:25:28 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/18 04:24:49 by brunodeoliv      ###   ########.fr       */
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

void	printMapTest(std::string str, bool ok)
{
	std::cout << std::setw(30) << STR_BLUE + str + ":" << (ok ? OK : NOTOK) << STR_RESET << std::endl;
}

template <typename K, typename T>
bool capacityMapTest(const K* ktab, const T* vtab, size_t size)
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
	printMapTest("size", isSizeOk);
	printMapTest("empty", isEmptyOk);
	printMapTest("MaxSize", isMaxSizeOk);
	return (isSizeOk && isEmptyOk && isMaxSizeOk);
}

template<typename MAPSTD, typename MAPFT>
bool clearMapTest(MAPSTD& stdmap, MAPFT& ftmap)
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
bool bracketsMapTest(MAPSTD& stdmap, MAPFT& ftmap)
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
bool atMapTest(MAPSTD& stdmap, MAPFT& ftmap)
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
bool atConstMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
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
bool beginMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
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
bool endMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
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
bool beginConstMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
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
bool endConstMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
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
bool rbeginMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	bool									isOk = true;
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
bool rendMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	bool									isOk = true;
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
bool rbeginConstMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
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
bool rendConstMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
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
bool countMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	bool							isOk = true;
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
bool findMapTest(MAPSTD& stdmap, MAPFT& ftmap)
{
	bool							isOk = true;
	typename MAPFT::const_iterator	ftit = ftmap.begin();
	typename MAPSTD::const_iterator	stdit = stdmap.begin();
	typename MAPFT::iterator		retft;
	typename MAPSTD::iterator		retstd;

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		retft = ftmap.find((*ftit).first);
		retstd = stdmap.find((*stdit).first);
		if (retft == ftmap.end() || retstd == stdmap.end() || !(*retstd == *retft))
			isOk = false;
	}
	retft = ftmap.find(typename MAPFT::key_type());
	retstd = stdmap.find(typename MAPSTD::key_type());
	if (retft != ftmap.end() && retstd != stdmap.end() && !(*retstd == *retft))
		isOk = false;
	if (isOk)
		return true;
	printMaps(stdmap, ftmap);
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool constFindMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	bool							isOk = true;
	typename MAPFT::const_iterator	ftit = ftmap.begin();
	typename MAPSTD::const_iterator	stdit = stdmap.begin();
	typename MAPFT::const_iterator	retft;
	typename MAPSTD::const_iterator	retstd;

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		retft = ftmap.find((*ftit).first);
		retstd = stdmap.find((*stdit).first);
		if (retft == ftmap.end() || retstd == stdmap.end() || !(*retstd == *retft))
			isOk = false;
	}
	retft = ftmap.find(typename MAPFT::key_type());
	retstd = stdmap.find(typename MAPSTD::key_type());
	if (retft != ftmap.end() && retstd != stdmap.end() && !(*retstd == *retft))
		isOk = false;
	if (isOk)
		return true;
	printMaps(stdmap, ftmap);
	return false;
}


template<typename MAPSTD, typename MAPFT>
bool lowerMapTest(MAPSTD& stdmap, MAPFT& ftmap)
{
	bool							isOk = true;
	typename MAPFT::const_iterator	ftit = ftmap.begin();
	typename MAPSTD::const_iterator	stdit = stdmap.begin();
	typename MAPFT::iterator		retft;
	typename MAPSTD::iterator		retstd;

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		retft = ftmap.lower_bound((*ftit).first);
		retstd = stdmap.lower_bound((*stdit).first);
		if (retft == ftmap.end() || retstd == stdmap.end() || !(*retstd == *retft))
			isOk = false;
	}
	retft = ftmap.lower_bound(typename MAPFT::key_type());
	retstd = stdmap.lower_bound(typename MAPSTD::key_type());
	if (retft != ftmap.end() && retstd != stdmap.end() && !(*retstd == *retft))
		isOk = false;
	if (isOk)
		return true;
	printMaps(stdmap, ftmap);
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool constLowerMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	bool							isOk = true;
	typename MAPFT::const_iterator	ftit = ftmap.begin();
	typename MAPSTD::const_iterator	stdit = stdmap.begin();
	typename MAPFT::const_iterator	retft;
	typename MAPSTD::const_iterator	retstd;

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		retft = ftmap.lower_bound((*ftit).first);
		retstd = stdmap.lower_bound((*stdit).first);
		if (retft == ftmap.end() || retstd == stdmap.end() || !(*retstd == *retft))
			isOk = false;
	}
	retft = ftmap.lower_bound(typename MAPFT::key_type());
	retstd = stdmap.lower_bound(typename MAPSTD::key_type());
	if (retft != ftmap.end() && retstd != stdmap.end() && !(*retstd == *retft))
		isOk = false;
	if (isOk)
		return true;
	printMaps(stdmap, ftmap);
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool upperMapTest(MAPSTD& stdmap, MAPFT& ftmap)
{
	bool							isOk = true;
	typename MAPFT::const_iterator	ftit = ftmap.begin();
	typename MAPSTD::const_iterator	stdit = stdmap.begin();
	typename MAPFT::iterator		retft;
	typename MAPSTD::iterator		retstd;

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		retft = ftmap.upper_bound((*ftit).first);
		retstd = stdmap.upper_bound((*stdit).first);
		if (retft != ftmap.end() && retstd != stdmap.end() && !(*retstd == *retft))
			isOk = false;
	}
	if (isOk)
	{
		retft = ftmap.upper_bound(typename MAPFT::key_type());
		retstd = stdmap.upper_bound(typename MAPSTD::key_type());
		if (retft != ftmap.end() && retstd != stdmap.end() && !(*retstd == *retft))
			isOk = false;
		if (isOk)
			return true;
	}
	printMaps(stdmap, ftmap);
	std::cout << "ft::upper_bound return == end()  : " << (retft == ftmap.end()) << std::endl;
	std::cout << "std::upper_bound return == end() : " << (retstd == stdmap.end()) << std::endl;
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool constUpperMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	bool							isOk = true;
	typename MAPFT::const_iterator	ftit = ftmap.begin();
	typename MAPSTD::const_iterator	stdit = stdmap.begin();
	typename MAPFT::const_iterator	retft;
	typename MAPSTD::const_iterator	retstd;

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		retft = ftmap.upper_bound((*ftit).first);
		retstd = stdmap.upper_bound((*stdit).first);
		if (retft != ftmap.end() && retstd != stdmap.end() && !(*retstd == *retft))
			isOk = false;
	}
	if (isOk)
	{
		retft = ftmap.upper_bound(typename MAPFT::key_type());
		retstd = stdmap.upper_bound(typename MAPSTD::key_type());
		if (retft != ftmap.end() && retstd != stdmap.end() && !(*retstd == *retft))
			isOk = false;
		if (isOk)
			return true;
	}
	printMaps(stdmap, ftmap);
	std::cout << "ft::upper_bound return == end()  : " << (retft == ftmap.end()) << std::endl;
	std::cout << "std::upper_bound return == end() : " << (retstd == stdmap.end()) << std::endl;
	return false;
}


template<typename MAPSTD, typename MAPFT>
bool equalMapTest(MAPSTD& stdmap, MAPFT& ftmap)
{
	bool							isOk = true;
	typename MAPFT::const_iterator	ftit = ftmap.begin();
	typename MAPSTD::const_iterator	stdit = stdmap.begin();
	ft::pair<typename MAPFT::iterator, typename MAPFT::iterator>	retft;
	std::pair<typename MAPSTD::iterator, typename MAPSTD::iterator>	retstd;

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		retft = ftmap.equal_range((*ftit).first);
		retstd = stdmap.equal_range((*stdit).first);
		if ((retft.first != ftmap.end() && retstd.first != stdmap.end() && !(*retstd.first == *retft.first)) ||
			(retft.second != ftmap.end() && retstd.second != stdmap.end() && !(*retstd.second == *retft.second)))
			isOk = false;
	}
	if (isOk)
	{
		retft = ftmap.equal_range(typename MAPFT::key_type());
		retstd = stdmap.equal_range(typename MAPSTD::key_type());
		if ((retft.first != ftmap.end() && retstd.first != stdmap.end() && !(*retstd.first == *retft.first)) ||
			(retft.second != ftmap.end() && retstd.second != stdmap.end() && !(*retstd.second == *retft.second)))
			isOk = false;
		if (isOk)
			return true;
	}
	printMaps(stdmap, ftmap);
	std::cout << "ft::equal_range return  : pair<" << (retft.first == ftmap.end() ? (typename MAPFT::value_type()) : *retft.first)
			  << ", " << (retft.second == ftmap.end() ? (typename MAPFT::value_type()) : *retft.second) << std::endl;
	std::cout << "std::equal_range return : pair<" << (retstd.first == stdmap.end() ? (typename MAPSTD::value_type()) : *retstd.first)
			  << ", " << (retstd.second == stdmap.end() ? (typename MAPSTD::value_type()) : *retstd.second) << std::endl;
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool constEqualMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	bool							isOk = true;
	typename MAPFT::const_iterator	ftit = ftmap.begin();
	typename MAPSTD::const_iterator	stdit = stdmap.begin();
	ft::pair<typename MAPFT::const_iterator, typename MAPFT::const_iterator>	retft;
	std::pair<typename MAPSTD::const_iterator, typename MAPSTD::const_iterator>	retstd;

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		retft = ftmap.equal_range((*ftit).first);
		retstd = stdmap.equal_range((*stdit).first);
		if ((retft.first != ftmap.end() && retstd.first != stdmap.end() && !(*retstd.first == *retft.first)) ||
			(retft.second != ftmap.end() && retstd.second != stdmap.end() && !(*retstd.second == *retft.second)))
			isOk = false;
	}
	if (isOk)
	{
		retft = ftmap.equal_range(typename MAPFT::key_type());
		retstd = stdmap.equal_range(typename MAPSTD::key_type());
		if ((retft.first != ftmap.end() && retstd.first != stdmap.end() && !(*retstd.first == *retft.first)) ||
			(retft.second != ftmap.end() && retstd.second != stdmap.end() && !(*retstd.second == *retft.second)))
			isOk = false;
		if (isOk)
			return true;
	}
	printMaps(stdmap, ftmap);
	std::cout << "ft::equal_range return  : pair<" << (retft.first == ftmap.end() ? (typename MAPFT::value_type()) : *retft.first)
			  << ", " << (retft.second == ftmap.end() ? (typename MAPFT::value_type()) : *retft.second) << std::endl;
	std::cout << "std::equal_range return : pair<" << (retstd.first == stdmap.end() ? (typename MAPSTD::value_type()) : *retstd.first)
			  << ", " << (retstd.second == stdmap.end() ? (typename MAPSTD::value_type()) : *retstd.second) << std::endl;
	return false;
}

template<typename MAPSTD, typename MAPFT>
bool insertValMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	MAPFT										tmpFt;
	MAPSTD										tmpStd;
	bool										isOk = true;
	typename MAPFT::const_iterator				ftit = ftmap.begin();
	typename MAPSTD::const_iterator				stdit = stdmap.begin();
	ft::pair<typename MAPFT::iterator, bool>	retft;
	std::pair<typename MAPSTD::iterator, bool>	retstd;

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		retft = tmpFt.insert(*ftit);
		retstd = tmpStd.insert(*stdit);
		if (!(*retft.first == *retstd.first) || retft.second != retstd.second || !mapEqual(tmpStd, tmpFt))
			return false;
	}
	return true;
}

template<typename MAPSTD, typename MAPFT>
bool insertRangeMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	MAPFT										tmpFt;
	MAPSTD										tmpStd;
	bool										isOk = true;
	typename MAPFT::const_iterator				ftit = ftmap.begin();
	typename MAPSTD::const_iterator				stdit = stdmap.begin();

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		tmpFt.insert(ftmap.begin(), ftit);
		tmpStd.insert(stdmap.begin(), stdit);
		if (!mapEqual(tmpStd, tmpFt))
			return false;
		tmpFt.clear();
		tmpStd.clear();
	}
	return true;
}

template<typename MAPSTD, typename MAPFT>
bool insertHintMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	MAPFT										tmpFt;
	MAPSTD										tmpStd;
	bool										isOk = true;
	typename MAPFT::const_iterator				ftit = ftmap.begin();
	typename MAPSTD::const_iterator				stdit = stdmap.begin();


	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		tmpFt.insert(tmpFt.begin(), *ftit);
		tmpStd.insert(tmpStd.begin(), *stdit);
		if (!mapEqual(tmpStd, tmpFt))
			return false;
	}
	tmpFt.clear();
	tmpStd.clear();
	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		tmpFt.insert(tmpFt.end(), *ftit);
		tmpStd.insert(tmpStd.end(), *stdit);
		if (!mapEqual(tmpStd, tmpFt))
			return false;
	}
	return true;
}

template<typename MAPSTD, typename MAPFT>
bool erasePosMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	MAPFT										tmpFt(ftmap);
	MAPSTD										tmpStd(stdmap);
	bool										isOk = true;
	typename MAPFT::const_iterator				ftit = ftmap.begin();
	typename MAPSTD::const_iterator				stdit = stdmap.begin();
	ft::pair<typename MAPFT::iterator, bool>	retft;
	std::pair<typename MAPSTD::iterator, bool>	retstd;

	if (!stdmap.size())
		return true;
	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		tmpFt.erase(tmpFt.begin());
		tmpStd.erase(tmpStd.begin());
		if (!mapEqual(tmpStd, tmpFt))
			return false;
	}
	return true;
}

template<typename MAPSTD, typename MAPFT>
bool eraseKeyMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	MAPFT										tmpFt;
	MAPSTD										tmpStd;
	bool										isOk = true;
	typename MAPFT::const_iterator				ftit = ftmap.begin();
	typename MAPSTD::const_iterator				stdit = stdmap.begin();
	size_t										resft;
	size_t										resstd;

	for (; isOk && ftit != ftmap.end() && stdit != stdmap.end(); stdit++, ftit++)
	{
		resft = tmpFt.erase((*ftit).first);
		resstd = tmpStd.erase((*stdit).first);
		if (resft != resstd && !mapEqual(tmpStd, tmpFt))
			return false;
	}
	return true;
}

template<typename MAPSTD, typename MAPFT>
bool eraseRangeMapTest(const MAPSTD& stdmap, const MAPFT& ftmap)
{
	MAPFT	tmpFt;
	MAPSTD	tmpStd;

	if (!stdmap.size())
		return true;

	tmpFt = ftmap;
	tmpStd = stdmap;
	tmpFt.erase(tmpFt.begin(), tmpFt.end());
	tmpStd.erase(tmpStd.begin(), tmpStd.end());
	if (!mapEqual(tmpStd, tmpFt))
	{
		printMaps(tmpStd, tmpFt);
		return false;
	}
	if (stdmap.size() < 3)
		return true;

	tmpFt = ftmap;
	tmpStd = stdmap;
	tmpFt.erase(++tmpFt.begin(), tmpFt.end());
	tmpStd.erase(++tmpStd.begin(), tmpStd.end());
	if (!mapEqual(tmpStd, tmpFt))
	{
		printMaps(tmpStd, tmpFt);
		return false;
	}

	tmpFt = ftmap;
	tmpStd = stdmap;
	tmpFt.erase(tmpFt.begin(), --tmpFt.end());
	tmpStd.erase(tmpStd.begin(), --tmpStd.end());
	if (!mapEqual(tmpStd, tmpFt))
	{
		printMaps(tmpStd, tmpFt);
		return false;
	}

	tmpFt = ftmap;
	tmpStd = stdmap;
	tmpFt.erase(++tmpFt.begin(), --tmpFt.end());
	tmpStd.erase(++tmpStd.begin(), --tmpStd.end());
	if (!mapEqual(tmpStd, tmpFt))
	{
		printMaps(tmpStd, tmpFt);
		return false;
	}
	return true;
}


template <typename K, typename T, class F>
bool doMapMapTest(const K* ktab, const T* vtab, size_t size, F* f, std::string test_name)
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
	printMapTest(test_name, isOk);
	return isOk;
}

template <typename K, typename T, class F>
bool doConstMapMapTest(const K* ktab, const T* vtab, size_t size, F* f, std::string test_name)
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
	printMapTest(test_name, isOk);
	return isOk;
}

template <typename K, typename T>
bool mapTest(const K* ktab, const T* vtab, size_t size, std::string types)
{
	bool isOk = true;

	printTitle("MAP" + types, STR_MAGENTA, 1);

	printTitle("Element access", STR_BLUE, 0);
	if (!doMapMapTest<K, T>(ktab, vtab, size, bracketsMapTest<STDMAP, FTMAP>, "brackets"))
		isOk = false;
	if (!doMapMapTest<K, T>(ktab, vtab, size, atMapTest<STDMAP, FTMAP>, "at"))
		isOk = false;
	if (!doConstMapMapTest<K, T>(ktab, vtab, size, atConstMapTest<STDMAP, FTMAP>, "at const"))
		isOk = false;

	printTitle("Iterators", STR_BLUE, 0);
	if (!doMapMapTest<K, T>(ktab, vtab, size, beginMapTest<STDMAP, FTMAP>, "begin"))
		isOk = false;
	if (!doMapMapTest<K, T>(ktab, vtab, size, endMapTest<STDMAP, FTMAP>, "end"))
		isOk = false;
	if (!doConstMapMapTest<K, T>(ktab, vtab, size, beginConstMapTest<STDMAP, FTMAP>, "begin const"))
		isOk = false;
	if (!doConstMapMapTest<K, T>(ktab, vtab, size, endConstMapTest<STDMAP, FTMAP>, "end const"))
		isOk = false;
	if (!doMapMapTest<K, T>(ktab, vtab, size, rbeginMapTest<STDMAP, FTMAP>, "rbegin"))
		isOk = false;
	if (!doMapMapTest<K, T>(ktab, vtab, size, rendMapTest<STDMAP, FTMAP>, "rend"))
		isOk = false;
	if (!doConstMapMapTest<K, T>(ktab, vtab, size, rbeginConstMapTest<STDMAP, FTMAP>, "rbegin const"))
		isOk = false;
	if (!doConstMapMapTest<K, T>(ktab, vtab, size, rendConstMapTest<STDMAP, FTMAP>, "rend const"))
		isOk = false;

	printTitle("capacity", STR_BLUE, 0);
	if(!capacityMapTest<K, T>(ktab, vtab, size))
		isOk = false;

	printTitle("LookUp", STR_BLUE, 0);
	if (!doMapMapTest<K, T>(ktab, vtab, size, countMapTest<STDMAP, FTMAP>, "count"))
		isOk = false;
	if (!doMapMapTest<K, T>(ktab, vtab, size, findMapTest<STDMAP, FTMAP>, "find"))
		isOk = false;
	if (!doConstMapMapTest<K, T>(ktab, vtab, size, constFindMapTest<STDMAP, FTMAP>, "find const"))
		isOk = false;
	if (!doMapMapTest<K, T>(ktab, vtab, size, lowerMapTest<STDMAP, FTMAP>, "lower_bound"))
		isOk = false;
	if (!doConstMapMapTest<K, T>(ktab, vtab, size, constLowerMapTest<STDMAP, FTMAP>, "lower_bound const"))
		isOk = false;
	if (!doMapMapTest<K, T>(ktab, vtab, size, upperMapTest<STDMAP, FTMAP>, "upper_bound"))
		isOk = false;
	if (!doConstMapMapTest<K, T>(ktab, vtab, size, constUpperMapTest<STDMAP, FTMAP>, "upper_bound const"))
		isOk = false;
	if (!doMapMapTest<K, T>(ktab, vtab, size, equalMapTest<STDMAP, FTMAP>, "equal_range"))
		isOk = false;
	if (!doConstMapMapTest<K, T>(ktab, vtab, size, constEqualMapTest<STDMAP, FTMAP>, "equal_range const"))
		isOk = false;

	printTitle("Modifiers", STR_BLUE, 0);
	if (!doMapMapTest<K, T>(ktab, vtab, size, clearMapTest<STDMAP, FTMAP>, "clear"))
		isOk = false;
	if (!doMapMapTest<K, T>(ktab, vtab, size, insertValMapTest<STDMAP, FTMAP>, "insert(val)"))
		isOk = false;
	if (!doMapMapTest<K, T>(ktab, vtab, size, insertRangeMapTest<STDMAP, FTMAP>, "insert(first, last)"))
		isOk = false;
	if (!doMapMapTest<K, T>(ktab, vtab, size, insertHintMapTest<STDMAP, FTMAP>, "insert(hint, val)"))
		isOk = false;
	if (!doMapMapTest<K, T>(ktab, vtab, size, erasePosMapTest<STDMAP, FTMAP>, "erase(pos)"))
		isOk = false;
	if (!doMapMapTest<K, T>(ktab, vtab, size, eraseKeyMapTest<STDMAP, FTMAP>, "erase(key)"))
		isOk = false;
	if (!doMapMapTest<K, T>(ktab, vtab, size, eraseRangeMapTest<STDMAP, FTMAP>, "erase(first, last)"))
		isOk = false;
	std::cout << std::endl << std::endl;
	return isOk;
}

#endif