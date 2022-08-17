/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_benchmark.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 05:16:56 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/17 08:34:32 by brunodeoliv      ###   ########.fr       */
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
}

int main(int argc, char** argv)
{
	if (argc == 1)
#if defined(STD) || defined(FT)
		fullTest();
#else
		fullCompareTest();
#endif
	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == std::string("map"))
			std::cout << "I am map" << std::endl;
		else if (std::string(argv[i]) == std::string("vector"))
			std::cout << "I am vector" << std::endl;
		else
			std::cout << "I am nothing like John Snow" << std::endl;
	}

	return 0;
}