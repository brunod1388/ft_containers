/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main666.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:38:25 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/07/12 00:28:13 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "vector_test.hpp"
#include <vector>
#include <list>

#define	TEST 0

int main( void )
{
	std::string	strTab[7] = {"KIKOU", "42", "nop", "Hello World", "ahah", "yeah", "why not?"};

	int			iTab[17] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

	vectorTest<std::string>(strTab, 7, "string");
	vectorTest<int>(iTab, 7, "int");

	ft::vector<int> v;

	v.push_back(1);
	v.push_back(1);
	
	for (ft::vector<int>::const_iterator i = v.begin(); i != v.end(); i++)
	{
		std::cout << *i;
	}

	std::vector<int> vs;

	vs.push_back(1);
	vs.push_back(1);
	
	for (std::vector<int>::const_iterator i = vs.begin(); i != vs.end(); i++)
	{
		std::cout << *i;
		*i = 0;
	}
	std::cout << "test : " << v[0] << "   " << v[1] << std::endl;
	
	if (TEST)
		while(42);
	return 0;
}