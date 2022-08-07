/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:25:28 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/06 20:21:43 by brunodeoliv      ###   ########.fr       */
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

// template< class T1, class T2 >
// std::ostream &operator<<(std::ostream &os, const std::pair<T1,T2>& rhs )
// {
// 	os << "(" << rhs.first << ", " << rhs.second << ")";
// 	return os;
// }

template <typename K, typename T>
void	print(const std::map<K, T>& m)
{
	for (typename std::map<K, T>::iterator i = m.begin(); i != m.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	std::cout << "size :" << m.size();
}

// template <class M>
// void	print(const M& m)
// {
// 	for (typename M::const_iterator i = m.begin(); i != m.end(); i++)
// 		std::cout << *i << " ";
// 	std::cout << std::endl;
// 	std::cout << "size :" << m.size();
//	}

		// void	print() const
		// {
		// 	for (iterator i = begin(); i != end(); i++)
		// 	{
		// 		std::cout << *i << " ";
		// 	}
		// 	std::cout << std::endl;
		// 	std::cout << "size :" << _tree.size() << std::endl;
		// }

template <typename K, typename T>
void capacityTest(K* ktab, T* vtab, size_t size)
{
	ft::map<K, T>	ftmap;
	std::map<K, T>	stdmap;

	for (size_t i = 0; i < size; i++)
	{
		// stdmap.insert(std::pair<K, T>(ktab[i], vtab[i]));
		ftmap.insert(ft::pair<K, T>(ktab[i], vtab[i]));
		// if (ftmap.size() != stdmap.size())
		// {
		// 	print(stdmap);
		// 	print(ftmap);
		// }
	}

	std::cout << "ftmap  size: " << ftmap.size() << std::endl;
	std::cout << "stdmap size: " << stdmap.size() << std::endl;

}

template <typename K, typename T>
void mapTest(K* ktab, T* vtab, size_t size)
{

	std::cout << "===================================================================" <<std::endl
			  << "====                        Capacity                           ====" <<std::endl
			  << "===================================================================" <<std::endl;
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