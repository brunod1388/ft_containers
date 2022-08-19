/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_benchmark.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:24:11 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/16 04:09:08 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_BENCHMARK_HPP
# define VECTOR_BENCHMARK_HPP

#include "utils_benchmark.hpp"
#include "tests.hpp"
#include "vector.hpp"
#include <vector>
#include <unistd.h>

template<class Vector>
void	at_vectorTest(Vector& v, Vector& v2)
{
	for (size_t i = 0; i < v.size(); i++)
		v.at(i);
	for (size_t i = 0; i < v.size(); i++)
		v2.at(i);
}

template<class Vector>
void	brackets_vectorTest(Vector& v, Vector& v2)
{
	for (size_t i = 0; i < v.size(); i++)
		v[i];
	for (size_t i = 0; i < v.size(); i++)
		v2[i];
}

template<class Vector>
void	front_vectorTest(Vector& v, Vector& v2)
{
	typename Vector::const_reference	a = v.front();
	typename Vector::const_reference	b = v2.front();
	(void) a;
	(void) b;
}

template<class Vector>
void	back_vectorTest(Vector& v, Vector& v2)
{
	typename Vector::const_reference	a = v.back();
	typename Vector::const_reference	b = v2.back();
	(void) a;
	(void) b;
}

template<class Vector>
void	data_vectorTest(Vector& v, Vector& v2)
{
	typename Vector::const_pointer	a = v.data();
	typename Vector::const_pointer	b = v2.data();
	(void) a;
	(void) b;
}

template<class Vector>
void	size_vectorTest(Vector& v, Vector& v2)
{
	typename Vector::size_type s = v.size();
	(void) s;
	(void) v2;
}

template<class Vector>
void	empty_vectorTest(Vector& v, Vector& v2)
{
	typename Vector::size_type s = v.empty();
	(void) s;
	(void) v2;
}

template<class Vector>
void	max_size_vectorTest(Vector& v, Vector& v2)
{
	typename Vector::size_type s = v.max_size();
	(void) s;
	(void) v2;
}

template<class Vector>
void	capacity_vectorTest(Vector& v, Vector& v2)
{
	typename Vector::size_type s = v.capacity();
	typename Vector::size_type s2 = v2.capacity();
	(void) s;
	(void) s2;
}

template<class Vector>
void	reserve_vectorTest(Vector& v, Vector& v2)
{
	v.reserve(NB_TEST * 2);
	v2.reserve(NB_TEST * 2);
}

template<class Vector>
void	begin_vectorTest(Vector& v, Vector& v2)
{
	typename Vector::iterator it = v.begin();
	typename Vector::iterator it2 = v2.begin();
	(void) it;
	(void) it2;
}

template<class Vector>
void	end_vectorTest(Vector& v, Vector& v2)
{
	typename Vector::iterator it = v.end();
	typename Vector::iterator it2 = v2.end();
	(void) it;
	(void) it2;
}

template<class Vector>
void	rbegin_vectorTest(Vector& v, Vector& v2)
{
	typename Vector::reverse_iterator it = v.rbegin();
	typename Vector::reverse_iterator it2 = v2.rbegin();
	(void) it;
	(void) it2;
}

template<class Vector>
void	rend_vectorTest(Vector& v, Vector& v2)
{
	typename Vector::reverse_iterator it = v.rend();
	typename Vector::reverse_iterator it2 = v2.rend();
	(void) it;
	(void) it2;
}

template<class Vector>
void	clear_vectorTest(Vector& v, Vector& v2)
{
	v.clear();
	v2.clear();
}

template<class Vector>
void	insertVal_vectorTest(Vector& v, Vector& v2)
{
	Vector	tmp, tmp2;
	for (typename Vector::iterator it = v.begin(); it != v.end(); it++)
		tmp.insert(tmp.begin(), *it);
	for (typename Vector::iterator it = v2.begin(); it != v2.end(); it++)
		tmp2.insert(tmp2.begin(), *it);
}

template<class Vector>
void	insertCountVal_vectorTest(Vector& v, Vector& v2)
{
	Vector	tmp, tmp2;
	for (typename Vector::iterator it = v.begin(); it != v.end(); it++)
		tmp.insert(tmp.begin(), 3, *it);
	for (typename Vector::iterator it = v2.begin(); it != v2.end(); it++)
		tmp2.insert(tmp2.begin(), 7, *it);
}

