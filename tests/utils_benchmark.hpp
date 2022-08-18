/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_benchmark.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/18 05:35:10 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BENCHMARK_HPP
# define UTILS_BENCHMARK_HPP

#include "tests.hpp"
#include <sys/time.h>
#include <string>
#include <iomanip>
#include <iostream>

#ifndef NB_TEST
# define NB_TEST 1000
#endif

float operator-(struct timeval& lhs, struct timeval& rhs)
{
	return (lhs.tv_sec - rhs.tv_sec) * 1000000 + (lhs.tv_usec - rhs.tv_usec);
}

template <class Container, class ContFunc>
float	timeTest(const Container& cont,
				 const Container& cont2,
				 ContFunc* fct)
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

	return t1 - t0;
}

template <class Container, class ContFunc>
float containerBenchmark(const Container& cont,
						const Container& cont2,
						ContFunc* fct,
						std::string testName)
{
	float t = timeTest(cont, cont2, fct);

	std::cout << NAMESPACE_STR << "::" << std::left << std::setw(30) << testName << ": ";
	if (t > 1000000)
		std::cout << std::setw(5) << std::right << t / 1000000.0 << "  s" << std::endl;
	else if (t > 1000)
		std::cout << std::setw(5) << std::right << t / 1000.0 << " ms" << std::endl;
	else
		std::cout << std::setw(5) << std::right << t << " us" << std::endl;
	return t;
}

template <class STDCont, class FTCont, class STDContFunc, class FTContFunc>
void containerCompareBenchmark(const STDCont& stdCont,
							   const STDCont& stdCont2,
							   const FTCont& ftCont,
							   const FTCont& ftCont2,
							   STDContFunc* stdFct,
							   FTContFunc* ftFct,
							   std::string testName)
{
	float	stdT = timeTest(stdCont, stdCont2, stdFct);
	float	ftT = timeTest(ftCont, ftCont2, ftFct);
	float	ratio = ftT / stdT;

	std::cout << std::left << std::setw(37) << testName;
	std::cout << std::setw(10) << std::right << Time(ftT) << std::setw(10) << std::right << Time(stdT)
			  << std::setw(10) << std::fixed << std::setprecision(3) << (ratio > 20 ? STR_RED : (ratio > 1 ? STR_YELLOW : STR_GREEN))
			  << ratio <<  STR_RESET << "  " << (ratio > 20 ? SKULL : "") << (ratio < 1 ? STAR : "") << std::endl;
}

#endif