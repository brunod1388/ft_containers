/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_benchmark.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/16 04:18:05 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BENCHMARK_HPP
# define UTILS_BENCHMARK_HPP

#include "tests.hpp"
#include <sys/time.h>
#include <iomanip>

#ifndef NB_TEST
# define NB_TEST 1000
#endif

float operator-(struct timeval& lhs, struct timeval& rhs)
{
	return (lhs.tv_sec - rhs.tv_sec) * 1000000 + (lhs.tv_usec - rhs.tv_usec);
}

template <class Container, class ContFunc>
float containerBenchmark(const Container& cont,
						const Container& cont2,
						ContFunc* fct,
						std::string testName)
{
	Container		tmp[NB_TEST];
	Container		tmp2[NB_TEST];
	struct timeval	t0, t1;

	for (size_t i = 0; i < NB_TEST; i++)
		tmp[i] = Container(cont);
	for (size_t i = 0; i < NB_TEST; i++)
		tmp2[i] = Container(cont2);
	gettimeofday(&t0, NULL);
	for (size_t i = 0; i < NB_TEST; i++)
		fct(tmp[i], tmp2[i]);
	gettimeofday(&t1, NULL);

	float t = t1 - t0;
	std::cout << NAMESPACE_STR << "::" << std::left << std::setw(30) << testName << ": ";
	if (t > 1000000)
		std::cout << std::setw(5) << std::right << t / 1000000.0 << "  s" << std::endl;
	else if (t > 1000)
		std::cout << std::setw(5) << std::right << t / 1000.0 << " ms" << std::endl;
	else
		std::cout << std::setw(5) << std::right << t << " us" << std::endl;
	return t;
}

/* TODO : Compare */
template <class Container, class Container2>
void containerCompareBenchmark(const Container& cont,
							   const Container2& cont2,
							   ContFunc* fct,
							   std::string testName)
{
	Container		tmp[NB_TEST];
	Container		tmp2[NB_TEST];
	struct timeval	t0, t1;

	for (size_t i = 0; i < NB_TEST; i++)
		tmp[i] = Container(cont);
	for (size_t i = 0; i < NB_TEST; i++)
		tmp2[i] = Container(cont2);
	gettimeofday(&t0, NULL);
	for (size_t i = 0; i < NB_TEST; i++)
		fct(tmp[i], tmp2[i]);
	gettimeofday(&t1, NULL);
	float t = t1 - t0;
	std::cout << NAMESPACE_STR << "::" << std::left << std::setw(30) << testName << ": ";
	if (t > 1000000)
		std::cout << std::setw(5) << std::right << t / 1000000.0 << "  s" << std::endl;
	else if (t > 1000)
		std::cout << std::setw(5) << std::right << t / 1000.0 << " ms" << std::endl;
	else
		std::cout << std::setw(5) << std::right << t << " us" << std::endl;
}

#endif