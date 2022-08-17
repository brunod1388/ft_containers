/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:25:28 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/17 08:22:05 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_TESTS_HPP
# define SET_TESTS_HPP

#include "tests.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <list>
#include <set>
#include <utility>
#include "set.hpp"
#include "utility.hpp"

#define STDSET std::set<T>
#define FTSET ft::set<T>

template <typename T>
bool setEqual(const std::set<T>& mstd, const ft::set<T>& mft)
{
	if (mft.size() != mstd.size())
		return false;

	typename ft::set<T>::const_iterator ift = mft.begin();
	typename std::set<T>::const_iterator istd = mstd.begin();

	while (ift != mft.end() && istd != mstd.end())
	{
		if ((*istd) != (*ift) || (*istd) != (*ift))
			return false;
		ift++;
		istd++;
	}
	return true;
}

template<typename T, class set>
set	constructSet(const T* vtab, size_t size)
{
	set m;
	for (size_t i = 0; i < size; i++)
		m.insert(vtab[i]);
	return m;
}

template <typename T>
void printSets(const STDSET& stdm, const FTSET& ftm, const STDSET* stdtmp = NULL, const FTSET* fttmp = NULL)
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

void	printSetTest(std::string str, bool ok)
{
	std::cout << std::setw(30) << STR_BLUE + str + ":" << (ok ? OK : NOTOK) << STR_RESET << std::endl;
}

template <typename T>
bool capacitySetTest(const T* vtab, size_t size)
{
	FTSET				ftset;
	STDSET				stdset;
	bool				isSizeOk = true;
	bool				isEmptyOk = true;
	bool				isMaxSizeOk = true;
	typename FTSET::size_type	ftMax = ftset.max_size();
	typename STDSET::size_type	stdMax = stdset.max_size();

	for (size_t i = 0; i < size && isSizeOk && isEmptyOk && isMaxSizeOk; i++)
	{
		stdset.insert(vtab[i]);
		ftset.insert(vtab[i]);
		if (ftset.size() != stdset.size())
			isSizeOk = false;
		if (ftset.empty() != stdset.empty())
			isEmptyOk = false;
		if (ftset.max_size() != ftMax || stdset.max_size() != stdMax)
			isMaxSizeOk = false;
	}
	for (size_t i = 0; i < size && isSizeOk && isEmptyOk && isMaxSizeOk; i++)
	{
		stdset.erase(stdset.begin());
		ftset.erase(ftset.begin());
		if (ftset.size() != stdset.size())
			isSizeOk = false;
		if (ftset.empty() != stdset.empty())
			isEmptyOk = false;
		if (ftset.max_size() != ftMax || stdset.max_size() != stdMax)
			isMaxSizeOk = false;
	}
	if (!(isSizeOk && isEmptyOk && isMaxSizeOk))
		printSets(stdset, ftset);
	printSetTest("size", isSizeOk);
	printSetTest("empty", isEmptyOk);
	printSetTest("MaxSize", isMaxSizeOk);
	return (isSizeOk && isEmptyOk && isMaxSizeOk);
}

template<typename SETSTD, typename SETFT>
bool clearSetTest(SETSTD& stdset, SETFT& ftset)
{
	SETSTD	tmpstd = stdset;
	SETFT	tmpft = ftset;

	tmpstd.clear();
	tmpft.clear();
	if (setEqual(tmpstd, tmpft))
		return true;
	printSets(stdset, ftset, &tmpstd, &tmpft);
	return false;
}

template<typename SETSTD, typename SETFT>
bool beginSetTest(const SETSTD& stdset, const SETFT& ftset)
{
	bool							isOk = true;
	typename SETFT::const_iterator	ftit = ftset.begin();
	typename SETSTD::const_iterator stdit = stdset.begin();

	for (; isOk && ftit != ftset.end() && stdit != stdset.end(); stdit++, ftit++)
		if (!(*stdit == *ftit))
			isOk = false;

	if (isOk)
		return true;
	printSets(stdset, ftset);
	std::cout << "ft::begin()-- : " << *ftit << std::endl;
	std::cout << "std::begin()-- : " << *stdit << std::endl;
	return false;
}

