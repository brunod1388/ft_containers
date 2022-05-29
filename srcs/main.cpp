/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:41:51 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/05/29 03:18:23 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <utility>

#include <type_traits>
#include "type_traits.hpp"

#define SHOW(...) std::cout << std::setw(35) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

class A {};
 
enum E : int {};
 
template <class T>
T f(T i)
{
	static_assert(std::is_integral<T>::value, "Integral required.");
	return i;
}

void	integral_test(void);

int main(void) {
	integral_test();

	return (0);
}


void	integral_test(void)
{
	SHOW( std::is_integral<A>::value );
	SHOW( ft::is_integral<A>::value );
	std::cout << std::endl;
	SHOW( std::is_integral<E>::value );
	SHOW( ft::is_integral<E>::value );
	std::cout << std::endl;
	SHOW( std::is_integral<float>::value );
	SHOW( ft::is_integral<float>::value );
	std::cout << std::endl;
	SHOW( std::is_integral<int>::value );
	SHOW( ft::is_integral<int>::value );
	std::cout << std::endl;
	SHOW( std::is_integral<const int>::value );
	SHOW( ft::is_integral<const int>::value );
	std::cout << std::endl;
	SHOW( std::is_integral<bool>::value );
	SHOW( ft::is_integral<bool>::value );
	std::cout << std::endl;
	SHOW( f(123) );
}