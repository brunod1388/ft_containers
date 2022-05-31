/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:41:51 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/05/31 01:06:10 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <string>
// #include <vector>
#include <utility>

#include "vector.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};
#define COUNT (MAX_RAM / (int)sizeof(Buffer))

class A {};
enum E {};

void	test(std::string s, void (*f)(void));
void	subject_test(void);
void	integral_test(void);
void	pair_test(void);
void	vector_test(void);
template <typename T>
void print_vector(ft::vector<T> &v)
{
	std::cout << "v : " << v << std::endl;
	std::cout << "size     : " << v.size() << std::endl;
	std::cout << "capacity : " << v.capacity() << std::endl;
	std::cout << "data     : " << v.data()  << std::endl;
	std::cout << "front    : " << v.front()  << std::endl;
	std::cout << "back     : " << v.back()  << std::endl;
	std::cout << "maxsize  : " << v.max_size() << std::endl << std::endl;
	std::cout << std::endl;
}

bool isTest(std::string toTest, std::string what)
{
	return toTest == what || toTest == "full";
}

int main(int argc, char **argv) {

	if (argc == 1 || isTest("is_integral", argv[1])) test("is_integral", integral_test);
	if (argc == 1 || isTest("pair", argv[1])) test("pair", pair_test);
	if (argc == 1 || isTest("pair", argv[1])) test("vector", vector_test);

	return (0);
}

void	pair_test(void)
{
	ft::pair<int, int> p00 = ft::pair<int, int>(0, 0);
	ft::pair<int, int> p11(1, 1);
	ft::pair<int, int> p12 = ft::pair<int, int>(1, 2);
	ft::pair<int, int> p22 = ft::make_pair(2, 2);
	ft::pair<int, int> p11_copy(p12);
	ft::pair<std::string, int> px("kikou", 13);
	p11_copy.second = 1;

	std::cout << "px(\"kikou\", 13)                     : " << px << std::endl;
	std::cout << "p00 = ft::pair<int, int>(0, 0)      : " << p00 << std::endl;
	std::cout << "p11(1, 1)                           : " << p11 << std::endl;
	std::cout << "p12 = ft::pair<int, int>(1, 2)      : " << p12 << std::endl;
	std::cout << "p22 = ft::make_pair(2, 2)           : " << p22 << std::endl;
	std::cout << "p11_copy(p12);\np11_copy.second = 1 : " << p11_copy << std::endl << std::endl;

	std::cout << "p00 < p11  = " << (p00 < p11) << " (1 expected)" << std::endl;
	std::cout << "p00 > p11  = " << (p00 > p11) << " (0 expected)" << std::endl;
	std::cout << "p00 <= p11 = " << (p00 <= p11) << " (1 expected)" << std::endl;
	std::cout << "p00 >= p11 = " << (p00 >= p11) << " (0 expected)" << std::endl;
	std::cout << "p00 == p11 = " << (p00 == p11) << " (0 expected)" << std::endl;
	std::cout << "p00 != p11 = " << (p00 != p11) << " (1 expected)" << std::endl;
	std::cout << std::endl;
	std::cout << "p00 < p00  = " << (p00 < p00) << " (0 expected)" << std::endl;
	std::cout << "p00 > p00  = " << (p00 > p00) << " (0 expected)" << std::endl;
	std::cout << "p00 <= p00 = " << (p00 <= p00) << " (1 expected)" << std::endl;
	std::cout << "p00 >= p00 = " << (p00 >= p00) << " (1 expected)" << std::endl;
	std::cout << "p00 == p00 = " << (p00 == p00) << " (1 expected)" << std::endl;
	std::cout << "p00 != p00 = " << (p00 != p00) << " (0 expected)" << std::endl;
	std::cout << std::endl;
	std::cout << "p12 < p11  = " << (p12 < p11) << " (0 expected)" << std::endl;
	std::cout << "p12 > p11  = " << (p12 > p11) << " (1 expected)" << std::endl;
	std::cout << "p12 <= p11 = " << (p12 <= p11) << " (0 expected)" << std::endl;
	std::cout << "p12 >= p11 = " << (p12 >= p11) << " (1 expected)" << std::endl;
	std::cout << "p12 == p11 = " << (p12 == p11) << " (0 expected)" << std::endl;
	std::cout << "p12 != p11 = " << (p12 != p11) << " (1 expected)" << std::endl;
	std::cout << std::endl;
	std::cout << "p00" << p00 << ", p11" << p11 << std::endl;
	std::cout << "swap(p00,p11)" << std::endl; ft::swap(p00, p11);
	std::cout << "p00" << p00 << ", p11" << p11 << std::endl;
}