template<typename SETSTD, typename SETFT>
bool endSetTest(const SETSTD& stdset, const SETFT& ftset)
{
	bool							isOk = true;
	typename SETFT::const_iterator	ftit = ftset.end();
	typename SETSTD::const_iterator stdit = stdset.end();

	if (stdset.size())
	{
		ftit--; stdit--;
	}
	for (; isOk && ftit != ftset.begin() && stdit != stdset.begin(); stdit--, ftit--)
		if (!(*stdit == *ftit))
			isOk = false;

	if (isOk)
		return true;
	printSets(stdset, ftset);
	std::cout << "ft::end()-- : " << *ftit << std::endl;
	std::cout << "std::end()-- : " << *stdit << std::endl;
	return false;
}

template<typename SETSTD, typename SETFT>
bool beginConstSetTest(const SETSTD& stdset, const SETFT& ftset)
{
	if (stdset.begin() == stdset.end() &&
		ftset.begin() == ftset.end())
		return true;

	if (*stdset.begin() == *ftset.begin())
		return true;
	printSets(stdset, ftset);
	std::cout << "ft::begin() const : " << *ftset.begin() << std::endl;
	std::cout << "std::begin() const : " << *stdset.begin() << std::endl;
	return false;
}

template<typename SETSTD, typename SETFT>
bool endConstSetTest(const SETSTD& stdset, const SETFT& ftset)
{
	if (stdset.begin() == stdset.end() &&
		ftset.begin() == ftset.end())
		return true;

	if (*(--stdset.end()) == *(--ftset.end()))
		return true;
	printSets(stdset, ftset);
	std::cout << "ft::end() const : " << *(--ftset.end()) << std::endl;
	std::cout << "std::end() const : " << *(--stdset.end()) << std::endl;
	return false;
}

template<typename SETSTD, typename SETFT>
bool rbeginSetTest(const SETSTD& stdset, const SETFT& ftset)
{
	bool									isOk = true;
	typename SETFT::const_reverse_iterator	ftit = ftset.rbegin();
	typename SETSTD::const_reverse_iterator stdit = stdset.rbegin();

	for (; isOk && ftit != ftset.rend() && stdit != stdset.rend(); stdit++, ftit++)
		if (!(*stdit == *ftit))
			isOk = false;

	if (isOk)
		return true;
	printSets(stdset, ftset);
	std::cout << "ft::rbegin()++ : " << *ftit << std::endl;
	std::cout << "std::rbegin()++ : " << *stdit << std::endl;
	return false;
}

template<typename SETSTD, typename SETFT>
bool rendSetTest(const SETSTD& stdset, const SETFT& ftset)
{
	bool									isOk = true;
	typename SETFT::const_reverse_iterator	ftit = ftset.rend();
	typename SETSTD::const_reverse_iterator stdit = stdset.rend();

	if (stdset.size())
	{
		ftit--; stdit--;
	}
	for (; isOk && ftit != ftset.rbegin() && stdit != stdset.rbegin(); stdit--, ftit--)
		if (!(*stdit == *ftit))
			isOk = false;

	if (isOk)
		return true;
	printSets(stdset, ftset);
	std::cout << "ft::rend()-- : " << *ftit << std::endl;
	std::cout << "std::rend()-- : " << *stdit << std::endl;
	return false;
}

template<typename SETSTD, typename SETFT>
bool rbeginConstSetTest(const SETSTD& stdset, const SETFT& ftset)
{
	if (stdset.rbegin() == stdset.rend() &&
		ftset.rbegin() == ftset.rend())
		return true;

	if (*stdset.rbegin() == *ftset.rbegin())
		return true;
	printSets(stdset, ftset);
	std::cout << "ft::rbegin() const : " << *ftset.rbegin() << std::endl;
	std::cout << "std::rbegin() const : " << *stdset.rbegin() << std::endl;
	return false;
}

