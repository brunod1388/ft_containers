/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:38:25 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/18 05:04:53 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TEST 0
#include "tests.hpp"
#include "vector.hpp"
#include "vector_test.hpp"
#include "map_test.hpp"
#include "set_test.hpp"
#include <vector>
#include <list>

int main( void )
{
	bool	vectorOk, mapOk, setOk;

	vectorOk = vectorTest<std::string>(strTab, 7, "string") && vectorTest<int>(iTab, 7, "int");
	mapOk = mapTest<int, std::string>(iTab, strTab, 7, "<int, std::string>") && mapTest<std::string, int>(strTab, iTab, 7, "<std::string, int>");
	setOk = setTest<int>(iTab, 7, "<int, std::string>") && setTest<std::string>(strTab, 7, "<std::string, int>");

	printTitle("Summary", STR_GREEN);
	std::cout << "Vector : " << (vectorOk ? OK : NOTOK) << std::endl;
	std::cout << "Map    : " << (mapOk ? OK : NOTOK) << std::endl;
	std::cout << "Set    : " << (setOk ? OK : NOTOK) << std::endl;
	if (TEST)
		while(42);
	return 0;
}