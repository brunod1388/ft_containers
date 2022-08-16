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

// template<class Vector>
// void	insertVal_vectorTest(Vector& v, Vector& v2)
// {
// 	Vector	tmp, tmp2;
// 	for (typename Vector::iterator it = v.begin(); it != v.end(); it++)
// 		tmp.insert(*it);
// 	for (typename Vector::iterator it = v2.begin(); it != v2.end(); it++)
// 		tmp2.insert(*it);
// }

// template<class Vector>
// void	insertRange_vectorTest(Vector& v, Vector& v2)
// {
// 	Vector	tmp, tmp2;

// 	tmp.insert(v.begin(), v.end());
// 	tmp2.insert(v2.begin(), v2.end());
// }

// template<class Vector>
// void	insertHint_vectorTest(Vector& v, Vector& v2)
// {
// 	Vector	tmp, tmp2;

// 	for (typename Vector::iterator it = v2.begin(); it != v2.end(); it++)
// 	{
// 		v.insert(v.)
// 	}
	
// }

// template<class Vector>
// void	erasePos_vectorTest(Vector& v, Vector& v2)
// {
// 	while (v.size())
// 		v.erase(v.begin());
// 	while (v2.size())
// 		v2.erase(v2.begin());
// }

// template<class Vector>
// void	eraseVal_vectorTest(Vector& v, Vector& v2)
// {
// 	while (v.size())
// 		v.erase((*v.begin()).first);
// 	while (v2.size())
// 		v2.erase((*v2.begin()).first);
// }

// template<class Vector>
// void	eraseRange_vectorTest(Vector& v, Vector& v2)
// {
// 	v.erase(v.begin(), ++v.begin());
// 	v.erase(v.begin(), --v.end());
// 	v2.erase(v2.begin(), ++v2.begin());
// 	v2.erase(v2.begin(), --v2.end());
// }

template<class Vector>
void	swap_vectorTest(Vector& v, Vector& v2)
{
	v.swap(v2);
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

	/* Capacity */
	containerBenchmark(v, v2, size_vectorTest<Vector>, "vector::size");
	containerBenchmark(v, v2, empty_vectorTest<Vector>, "vector::empty");
	containerBenchmark(v, v2, max_size_vectorTest<Vector>, "vector::max_size");

	/* Iterator */
	containerBenchmark(v, v2, begin_vectorTest<Vector>, "vector::begin");
	containerBenchmark(v, v2, end_vectorTest<Vector>, "vector::end");
	containerBenchmark(v, v2, rbegin_vectorTest<Vector>, "vector::rbegin");
	containerBenchmark(v, v2, rend_vectorTest<Vector>, "vector::rend");

	/* Modifiers */
	// containerBenchmark(v, v2, clear_vectorTest<Vector>, "vector::clear");
	// containerBenchmark(v, v2, insertVal_vectorTest<Vector>, "vector::insert(val)");
	// containerBenchmark(v, v2, insertRange_vectorTest<Vector>, "vector::insert(first, last)");
	// // containerBenchmark(v, v2, insertHint_vectorTest<Vector>, "vector::insert(hint, value)");
	// containerBenchmark(v, v2, eraseVal_vectorTest<Vector>, "vector::erase(key)");
	// containerBenchmark(v, v2, erasePos_vectorTest<Vector>, "vector::erase(pos)");
	// containerBenchmark(v, v2, eraseRange_vectorTest<Vector>, "vector::erase(first, last)");
	// containerBenchmark(v, v2, swap_vectorTest<Vector>, "vector::swap");

	/* LookUp */

}



#endif