template<typename SETSTD, typename SETFT>
bool rendConstSetTest(const SETSTD& stdset, const SETFT& ftset)
{
	if (stdset.rbegin() == stdset.rend() &&
		ftset.rbegin() == ftset.rend())
		return true;

	if (*(--stdset.rend()) == *(--ftset.rend()))
		return true;
	printSets(stdset, ftset);
	std::cout << "ft::rend() const : " << *(--ftset.rend()) << std::endl;
	std::cout << "std::rend() const : " << *(--stdset.rend()) << std::endl;
	return false;
}

template<typename SETSTD, typename SETFT>
bool countSetTest(const SETSTD& stdset, const SETFT& ftset)
{
	bool							isOk = true;
	typename SETFT::const_iterator	ftit = ftset.begin();
	typename SETSTD::const_iterator	stdit = stdset.begin();

	for (; isOk && ftit != ftset.end() && stdit != stdset.end(); stdit++, ftit++)
		if (stdset.count((*stdit)) != ftset.count((*ftit)))
			isOk = false;
	if (stdset.count(typename SETSTD::key_type()) != ftset.count(typename SETFT::key_type()))
		isOk = false;
	if (isOk)
		return true;
	printSets(stdset, ftset);
	return false;
}

template<typename SETSTD, typename SETFT>
bool findSetTest(SETSTD& stdset, SETFT& ftset)
{
	bool							isOk = true;
	typename SETFT::const_iterator	ftit = ftset.begin();
	typename SETSTD::const_iterator	stdit = stdset.begin();
	typename SETFT::iterator		retft;
	typename SETSTD::iterator		retstd;

	for (; isOk && ftit != ftset.end() && stdit != stdset.end(); stdit++, ftit++)
	{
		retft = ftset.find((*ftit));
		retstd = stdset.find((*stdit));
		if (retft == ftset.end() || retstd == stdset.end() || !(*retstd == *retft))
			isOk = false;
	}
	retft = ftset.find(typename SETFT::key_type());
	retstd = stdset.find(typename SETSTD::key_type());
	if (retft != ftset.end() && retstd != stdset.end() && !(*retstd == *retft))
		isOk = false;
	if (isOk)
		return true;
	printSets(stdset, ftset);
	return false;
}

template<typename SETSTD, typename SETFT>
bool constFindSetTest(const SETSTD& stdset, const SETFT& ftset)
{
	bool							isOk = true;
	typename SETFT::const_iterator	ftit = ftset.begin();
	typename SETSTD::const_iterator	stdit = stdset.begin();
	typename SETFT::const_iterator	retft;
	typename SETSTD::const_iterator	retstd;

	for (; isOk && ftit != ftset.end() && stdit != stdset.end(); stdit++, ftit++)
	{
		retft = ftset.find((*ftit));
		retstd = stdset.find((*stdit));
		if (retft == ftset.end() || retstd == stdset.end() || !(*retstd == *retft))
			isOk = false;
	}
	retft = ftset.find(typename SETFT::key_type());
	retstd = stdset.find(typename SETSTD::key_type());
	if (retft != ftset.end() && retstd != stdset.end() && !(*retstd == *retft))
		isOk = false;
	if (isOk)
		return true;
	printSets(stdset, ftset);
	return false;
}


template<typename SETSTD, typename SETFT>
bool lowerSetTest(SETSTD& stdset, SETFT& ftset)
{
	bool							isOk = true;
	typename SETFT::const_iterator	ftit = ftset.begin();
	typename SETSTD::const_iterator	stdit = stdset.begin();
	typename SETFT::iterator		retft;
	typename SETSTD::iterator		retstd;

	for (; isOk && ftit != ftset.end() && stdit != stdset.end(); stdit++, ftit++)
	{
		retft = ftset.lower_bound((*ftit));
		retstd = stdset.lower_bound((*stdit));
		if (retft == ftset.end() || retstd == stdset.end() || !(*retstd == *retft))
			isOk = false;
	}
	retft = ftset.lower_bound(typename SETFT::key_type());
	retstd = stdset.lower_bound(typename SETSTD::key_type());
	if (retft != ftset.end() && retstd != stdset.end() && !(*retstd == *retft))
		isOk = false;
	if (isOk)
		return true;
	printSets(stdset, ftset);
	return false;
}

