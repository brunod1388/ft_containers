/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_benchmark.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 05:16:56 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/18 05:11:11 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifdef STD
# define NAMESPACE std
# define NAMESPACE_STR std::string("std")
# include <map>
# include <vector>
#else
# define NAMESPACE ft
# define NAMESPACE_STR std::string("ft")
# include "map.hpp"
# include "set.hpp"
# include "stack.hpp"
# include "vector.hpp"
#endif

#ifndef NB_TEST
# define NB_TEST 1000
#endif

#include <string.h>
#include <stdlib.h>
#include "utils_benchmark.hpp"
#include "map_benchmark.hpp"
#include "set_benchmark.hpp"
#include "stack_benchmark.hpp"
#include "vector_benchmark.hpp"
#include "tests.hpp"

void fullTest()
{
	printTitle("FULL TEST" , STR_BLUE, 1);
	fullMapTest<NAMESPACE::map<int, std::string> >(iTab, strTab, 20, iTabOrder, strTabOrder, 20);
	std::cout << std::endl;
	fullVectorTest<NAMESPACE::vector<int> >(iTab, 20, iTabOrder, 20);
}

void fullCompareTest()
{
	printTitle("FULL COMPARE TEST" , STR_BLUE, 1);
	printTitle("Vector<int>" , STR_CYAN, 0);
	fullBothVectorTest<int>(iTab, 20, iTabOrder, 20);
	printTitle("Vector<std::string>" , STR_CYAN, 0);
	fullBothVectorTest<std::string>(strTab, 20, strTabOrder, 20);
	printTitle("Map<std::string, int>" , STR_CYAN, 0);
	fullBothMapTest<std::string, int>(strTab, iTab, 20, strTabOrder, iTabOrder, 20);
	printTitle("Map<int, std::string>" , STR_CYAN, 0);
	fullBothMapTest<int, std::string>(iTab, strTab, 20, iTabOrder, strTabOrder, 20);
	printTitle("Set<int>" , STR_CYAN, 0);
	fullBothSetTest<int>(iTab, 20, iTabOrder, 20);
	printTitle("Set<std::string>" , STR_CYAN, 0);
	fullBothSetTest<std::string>(strTab, 20, strTabOrder, 20);
	printTitle("stack<int>" , STR_CYAN, 0);
	fullBothStackTest<int>(iTab, 20, iTabOrder, 20);
	printTitle("stack<std::string>" , STR_CYAN, 0);
	fullBothStackTest<std::string>(strTab, 20, strTabOrder, 20);
}

int main(void)
{
#if defined(STD) || defined(FT)
		fullTest();
#else
		fullCompareTest();
#endif
	return 0;
}