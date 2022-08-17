/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:38:25 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/17 08:22:56 by brunodeoliv      ###   ########.fr       */
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

	if (setTest<int>(iTab, 7, "<int, std::string>") &&
		setTest<std::string>(strTab, 7, "<std::string, int>"))
		std::cout << "Set TEST : " << OK << std::endl;
	else
		std::cout << "Set TEST : " << NOTOK << std::endl;

	if (TEST)
		while(42);
	return 0;
}