template<typename SETSTD, typename SETFT>
bool constLowerSetTest(const SETSTD& stdset, const SETFT& ftset)
{
	bool							isOk = true;
	typename SETFT::const_iterator	ftit = ftset.begin();
	typename SETSTD::const_iterator	stdit = stdset.begin();
	typename SETFT::const_iterator	retft;
	typename SETSTD::const_iterator	retstd;

	for (; isOk && ftit != ftset.end() && stdit != stdset.end(); stdit++, ftit++)
	{
		retft = ftset.lower_bound((*ftit));
		retstd = stdset.lower_bound((*stdit));
		if (retft == ftset.end() || retstd == stdset.end() || !(*retstd == *retft))
			isOk = false;
	}
	retft = ftset.lower_bound(typename SETFT::key_type());
	retstd = stdset.lower_bound(typename SETSTD::key_type());
	if (retft != ftset.end() && retstd != stdset.end() && !(*retstd == *retft))
		isOk = false;
	if (isOk)
		return true;
	printSets(stdset, ftset);
	return false;
}

template<typename SETSTD, typename SETFT>
bool upperSetTest(SETSTD& stdset, SETFT& ftset)
{
	bool							isOk = true;
	typename SETFT::const_iterator	ftit = ftset.begin();
	typename SETSTD::const_iterator	stdit = stdset.begin();
	typename SETFT::iterator		retft;
	typename SETSTD::iterator		retstd;

	for (; isOk && ftit != ftset.end() && stdit != stdset.end(); stdit++, ftit++)
	{
		retft = ftset.upper_bound((*ftit));
		retstd = stdset.upper_bound((*stdit));
		if (retft != ftset.end() && retstd != stdset.end() && !(*retstd == *retft))
			isOk = false;
	}
	if (isOk)
	{
		retft = ftset.upper_bound(typename SETFT::key_type());
		retstd = stdset.upper_bound(typename SETSTD::key_type());
		if (retft != ftset.end() && retstd != stdset.end() && !(*retstd == *retft))
			isOk = false;
		if (isOk)
			return true;
	}
	printSets(stdset, ftset);
	std::cout << "ft::upper_bound return == end()  : " << (retft == ftset.end()) << std::endl;
	std::cout << "std::upper_bound return == end() : " << (retstd == stdset.end()) << std::endl;
	return false;
}

template<typename SETSTD, typename SETFT>
bool constUpperSetTest(const SETSTD& stdset, const SETFT& ftset)
{
	bool							isOk = true;
	typename SETFT::const_iterator	ftit = ftset.begin();
	typename SETSTD::const_iterator	stdit = stdset.begin();
	typename SETFT::const_iterator	retft;
	typename SETSTD::const_iterator	retstd;

	for (; isOk && ftit != ftset.end() && stdit != stdset.end(); stdit++, ftit++)
	{
		retft = ftset.upper_bound((*ftit));
		retstd = stdset.upper_bound((*stdit));
		if (retft != ftset.end() && retstd != stdset.end() && !(*retstd == *retft))
			isOk = false;
	}
	if (isOk)
	{
		retft = ftset.upper_bound(typename SETFT::key_type());
		retstd = stdset.upper_bound(typename SETSTD::key_type());
		if (retft != ftset.end() && retstd != stdset.end() && !(*retstd == *retft))
			isOk = false;
		if (isOk)
			return true;
	}
	printSets(stdset, ftset);
	std::cout << "ft::upper_bound return == end()  : " << (retft == ftset.end()) << std::endl;
	std::cout << "std::upper_bound return == end() : " << (retstd == stdset.end()) << std::endl;
	return false;
}