void	test(std::string s, void (*f)(void))
{
	std::cout << "----------------------------------------------------------" << std::endl;
	std::cout << "       " << s << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;
	std::cout << std::endl;
	f();
	// std::cout << "----------------------------------------------------------" << std::endl;
	std::cout << std::endl;
}

void	integral_test(void)
{
	std::cout << "Non integral :" << std::endl;
	std::cout << std::endl;
	std::cout << "ft::is_integral<A>::value                       : " << ft::is_integral<A>::value << std::endl;
	std::cout << "ft::is_integral<const A>::value                 : " << ft::is_integral<const A>::value << std::endl;
	std::cout << std::endl;
	std::cout << "ft::is_integral<E>::value                       : " << ft::is_integral<E>::value << std::endl;
	std::cout << std::endl;
	std::cout << "ft::is_integral<float>::value                   : " << ft::is_integral<float>::value << std::endl;
	std::cout << "ft::is_integral<double>::value                  : " << ft::is_integral<double>::value << std::endl;
	std::cout << std::endl;
	std::cout << "ft::is_integral<std::string>::value             : " << ft::is_integral<std::string>::value << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Integral :" << std::endl;
	std::cout << std::endl;
	std::cout << "ft::is_integral<int>::value                     : " << ft::is_integral<int>::value << std::endl;
	std::cout << "ft::is_integral<unsigned int>::value            : " << ft::is_integral<unsigned int>::value << std::endl;
	std::cout << "ft::is_integral<const int>::value               : " << ft::is_integral<const int>::value << std::endl;
	std::cout << std::endl;
	std::cout << "ft::is_integral<short>::value                   : " << ft::is_integral<short>::value << std::endl;
	std::cout << "ft::is_integral<unsigned short>::value          : " << ft::is_integral<unsigned short>::value << std::endl;
	std::cout << "ft::is_integral<const short>::value             : " << ft::is_integral<const short>::value << std::endl;
	std::cout << std::endl;
	std::cout << "ft::is_integral<long>::value                    : " << ft::is_integral<long>::value << std::endl;
	std::cout << "ft::is_integral<long long>::value               : " << ft::is_integral<long long>::value << std::endl;
	std::cout << "ft::is_integral<const long int>::value          : " << ft::is_integral<const long int>::value << std::endl;
	std::cout << "ft::is_integral<unsigned long int>::value       : " << ft::is_integral<unsigned long int>::value << std::endl;
	std::cout << "ft::is_integral<const unsigned long int>::value : " << ft::is_integral<const unsigned long int>::value << std::endl;
	std::cout << std::endl;
	std::cout << "ft::is_integral<bool>::value                    : " << ft::is_integral<bool>::value << std::endl;
	std::cout << "ft::is_integral<const bool>::value              : " << ft::is_integral<const bool>::value << std::endl;
	std::cout << std::endl;
	std::cout << "ft::is_integral<char>::value                    : " << ft::is_integral<char>::value << std::endl;
	std::cout << "ft::is_integral<unsigned char>::value           : " << ft::is_integral<unsigned char>::value << std::endl;
	std::cout << "ft::is_integral<const char>::value              : " << ft::is_integral<const char>::value << std::endl;
	std::cout << std::endl;
}

void	vector_test(void)
{
	ft::vector<int> v;

	print_vector(v);

	// for (int i = 0; i < 3; i++)
	// {
	// 	print_vector(v);
	// 	v.push_back(i);
	// }
	// v.reserve(5);
	// std::cout << "After reserve" << std::endl;
	// print_vector(v);
	// v.push_back(3);
	// v.push_back(3);
	// v.push_back(3);
	// print_vector(v);
}











// void	subject_test(void)
// {
// 	std::vector<int> v;
// 	ft::vector<int> myv;


// 	std::vector_iterator<int> myvit;
	
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);

// 	ft::vector<std::string> vector_str;
// 	ft::vector<int> vector_int;
// 	ft::vector<Buffer> vector_buffer;

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	ft::vector<Buffer>().swap(vector_buffer);

// 	try
// 	{
// 		for (int i = 0; i < COUNT; i++)
// 		{
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
// 		}
// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}

// 	std::cout << std::endl;
// }


