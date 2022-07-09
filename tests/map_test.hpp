/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:25:28 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/07/09 02:36:33 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TESTS_HPP
# define MAP_TESTS_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include "vector.hpp"
#include "tests.hpp"
#include <list>

template< class T, class Alloc >
std::ostream &operator<<( std::ostream &os, const std::vector<T, Alloc>& rhs )
{
	os << "(";
	for (size_t i = 0; i < rhs.size(); i++)
		os << rhs[i] << (i < rhs.size() - 1 ? ", " : "");
	os << ")";
	return os;
}

template <class V>
void printVecInfo(V &v, std::string name, int flag = ALL)
{
	if (!flag)
		return ;
	std::cout << std::left << std::setw(14) << name + "::vector :";

	if (flag & SIZE)
		std::cout << "size:" << std::setw(5) << v.size() << "  ";
	if (flag & CAPACITY)
		std::cout << "capacity:" << std::setw(5) << v.capacity() << "  ";
	if (flag & DATA)
		std::cout << "data:" << std::setw(15) << v.data()  << "  ";
	if (v.size() && flag >= FRONT)
	{
		if (flag & FRONT)
			std::cout << "front:" << std::setw(5) << v.front() << "  ";
		if (flag & BACK)
			std::cout << "back:" << std::setw(5) << v.back() << "  ";
		if (flag & BEGIN)
			std::cout << "*begin:" << std::setw(5) << *v.begin() << "  ";
		if (flag & ENDMIN1)
			std::cout << "*(end-1):" << std::setw(5) << *(v.end() - 1) << "  ";
		if (flag & END)
			std::cout << "*(end):" << std::setw(5) << *v.end() << "  ";
	}
	std::cout << std::endl;
}

template <class V1, class V2>
void print_vector(V1 &v,
				  V2 &v2,
				  std::string testName,
				  int flag = ALL,
				  std::string name1 = "ft",
				  std::string name2 = "std")
{
	std::cout << std::endl << BOLDRED << "FAIL on " << testName << RESET << std::endl;
	std::cout << "Details:" <<std::endl;
	std::cout << std::left << std::setw(10) << name1 + "::v : " << v << std:: endl;
	std::cout << std::left << std::setw(10) << name2 + "::v : "<< v2 << std::endl;

	if (NOFLAG)
		return ;
	printVecInfo(v, name1, flag);
	printVecInfo(v2, name2, flag);
}

template <class V1, class V2>
bool	isEqual(const V1& v1, const V2& v2)
{
	if (v1.size() != v2.size())
		return false;

	bool	ret = true;

	try
	{
		for (size_t i = 0; i < v2.size(); i++)
			if (v1[i] != v2[i])
			{
				*(&ret) = false;
				break ;
			}
	}
	catch(const std::exception& e)
	{
		std::cerr << "error happened : " << e.what() << '\n';
		*(&ret) = false;
	}
	return ret;
}

template <class V1, class V2, typename T>
void	constructVector(int (*f) (V1& , V2&, std::string),
						T* tab,
						size_t size,
						std::string testName)
{
	V1				v1;
	V2				v2;
	bool			isOk = true;
	std::list<T>	lst;

	for (size_t i = 0; i < size; i++)
		lst.push_back(tab[i]);

	if (f(v1, v2, testName + " EmptyVect"))
		isOk = false;

	for (size_t i = 0; i < size && isOk; i++)
	{
		v1.push_back(tab[i]);
		v2.push_back(tab[i]);

		if (isOk && (f(v1, v2, testName + " push 1 element") || !isEqual(v1, v2)))
			isOk = false;
	}

	while (v1.size() || v2.size())
	{
		if(v1.size())
			v1.pop_back();
		if(v2.size())
			v2.pop_back();
		if (isOk && (f(v1, v2, testName + " pop 1 element") || !isEqual(v1, v2)))
			isOk = false;
	}

	for (size_t i = 0; i < size && isOk; i++)
	{
		v1.push_back(tab[i]);
		v2.push_back(tab[i]);
	}

	if (isOk && (f(v1, v2, testName + " push 1 element") || !isEqual(v1, v2)))
		isOk = false;

	while (isOk && (v1.size() || v2.size()))
	{
		if(v1.size())
			v1.pop_back();
		if(v2.size())
			v2.pop_back();
	}
	if (isOk && (f(v1, v2, testName + " pop 1 element") || !isEqual(v1, v2)))
		isOk = false;

	if (!isOk)
		std::cout << std::endl;
	std::cout << BLUE << std::left << std::setw(30) << testName + " : " << (isOk ? OK : NOTOK) << RESET << std::endl;
}