template<typename SETSTD, typename SETFT>
bool equalSetTest(SETSTD& stdset, SETFT& ftset)
{
	bool							isOk = true;
	typename SETFT::const_iterator	ftit = ftset.begin();
	typename SETSTD::const_iterator	stdit = stdset.begin();
	ft::pair<typename SETFT::iterator, typename SETFT::iterator>	retft;
	std::pair<typename SETSTD::iterator, typename SETSTD::iterator>	retstd;

	for (; isOk && ftit != ftset.end() && stdit != stdset.end(); stdit++, ftit++)
	{
		retft = ftset.equal_range((*ftit));
		retstd = stdset.equal_range((*stdit));
		if ((retft.first != ftset.end() && retstd.first != stdset.end() && !(*retstd.first == *retft.first)) ||
			(retft.second != ftset.end() && retstd.second != stdset.end() && !(*retstd.second == *retft.second)))
			isOk = false;
	}
	if (isOk)
	{
		retft = ftset.equal_range(typename SETFT::key_type());
		retstd = stdset.equal_range(typename SETSTD::key_type());
		if ((retft.first != ftset.end() && retstd.first != stdset.end() && !(*retstd.first == *retft.first)) ||
			(retft.second != ftset.end() && retstd.second != stdset.end() && !(*retstd.second == *retft.second)))
			isOk = false;
		if (isOk)
			return true;
	}
	printSets(stdset, ftset);
	std::cout << "ft::equal_range return  : pair<" << (retft.first == ftset.end() ? (typename SETFT::value_type()) : *retft.first)
			  << ", " << (retft.second == ftset.end() ? (typename SETFT::value_type()) : *retft.second) << std::endl;
	std::cout << "std::equal_range return : pair<" << (retstd.first == stdset.end() ? (typename SETSTD::value_type()) : *retstd.first)
			  << ", " << (retstd.second == stdset.end() ? (typename SETSTD::value_type()) : *retstd.second) << std::endl;
	return false;
}

template<typename SETSTD, typename SETFT>
bool constEqualSetTest(const SETSTD& stdset, const SETFT& ftset)
{
	bool							isOk = true;
	typename SETFT::const_iterator	ftit = ftset.begin();
	typename SETSTD::const_iterator	stdit = stdset.begin();
	ft::pair<typename SETFT::const_iterator, typename SETFT::const_iterator>	retft;
	std::pair<typename SETSTD::const_iterator, typename SETSTD::const_iterator>	retstd;

	for (; isOk && ftit != ftset.end() && stdit != stdset.end(); stdit++, ftit++)
	{
		retft = ftset.equal_range((*ftit));
		retstd = stdset.equal_range((*stdit));
		if ((retft.first != ftset.end() && retstd.first != stdset.end() && !(*retstd.first == *retft.first)) ||
			(retft.second != ftset.end() && retstd.second != stdset.end() && !(*retstd.second == *retft.second)))
			isOk = false;
	}
	if (isOk)
	{
		retft = ftset.equal_range(typename SETFT::key_type());
		retstd = stdset.equal_range(typename SETSTD::key_type());
		if ((retft.first != ftset.end() && retstd.first != stdset.end() && !(*retstd.first == *retft.first)) ||
			(retft.second != ftset.end() && retstd.second != stdset.end() && !(*retstd.second == *retft.second)))
			isOk = false;
		if (isOk)
			return true;
	}
	printSets(stdset, ftset);
	std::cout << "ft::equal_range return  : pair<" << (retft.first == ftset.end() ? (typename SETFT::value_type()) : *retft.first)
			  << ", " << (retft.second == ftset.end() ? (typename SETFT::value_type()) : *retft.second) << std::endl;
	std::cout << "std::equal_range return : pair<" << (retstd.first == stdset.end() ? (typename SETSTD::value_type()) : *retstd.first)
			  << ", " << (retstd.second == stdset.end() ? (typename SETSTD::value_type()) : *retstd.second) << std::endl;
	return false;
}

