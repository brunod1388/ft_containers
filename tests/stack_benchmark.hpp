/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_benchmark.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:24:11 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/16 04:09:08 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_BENCHMARK_HPP
# define STACK_BENCHMARK_HPP

#include "utils_benchmark.hpp"
#include "tests.hpp"
#include "stack.hpp"
#include <stack>
#include <unistd.h>

template<class Stack>
void	size_stackTest(Stack& stk, Stack& stk2)
{
	typename Stack::size_type s = stk.size();
	typename Stack::size_type s2 = stk2.size();
	(void) s;
	(void) s2;
}

template<class Stack>
void	empty_stackTest(Stack& stk, Stack& stk2)
{
	typename Stack::size_type s = stk.empty();
	typename Stack::size_type s2 = stk2.empty();
	(void) s;
	(void) s2;
}

template<class Stack>
void	top_stackTest(Stack& stk, Stack& stk2)
{
	typename Stack::value_type s = stk.top();
	typename Stack::value_type s2 = stk2.top();
	(void) s;
	(void) s2;
}

template<class Stack>
void	push_stackTest(Stack& v, Stack& v2)
{
	typename Stack::value_type	val = v2.top();

	for (size_t i = 0; i < 50; i++)
		v.push(val);
}

template<class Stack>
void	pop_stackTest(Stack& v, Stack& v2)
{
	while (v.size())
		v.pop();
	while (v2.size())
		v2.pop();
}

template<class Stack>
void	swap_stackTest(Stack& v, Stack& v2)
{
	v.swap(v2);
}

template<class Stack>
typename Stack::container_type	constructVector(typename Stack::value_type* vTab, size_t size)
{
	typename Stack::container_type v;

	for (size_t i = 0; i < size; i++)
		v.push_back(vTab[i]);
	return v;
}

template <class Stack>
void	fullStackTest(typename Stack::value_type* vTab, size_t size,
					   typename Stack::value_type* vTab2, size_t size2)
{
	std::vector<typename Stack::value_type> v = constructVector<Stack>(vTab, size);
	std::vector<typename Stack::value_type> v2 = constructVector<Stack>(vTab2, size2);

	Stack	s(v);
	Stack	s2(v2);

	containerBenchmark(s, s2, size_stackTest<Stack>, "stack::size");
	containerBenchmark(s, s2, empty_stackTest<Stack>, "stack::empty");
	containerBenchmark(s, s2, top_stackTest<Stack>, "stack::top");
	containerBenchmark(s, s2, pop_stackTest<Stack>, "stack::pop");
	containerBenchmark(s, s2, push_stackTest<Stack>, "stack::push");
}

template <typename T>
void	fullBothStackTest(T* vTab, size_t size, T* vTab2, size_t size2)
{
	std::cout << STR_MAGENTA << "Test" << std::setw(46) << "ft Time" << std::setw(13)
			  << "std Time" << std::setw(10) << "Ratio" << STR_RESET << std::endl;
	typename std::stack<T>::container_type vx = constructVector<typename std::stack<T> >(vTab, size);
	typename std::stack<T>::container_type vx2 = constructVector<typename std::stack<T> >(vTab2, size2);
	ft::vector<T> ftvx = constructVector<ft::stack<T> >(vTab, size);
	ft::vector<T> ftvx2 = constructVector<ft::stack<T> >(vTab2, size2);

	std::stack<T>	stdv(vx);
	std::stack<T>	stdv2(vx2);
	ft::stack<T>	ftv(ftvx);
	ft::stack<T>	ftv2(ftvx2);

	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, size_stackTest<std::stack<T> >, size_stackTest<ft::stack<T> >, "stack::size");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, empty_stackTest<std::stack<T> >, empty_stackTest<ft::stack<T> >, "stack::empty");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, top_stackTest<std::stack<T> >, top_stackTest<ft::stack<T> >, "stack::top");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, pop_stackTest<std::stack<T> >, pop_stackTest<ft::stack<T> >, "stack::pop");
	containerCompareBenchmark(stdv, stdv2, ftv, ftv2, push_stackTest<std::stack<T> >, push_stackTest<ft::stack<T> >, "stack::push");

}

#endif