template<class Vector>
void	insertRange_vectorTest(Vector& v, Vector& v2)
{
	if (v.size() < 3 || v2.size() < 3)
		return;
	Vector	tmp(v.begin(), ++v.begin());
	Vector	tmp2(v2.begin(), ++v2.begin());

	tmp.insert(tmp.begin(), v.begin(), v.end());
	tmp2.insert(tmp2.begin(), v2.begin(), v2.end());
}

template<class Vector>
void	erasePos_vectorTest(Vector& v, Vector& v2)
{
	while (v2.size())
		v2.erase(v2.begin());
	(void) v;
}

template<class Vector>
void	eraseRange_vectorTest(Vector& v, Vector& v2)
{
	if (v.size() < 3 || v2.size() < 3)
		return;
	v.erase(v.begin(), ++v.begin());
	v2.erase(v2.begin(), ++v2.begin());
}

template<class Vector>
void	resize_vectorTest(Vector& v, Vector& v2)
{
	v.resize(v.size() * 5);
	v2.resize(v2.size() * 3);
}

template<class Vector>
void	swap_vectorTest(Vector& v, Vector& v2)
{
	v.swap(v2);
}

template<class Vector>
void	push_back_vectorTest(Vector& v, Vector& v2)
{
	Vector	tmp, tmp2;
	for (typename Vector::iterator it = v.begin(); it != v.end(); it++)
		tmp.push_back(*it);
	for (typename Vector::iterator it = v2.begin(); it != v2.end(); it++)
		tmp2.push_back(*it);
}

template<class Vector>
void	pop_back_vectorTest(Vector& v, Vector& v2)
{
	size_t size = v.size();
	for (size_t i = 0; i < size; i++)
		v.pop_back();
	size = v2.size();
	for (size_t i = 0; i < size; i++)
		v2.pop_back();
}

template<class Vector>
std::list<typename Vector::value_type>	constructList(typename Vector::value_type* vTab, size_t size)
{
	std::list<typename Vector::value_type> lst;

	for (size_t i = 0; i < size; i++)
		lst.push_back(typename Vector::value_type(vTab[i]));
	return lst;
}

template <class Vector>
void	fullVectorTest(typename Vector::value_type* vTab, size_t size,
					   typename Vector::value_type* vTab2, size_t size2)
{
	std::list<typename Vector::value_type> lst = constructList<Vector>(vTab, size);
	std::list<typename Vector::value_type> lst2 = constructList<Vector>(vTab2, size2);

	Vector	v(lst.begin(), lst.end());
	Vector	v2(lst2.begin(), lst2.end());

	/* Element Access */
	containerBenchmark(v, v2, at_vectorTest<Vector>, "vector::at");
	containerBenchmark(v, v2, brackets_vectorTest<Vector>, "vector::[]");
	containerBenchmark(v, v2, front_vectorTest<Vector>, "vector::front");
	containerBenchmark(v, v2, back_vectorTest<Vector>, "vector::back");
	containerBenchmark(v, v2, data_vectorTest<Vector>, "vector::data");

	/* Capacity */
	containerBenchmark(v, v2, size_vectorTest<Vector>, "vector::size");
	containerBenchmark(v, v2, empty_vectorTest<Vector>, "vector::empty");
	containerBenchmark(v, v2, max_size_vectorTest<Vector>, "vector::max_size");
	containerBenchmark(v, v2, capacity_vectorTest<Vector>, "vector::capacity");
	containerBenchmark(v, v2, reserve_vectorTest<Vector>, "vector::reserve");

	/* Iterator */
	containerBenchmark(v, v2, begin_vectorTest<Vector>, "vector::begin");
	containerBenchmark(v, v2, end_vectorTest<Vector>, "vector::end");
	containerBenchmark(v, v2, rbegin_vectorTest<Vector>, "vector::rbegin");
	containerBenchmark(v, v2, rend_vectorTest<Vector>, "vector::rend");

	/* Modifiers */
	containerBenchmark(v, v2, clear_vectorTest<Vector>, "vector::clear");
	containerBenchmark(v, v2, insertVal_vectorTest<Vector>, "vector::insert(pos, val)");
	containerBenchmark(v, v2, insertCountVal_vectorTest<Vector>, "vector::insert(pos, count, value)");
	// containerBenchmark(v, v2, insertRange_vectorTest<Vector>, "vector::insert(first, last)");
	containerBenchmark(v, v2, erasePos_vectorTest<Vector>, "vector::erase(pos)");
	containerBenchmark(v, v2, eraseRange_vectorTest<Vector>, "vector::erase(first, last)");
	containerBenchmark(v, v2, push_back_vectorTest<Vector>, "vector::push_back");
	containerBenchmark(v, v2, pop_back_vectorTest<Vector>, "vector::pop_back");
	containerBenchmark(v, v2, resize_vectorTest<Vector>, "vector::resize");
	containerBenchmark(v, v2, swap_vectorTest<Vector>, "vector::swap");
}