template <typename T, class F>
bool doSetTest(const T* vtab, size_t size, F* f, std::string test_name)
{
	bool isOk = true;
	{
		FTSET				ftset;
		STDSET				stdset;

		for (size_t i = 0; isOk && i < size; i++)
		{
			isOk = f(stdset, ftset);
			if (!setEqual(stdset, ftset))
				isOk = false;
			stdset.insert(vtab[i]);
			ftset.insert(vtab[i]);
		}
	}
	printSetTest(test_name, isOk);
	return isOk;
}

template <typename T, class F>
bool doConstSetTest(const T* vtab, size_t size, F* f, std::string test_name)
{
	bool isOk = true;
	{
		std::list<T>	lst;
		std::list<T>	lft;

		for (size_t i = 0; i < size; i++)
			lst.push_back(vtab[i]);
		for (size_t i = 0; i < size; i++)
			lft.push_back(vtab[i]);

		for (size_t i = 0; isOk && i < size; i++)
		{
			const std::set<T>	stdset(lst.begin(), lst.end());
			const ft::set<T>		ftset(lft.begin(), lft.end());
			isOk = f(stdset, ftset);
			if (!setEqual(stdset, ftset))
				isOk = false;
		}
	}
	printSetTest(test_name, isOk);
	return isOk;
}

template <typename T>
bool setTest(const T* vTab, size_t size, std::string types)
{
	bool isOk = true;

	printTitle("SET" + types, STR_MAGENTA, 1);


	printTitle("Iterators", STR_BLUE, 0);
	if (!doSetTest<T>(vTab, size, beginSetTest<STDSET, FTSET>, "begin"))
		isOk = false;
	if (!doSetTest<T>(vTab, size, endSetTest<STDSET, FTSET>, "end"))
		isOk = false;
	if (!doConstSetTest<T>(vTab, size, beginConstSetTest<STDSET, FTSET>, "begin const"))
		isOk = false;
	if (!doConstSetTest<T>(vTab, size, endConstSetTest<STDSET, FTSET>, "end const"))
		isOk = false;
	if (!doSetTest<T>(vTab, size, rbeginSetTest<STDSET, FTSET>, "rbegin"))
		isOk = false;
	if (!doSetTest<T>(vTab, size, rendSetTest<STDSET, FTSET>, "rend"))
		isOk = false;
	if (!doConstSetTest<T>(vTab, size, rbeginConstSetTest<STDSET, FTSET>, "rbegin const"))
		isOk = false;
	if (!doConstSetTest<T>(vTab, size, rendConstSetTest<STDSET, FTSET>, "rend const"))
		isOk = false;

	printTitle("capacity", STR_BLUE, 0);
	if(!capacitySetTest<T>(vTab, size))
		isOk = false;

	printTitle("LookUp", STR_BLUE, 0);
	if (!doSetTest<T>(vTab, size, countSetTest<STDSET, FTSET>, "count"))
		isOk = false;
	if (!doSetTest<T>(vTab, size, findSetTest<STDSET, FTSET>, "find"))
		isOk = false;
	if (!doConstSetTest<T>(vTab, size, constFindSetTest<STDSET, FTSET>, "find const"))
		isOk = false;
	if (!doSetTest<T>(vTab, size, lowerSetTest<STDSET, FTSET>, "lower_bound"))
		isOk = false;
	if (!doConstSetTest<T>(vTab, size, constLowerSetTest<STDSET, FTSET>, "lower_bound const"))
		isOk = false;
	if (!doSetTest<T>(vTab, size, upperSetTest<STDSET, FTSET>, "upper_bound"))
		isOk = false;
	if (!doConstSetTest<T>(vTab, size, constUpperSetTest<STDSET, FTSET>, "upper_bound const"))
		isOk = false;
	if (!doSetTest<T>(vTab, size, equalSetTest<STDSET, FTSET>, "equal_range"))
		isOk = false;
	if (!doConstSetTest<T>(vTab, size, constEqualSetTest<STDSET, FTSET>, "equal_range const"))
		isOk = false;

	printTitle("Modifiers", STR_BLUE, 0);
	if (!doSetTest<T>(vTab, size, clearSetTest<STDSET, FTSET>, "clear"))
		isOk = false;

	return isOk;
}

#endif