/*===================================================================*/
/*====                                                           ====*/
/*====                        Capacity                           ====*/
/*====                                                           ====*/
/*===================================================================*/

template <class V1, class V2>
int	vectorTest_size(V1& v1, V2& v2, std::string testName)
{
	if (v1.size() != v2.size())
	{
		print_vector(v1, v2, testName, SIZE);
		return 1;
	}
	return 0;
}

template <class V1, class V2>
int	vectorTest_empty(V1& v1, V2& v2, std::string testName)
{
	if (v1.empty() != v2.empty())
	{
		print_vector(v1, v2, testName, SIZE);
		return 1;
	}
	return 0;
}

template <class V1, class V2>
int	vectorTest_max_size(V1& v1, V2& v2, std::string testName)
{
	if (v1.max_size() != v2.max_size())
	{
		print_vector(v1, v2, testName, NOFLAG);
		return 1;
	}
	return 0;
}

template <class V1, class V2>
int	vectorTest_capacity(V1& v1, V2& v2, std::string testName)
{
	if (v1.capacity() != v2.capacity())
	{
		print_vector(v1, v2, testName, SIZE | CAPACITY);
		return 1;
	}
	return 0;
}

template <class V1, class V2>
int	vectorTest_reserve(V1& v1, V2& v2, std::string testName)
{
	v1.reserve(v1.size() * 3);
	v2.reserve(v1.size() * 3);
	if (v1.capacity() != v2.capacity())
	{
		print_vector(v1, v2, testName, SIZE | CAPACITY);
		return 1;
	}
	return 0;
}

/*===================================================================*/
/*====                                                           ====*/
/*====                        modifiers                          ====*/
/*====                                                           ====*/
/*===================================================================*/

template <class V1, class V2>
int	vectorTest_clear(V1& v1, V2& v2, std::string testName)
{
	v1.clear();
	v2.clear();
	if (v1.size() != v2.size())
	{
		print_vector(v1, v2, testName, SIZE | CAPACITY);
		return 1;
	}
	return 0;
}

template <class V1, class V2>
int	vectorTest_insertVal(V1& v1, V2& v2, std::string testName)
{

	if (v1.size() == 0 && v2.size() == 0)
		return 0;
	if (v1.size() == 0 || v2.size() == 0)
		return 1;

	typename	V1::value_type	el = v1[0];
	bool		isOk = true;

	for (size_t i = 0; i < 3; i++)
	{
		v2.insert(v2.begin(), el);
		v1.insert(v1.begin(), el);
	}

	if (!isEqual(v1, v2))
		isOk = false;
	for (size_t i = 0; i < 3; i++)
	{
		v1.insert(v1.end(), el);
		v2.insert(v2.end(), el);
	}
	if (!isEqual(v1, v2))
		isOk = false;
	for (size_t i = 0; i < 6; i++)
	{
		if(v1.size())
			v1.pop_back();
		if(v2.size())
			v2.pop_back();
	}
	if (!isOk)
	{
		print_vector(v1, v2, testName, SIZE | CAPACITY);
		return 1;
	}
	return 0;
}

template <class V1, class V2>
void	print_It(typename V1::const_reverse_iterator it1,
				 typename V2::const_reverse_iterator it2,
				 std::string name1 = "ft",
				 std::string name2 = "std")
{
	std::cout << name1 << "::reverse iterator * : " << *it1 << std::endl;
	std::cout << name2 << "::reverse iterator * : " << *it2 << std::endl;
}