template <typename T>
void	fullBothVectorTest(T* vTab, size_t size, T* vTab2, size_t size2)
{
	std::cout << STR_MAGENTA << "Test" << std::setw(46) << "ft Time" << std::setw(13)
			  << "std Time" << std::setw(10) << "Ratio" << STR_RESET << std::endl;
	std::list<typename std::vector<T>::value_type> lst = constructList<std::vector<T> >(vTab, size);
	std::list<typename std::vector<T>::value_type> lst2 = constructList<std::vector<T> >(vTab2, size2);
	std::list<typename std::vector<T>::value_type> ftlst = constructList<ft::vector<T> >(vTab, size);
	std::list<typename std::vector<T>::value_type> ftlst2 = constructList<ft::vector<T> >(vTab2, size2);

	std::vector<T>	stdv(lst.begin(), lst.end());
	std::vector<T>	stdv2(lst2.begin(), lst2.end());
	ft::vector<T>	ftv(ftlst.begin(), ftlst.end());
	ft::vector<T>	ftv2(ftlst2.begin(), ftlst2.end());

	/* Element Access */
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, at_vectorTest<std::vector<T> >, at_vectorTest<ft::vector<T> >, "vector::at");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, brackets_vectorTest<std::vector<T> >, brackets_vectorTest<ft::vector<T> >, "vector::[]");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, front_vectorTest<std::vector<T> >, front_vectorTest<ft::vector<T> >, "vector::front");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, back_vectorTest<std::vector<T> >, back_vectorTest<ft::vector<T> >, "vector::back");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, data_vectorTest<std::vector<T> >, data_vectorTest<ft::vector<T> >, "vector::data");

	/* Capacity */
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, size_vectorTest<std::vector<T> >, size_vectorTest<ft::vector<T> >, "vector::size");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, empty_vectorTest<std::vector<T> >, empty_vectorTest<ft::vector<T> >, "vector::empty");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, max_size_vectorTest<std::vector<T> >, max_size_vectorTest<ft::vector<T> >, "vector::max_size");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, capacity_vectorTest<std::vector<T> >, capacity_vectorTest<ft::vector<T> >, "vector::capacity");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, reserve_vectorTest<std::vector<T> >, reserve_vectorTest<ft::vector<T> >, "vector::reserve");

	/* Iterator */
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, begin_vectorTest<std::vector<T> >, begin_vectorTest<ft::vector<T> >, "vector::begin");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, end_vectorTest<std::vector<T> >, end_vectorTest<ft::vector<T> >, "vector::end");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, rbegin_vectorTest<std::vector<T> >, rbegin_vectorTest<ft::vector<T> >, "vector::rbegin");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, rend_vectorTest<std::vector<T> >, rend_vectorTest<ft::vector<T> >, "vector::rend");

	/* Modifiers */
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, clear_vectorTest<std::vector<T> >, clear_vectorTest<ft::vector<T> >, "vector::clear");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, insertVal_vectorTest<std::vector<T> >, insertVal_vectorTest<ft::vector<T> >, "vector::insert(pos, val)");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, insertCountVal_vectorTest<std::vector<T> >, insertCountVal_vectorTest<ft::vector<T> >, "vector::insert(pos, count, value)");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, insertRange_vectorTest<std::vector<T> >, insertRange_vectorTest<ft::vector<T> >, "vector::insert(first, last)");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, erasePos_vectorTest<std::vector<T> >, erasePos_vectorTest<ft::vector<T> >, "vector::erase(pos)");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, eraseRange_vectorTest<std::vector<T> >, eraseRange_vectorTest<ft::vector<T> >, "vector::erase(first, last)");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, push_back_vectorTest<std::vector<T> >, push_back_vectorTest<ft::vector<T> >, "vector::push_back");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, pop_back_vectorTest<std::vector<T> >, pop_back_vectorTest<ft::vector<T> >, "vector::pop_back");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, resize_vectorTest<std::vector<T> >, resize_vectorTest<ft::vector<T> >, "vector::resize");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, swap_vectorTest<std::vector<T> >, swap_vectorTest<ft::vector<T> >, "vector::swap");
}

#endif