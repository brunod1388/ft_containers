/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_benchmark.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 05:16:56 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/16 03:05:51 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifdef STD
# define NAMESPACE std
# define NAMESPACE_STR std::string("std")
# include <map>
#else
# define NAMESPACE ft
# define NAMESPACE_STR std::string("ft")
# include "map.hpp"
#endif

#ifndef NB_TEST
# define NB_TEST 1000
#endif

#include <string.h>
#include <stdlib.h>
#include "utils_benchmark.hpp"
#include "map_benchmark.hpp"
#include "tests.hpp"


void fullTest()
{
	printTitle("FULL TEST  (nbTest: 1000)" , STR_BLUE, 1);
	fullMapTest<NAMESPACE::map<int, std::string> >(iTab, strTab, 20, iTabOrder, strTabOrder, 20);
}

int main(int argc, char** argv)
{
	if (argc == 1)
		fullTest();
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