template <class V1, class V2>
int	vectorTest_reverseIterator(V1& v1, V2& v2, std::string testName)
{
	bool	isOk = true;

	if (v1.size() == 0 && v2.size() == 0)
		return 0;
	if (v1.size() == 0 || v2.size() == 0)
		return 1;

	{
		typename V1::reverse_iterator rit1 = v1.rbegin();
		typename V2::reverse_iterator rit2 = v2.rbegin();
		while (rit1 != v1.rend() && rit2 != v2.rend())
		{
			if (*rit1 != *rit2)
			{
				print_vector(v1, v2, testName + "(rIt++)");
				print_It<V1, V2>(rit1, rit2);
				isOk = false;
				break ;
			}
			if (*(rit1++) != *(rit2++))
			{
				std::cout << std::endl << BOLDRED << "FAIL on rit++" << RESET << std::endl;
				print_It<V1, V2>(rit1, rit2);
				isOk = false;
				break;
			}
		}
	}

	if (isOk)
	{
		typename V1::const_reverse_iterator rit1 = v1.rbegin();
		typename V2::const_reverse_iterator rit2 = v2.rbegin();
		while (rit1 != v1.rend() && rit2 != v2.rend())
		{
			if (*rit1 != *rit2)
			{
				print_vector(v1, v2, testName + "(const_rIt++)");
				print_It<V1, V2>(rit1, rit2);
				isOk = false;
				break ;
			}
			if (*(rit1++) != *(rit2++))
			{
				std::cout << std::endl << BOLDRED << "FAIL on const_rit++" << RESET << std::endl;
				print_It<V1, V2>(rit1, rit2);
				isOk = false;
				break;
			}
		}
	}

	if (isOk)
	{
		typename V1::reverse_iterator rit1 = v1.rend() - 1;
		typename V2::reverse_iterator rit2 = v2.rend() - 1;
		while (rit1 != v1.rbegin() && rit2 != v2.rbegin())
		{
			if (*rit1 != *rit2)
			{
				print_vector(v1, v2, testName + "(rIt--)");
				print_It<V1, V2>(rit1, rit2);
				isOk = false;
				break ;
			}
			if (*(rit1--) != *(rit2--))
			{
				std::cout << std::endl << BOLDRED << "FAIL on rit--" << RESET << std::endl;
				print_It<V1, V2>(rit1, rit2);
				isOk = false;
				break;
			}
		}
	}

	if (isOk)
	{
		typename V1::const_reverse_iterator rit1 = v1.rend() - 1;
		typename V2::const_reverse_iterator rit2 = v2.rend() - 1;
		while (rit1 != v1.rbegin() && rit2 != v2.rbegin())
		{
			if (*rit1 != *rit2)
			{
				print_vector(v1, v2, testName + "(const_rIt--)");
				print_It<V1, V2>(rit1, rit2);
				isOk = false;
				break ;
			}
			if (*(rit1--) != *(rit2--))
			{
				std::cout << std::endl << BOLDRED << "FAIL on const_rit--" << RESET << std::endl;
				print_It<V1, V2>(rit1, rit2);
				isOk = false;
				break;
			}
		}
	}
	return (!isOk);
}

template <typename T>
void vectorTest(T* tab, size_t size, std::string type)
{


	// std::cout << "===================================================================" <<std::endl
	// 		  << "====                        Capacity                           ====" <<std::endl
	// 		  << "===================================================================" <<std::endl;
	// constructVector<ft::vector<T>, std::vector<T>, T>(
	// 	vectorTest_size< ft::vector<T>, std::vector<T> >, tab, size, "size(" + type + ")");
	// constructVector<ft::vector<T>, std::vector<T>, T>(
	// 	vectorTest_empty< ft::vector<T>, std::vector<T> >, tab, size, "empty(" + type + ")");
	// constructVector<ft::vector<T>, std::vector<T>, T>(
	// 	vectorTest_max_size< ft::vector<T>, std::vector<T> >, tab, size, "max_size(" + type + ")");
	// constructVector<ft::vector<T>, std::vector<T>, T>(
	// 	vectorTest_capacity< ft::vector<T>, std::vector<T> >, tab, size, "capacity(" + type + ")");
	// constructVector<ft::vector<T>, std::vector<T>, T>(
	// 	vectorTest_reserve< ft::vector<T>, std::vector<T> >, tab, size, "reserve(" + type + ")");

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