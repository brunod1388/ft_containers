/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:38:25 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/16 04:38:22 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TEST 0
#include "tests.hpp"
#include "vector.hpp"
#include "vector_test.hpp"
#include "map_test.hpp"
#include <vector>
#include <list>

int main( void )
{
	// std::string	strTab[7] = {"KIKOU", "42", "nop", "Hello World", "ahah", "yeah", "why not?"};
	// int			iTab[17] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

	if (vectorTest<std::string>(strTab, 7, "string") &&
		vectorTest<int>(iTab, 7, "int"))
		std::cout << "Vector TEST : " << OK << std::endl;
	else
		std::cout << "Vector TEST : " << NOTOK << std::endl;

	if (mapTest<int, std::string>(iTab, strTab, 7, "<int, std::string>") &&
		mapTest<std::string, int>(strTab, iTab, 7, "<std::string, int>"))
		std::cout << "Map TEST : " << OK << std::endl;
	else
		std::cout << "Map TEST : " << NOTOK << std::endl;


	if (TEST)
		while(42);
	return 0;
}