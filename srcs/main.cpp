/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:41:51 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/07/10 21:24:55 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <string>
// #include <vector>
#include <utility>
#include <vector>
#include <stack>
#include <list>

#include "vector.hpp"
// #include "map.hpp"
#include "stack.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
#define TEST 0

struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

class A {};
enum E {};

class truc
{
	int i;
public:
	truc(int x = 0) : i(x) {}
	truc(const truc& src) { *this = src; }
	~truc() {};

	truc& operator=(const truc& rhs) { i = rhs.i; return *this; }

	void	f()
	{
		std::cout << "KIKOUU! : " << i << std::endl;
	}
};

void	test(std::string s, void (*f)(void));
void	subject_test(void);
void	integral_test(void);
void	pair_test(void);
void	vector_test(void);
void	stack_test(void);

template< class T, class Alloc >
std::ostream &operator<<( std::ostream &os, const std::vector<T, Alloc>& rhs )
{
	os << "(";
	for (size_t i = 0; i < rhs.size(); i++)
		os << rhs[i] << (i < rhs.size() - 1 ? ", " : "");
	os << ")";
	return os;
}

template <typename T1, typename T2>
void print_vector(T1 &v, T2 &v2)
{
	std::cout << "ft::v      : " << v << "    " << std:: endl;
	std::cout << "std::v     : "<< v2 << std::endl;
	std::cout << "size       : " << std::setw(15) << v.size() << "    " << std::setw(15) << v2.size() << std::endl;
	std::cout << "capacity   : " << std::setw(15) << v.capacity() << "    " << std::setw(15) << v2.capacity() << std::endl;
	std::cout << "data       : " << std::setw(15) << v.data()  << "    " << std::setw(15) << v2.data() << std::endl;
	if (v.size() && v2.size())
	{
		std::cout << "front      : " << std::setw(15) << v.front()  << "    " << std::setw(15) << v2.front() << std::endl;
		std::cout << "back       : " << std::setw(15) << v.back()  << "    " << std::setw(15) << v2.back() << std::endl;
		std::cout << "*begin     : " << std::setw(15) << *v.begin()  << "    " << std::setw(15) << *v2.begin() << std::endl;
		std::cout << "*(end-1)   : " << std::setw(15) << *(v.end()-1)  << "    " << std::setw(15) << *(v2.end()-1) << std::endl;
		std::cout << "*(end)   : " << std::setw(15) << *(v.end())  << "    " << std::setw(15) << *(v2.end()) << std::endl;
	}
	std::cout << std::endl;
}

template <typename T>
void print_stack(ft::stack<T> &st, std::stack<T> &st2)
{
	if (!st.empty())
		std::cout << "ft::stack.top()      : " << st.top() << std:: endl;
	if (!st2.empty())
		std::cout << "std::stack.top()     : "<< st2.top() << std::endl;
	std::cout << "size       ft: " << st.size() << "    std: " << st2.size() << std::endl;
	std::cout << "empty      ft: " << st.empty() << "    std: " << st2.empty() << std::endl;
	std::cout << std::endl;
}

bool isTest(std::string toTest, std::string what)
{
	return toTest == what || toTest == "full";
}

int main(int argc, char **argv) {

	if (argc == 1 || isTest("is_integral", argv[1])) test("is_integral", integral_test);
	if (argc == 1 || isTest("pair", argv[1])) test("pair", pair_test);
	if (argc == 1 || isTest("vector", argv[1])) test("vector", vector_test);
	// if (argc == 1 || isTest("stack", argv[1])) test("stack", stack_test);
	// if (argc == 1 || isTest("map", argv[1])) test("map", map_test);

	std::list<int>	lst;

	for (int i = 0; i < 10; i++)
		lst.push_back(i);

	ft::vector<int>		vft(lst.begin(), lst.end());
	std::vector<int>	vstd(lst.begin(), lst.end());
	print_vector(vft, vstd);
	
	ft::vector<int>			v1(lst.begin(), lst.end());
	std::vector<int>		v2(lst.begin(), lst.end());
	std::cout << "TEST : " << v2.front() << std::endl;
	for (ft::vector<int>::const_iterator i = v1.begin(); i < v1.end(); i++)
	{
		std::cout << "test " << *i << std::endl;
		
	}
	

	if (TEST)
		while(42);
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
	std::vector<int> v2;

	std::cout << "ft::v.maxsize  : " << v.max_size() << std::endl;
	std::cout << "std::v.maxsize : " << v.max_size() << std::endl << std::endl;
	print_vector(v, v2);

	for (int i = 11; i < 18; i++)
	{
		v.push_back(i);
		v2.push_back(i);
		print_vector(v, v2);
	}
	v.reserve(50); v2.reserve(50);
	std::cout << "After reserve" << std::endl;
	print_vector(v, v2);
	v.push_back(3); v2.push_back(3);
	v.push_back(3); v2.push_back(3);
	v.push_back(3); v2.push_back(3);
	v.push_back(7); v2.push_back(7);
	print_vector(v, v2);

	ft::vector<int> v_cpy(v);
	ft::vector<int> v_cpy2 = v;
	print_vector(v_cpy, v2);
	print_vector(v_cpy2, v2);

	/* =========================================================*/
	/*       iterator									*/
	/* =========================================================*/

	std::cout << "ft::iterator--  : ";
	ft::vector<int>::iterator it = v.end();
	while (it != v.begin())
		std::cout << *it-- << " ";
	std::cout << std::endl;

	std::cout << "std::iterator-- : ";
	std::vector<int>::iterator it2 = v2.end();
	while (it2 != v2.begin())
		std::cout << *it2-- << " ";
	std::cout << std::endl;

	std::cout << "--ft::iterator  : ";
	it = v.end();
	while (it != v.begin() + 1)
		std::cout << *--it << " ";
	std::cout << std::endl;

	std::cout << "--std::iterator : ";
	it2 = v2.end();
	while (it2 != v2.begin() + 1)
		std::cout << *--it2 << " ";
	std::cout << std::endl;

	std::cout << "ft::iterator++  : ";
	it = v.begin();
	while (it != v.end())
		std::cout << *it++ << " ";
	std::cout << std::endl;

	std::cout << "std::iterator++ : ";
	it2 = v2.begin();
	while (it2 != v2.end())
		std::cout << *it2++ << " ";
	std::cout << std::endl;

	std::cout << "++ft::iterator  : ";
	it = v.begin();
	while (it != v.end())
		std::cout << *++it << " ";
	std::cout << std::endl;

	std::cout << "++std::iterator : ";
	it2 = v2.begin();
	while (it2 != v2.end())
		std::cout << *++it2 << " ";
	std::cout << std::endl;

	/* =========================================================*/
	/*        reverse_iterator									*/
	/* =========================================================*/
	std::cout << "ft::reverse_iterator++  : ";
	ft::vector<int>::reverse_iterator rIt = v.rbegin();
	while (rIt != v.rend())
		std::cout << *rIt++ << " ";
	std::cout << std::endl;

	std::cout << "std::reverse_iterator++ : ";
	std::vector<int>::reverse_iterator rIt2 = v2.rbegin();
	while (rIt2 != v2.rend())
		std::cout << *rIt2++ << " ";
	std::cout << std::endl << std::endl;

	std::cout << "++ft::reverse_iterator  : ";
	rIt = v.rbegin();
	while (rIt != v.rend())
		std::cout << *++rIt << " ";
	std::cout << std::endl;

	std::cout << "++std::reverse_iterator : ";
	rIt2 = v2.rbegin();
	while (rIt2 != v2.rend())
		std::cout << *++rIt2 << " ";
	std::cout << std::endl << std::endl;

	std::cout << "ft::reverse_iterator--  : ";
	rIt = v.rend();
	while (rIt != v.rbegin())
		std::cout << *rIt-- << " ";
	std::cout << std::endl;

	std::cout << "std::reverse_iterator-- : ";
	rIt2 = v2.rend();
	while (rIt2 != v2.rbegin())
		std::cout << *rIt2-- << " ";
	std::cout << std::endl << std::endl;

	std::cout << "--ft::reverse_iterator  : ";
	rIt = v.rend();
	while (rIt != v.rbegin())
		std::cout << *--rIt << " ";
	std::cout << std::endl;

	std::cout << "--std::reverse_iterator : ";
	rIt2 = v2.rend();
	while (rIt2 != v2.rbegin())
		std::cout << *--rIt2 << " ";
	std::cout << std::endl << std::endl;


	it = v.begin() + 4;
	it2 = v2.begin() + 4;
	v.insert(it, 666);
	v2.insert(it2, 666);
	std::cout << "ft:  v.insert(v.begin() + 4   : " << v << std::endl;
	std::cout << "std: v2.insert(v2.begin() + 4 : " << v2 << std::endl << std::endl;
	std::cout << "ft: v.front() : " << v.front() << "      " << v2.front() << " : std: v2.front()" <<  std::endl;
	std::cout << "ft: v.back()  : " << v.back() << "      " << v2.back() << " : std: v2.back() " <<  std::endl << std::endl;
	v.front() = 555;
	v.back() = 999;
	v2.front() = 555;
	v2.back() = 999;
	std::cout << "ft: v.front() : " << v.front() << "      " << v2.front() << " : std: v2.front()" <<  std::endl;
	std::cout << "ft: v.back()  : " << v.back() << "      " << v2.back() << " : std: v2.back() " <<  std::endl << std::endl;
	std::cout << "ft:  v  : " << v << std::endl;
	std::cout << "std: v2 : " << v2 << std::endl<< std::endl<< std::endl;

	ft::vector<int> va;
	std::vector<int> va2;

	it = v.begin() + 4;
	it2 = v2.begin() + 4;
	va.assign(it, v.end());
	va2.assign(it2, v2.end());
	print_vector(va, va2);

	std::cout << "va.at(2)  : " <<va.at(2) << std::endl;
	std::cout << "va2.at(2) : " <<va2.at(2) << std::endl;

	va.assign(v.begin(), v.end());
	va2.assign(v2.begin(), v2.end());
	// va.assign(v2.end(), v2.begin());
	print_vector(va, va2);

	// va.insert(va.begin() + 5, 777);
	// va2.insert(va2.begin() + 5, 777);
	// print_vector(va, va2);

	ft::vector<int> vfill(10, 55);
	std::vector<int> vfill2(10, 55);
	print_vector(vfill, vfill2);

	// ft::vector<int> vfill(10, 55);
	// ft::vector<int> vx;
	// ft::vector<int>::const_iterator cIt = vx.begin();
	// std::vector<int> vx2;
	// std::vector<int>::const_iterator cIt2 = vx2.begin();


	std::cout << "===================================" << std::endl;
	std::cout << "===           resize            ===" << std::endl;
	std::cout << "===================================" << std::endl;

	print_vector(va, va2);
	// v.resize(20, 13);
	va.resize(50, 13);
	va2.resize(50, 13);
	print_vector(va, va2);
	va.resize(5, 13);
	va2.resize(5, 13);
	print_vector(va, va2);



	// va.assign(7, 7);
	// va2.assign(7, 7);
	// print_vector(va, va2);
	// va.assign(3, 3);
	// va2.assign(3, 3);

	std::cout << "===================================" << std::endl;
	std::cout << "===       insert one el         ===" << std::endl;
	std::cout << "===================================" << std::endl;


	va = ft::vector<int>(2, 1);
	va2 = std::vector<int>(2, 1);
	print_vector(va, va2);
	va.insert(va.begin(), 11);
	va2.insert(va2.begin(), 11);
	print_vector(va, va2);
	va.insert(va.end(), 100);
	va2.insert(va2.end(), 100);
	print_vector(va, va2);
	va.insert(va.end(), 100);
	va2.insert(va2.end(), 100);
	print_vector(va, va2);

	{

		ft::vector<int> vi;
		std::vector<int> vi2;
		print_vector(vi, vi2);

		// std::cout << "TEST   : " << vi.begin().base() << std::endl;
		// std::cout << "TEST   : " << vi2.begin().base() << std::endl;
		// std::cout << "TEST   : " << vi.end().base() << std::endl;
		// std::cout << "TEST   : " << vi2.end().base() << std::endl;
		

		vi.insert(vi.begin(), 11);
		vi2.insert(vi2.begin(), 11);
		print_vector(vi, vi2);

		vi.insert(vi.end(), 100);
		vi2.insert(vi2.end(), 100);
		print_vector(vi, vi2);

		vi.insert(vi.end(), 100);
		vi2.insert(vi2.end(), 100);
		print_vector(vi, vi2);
	}

	std::cout << "===================================" << std::endl;
	std::cout << "===       insert n el           ===" << std::endl;
	std::cout << "===================================" << std::endl;

	{

		ft::vector<int> vi = ft::vector<int>(2, 11);
		std::vector<int> vi2 = std::vector<int>(2, 11);
		print_vector(vi, vi2);

		vi.insert(vi.begin(), 1, 11);
		vi2.insert(vi2.begin(), 1, 11);
		print_vector(vi, vi2);

		vi.insert(vi.end(), 100);
		vi2.insert(vi2.end(), 100);
		print_vector(vi, vi2);

		vi.insert(vi.end(), 100);
		vi2.insert(vi2.end(), 100);
		print_vector(vi, vi2);
	}

	{
		ft::vector<int> vi;
		std::vector<int> vi2;
		print_vector(vi, vi2);

		vi.insert(vi.begin(), 1, 11);
		vi2.insert(vi2.begin(), 1, 11);
		print_vector(vi, vi2);

		vi.insert(vi.end(), 100);
		vi2.insert(vi2.end(), 100);
		print_vector(vi, vi2);

		vi.insert(vi.end(), 100);
		vi2.insert(vi2.end(), 100);
		print_vector(vi, vi2);
	}

	std::cout << "===================================" << std::endl;
	std::cout << "===       insert iter           ===" << std::endl;
	std::cout << "===================================" << std::endl;

	{
		ft::vector<int> ftV;
		ft::vector<int> ftV2(10, 100);
		std::vector<int> stdV;
		std::vector<int> stdV2(10, 100);

		for (size_t i = 0; i < 10; i++)
		{
			ftV.push_back(i);
			stdV.push_back(i);
		}

		ftV2.insert(ftV2.begin() + 2, ftV.begin() + 1, ftV.end() - 4);
		stdV2.insert(stdV2.begin() + 2, stdV.begin() + 1, stdV.end() - 4);

		print_vector(ftV2, stdV2);
	}

	std::cout << "===================================" << std::endl;
	std::cout << "===       insert iter list      ===" << std::endl;
	std::cout << "===================================" << std::endl;
	{
		struct machin
		{
			ft::vector<int>::iterator ift;
			std::vector<int>::iterator ist;

			machin() : ift(), ist() {}
		};

		std::list<int> lst;
		std::list<int>::iterator lst_it;
		for (int i = 1; i < 5; ++i)
			lst.push_back(i * 3);

		ft::vector<int> vft(lst.begin(), lst.end());
		std::vector<int> vstd(lst.begin(), lst.end());

		print_vector(vft, vstd);

		{
			ft::vector<int>::iterator	ift = vft.begin();
			std::vector<int>::iterator	ist = vstd.begin();
			struct machin				*m = new machin();

			m->ift = ift;
			m->ist = ist;

			std::cout << "ift : " << *ift << std::endl;
			std::cout << "ist : " << *ist << std::endl;

			++*ift;
			++*ist;

			std::cout << "ift : " << *++ift << std::endl;
			std::cout << "ist : " << *++ist << std::endl;

			std::cout << "ift : " << *m->ift << std::endl;
			std::cout << "ist : " << *m->ist << std::endl << std::endl;
			delete m;
		}


		{
			ft::vector<int>::const_iterator		cift = vft.begin();
			std::vector<int>::const_iterator	cist = vstd.begin();

			std::cout << "cift : " << *cift << std::endl;
			std::cout << "cist : " << *cist << std::endl;

			++cift;
			++cist;

			std::cout << "cift : " << *++cift << std::endl;
			std::cout << "cist : " << *++cist << std::endl;
		}

	}

	std::cout << "===================================" << std::endl;
	std::cout << "===      relational operator    ===" << std::endl;
	std::cout << "===================================" << std::endl;
	{

		std::list<int> lst;
		std::list<int>::iterator lst_it;
		for (int i = 1; i < 5; ++i)
			lst.push_back(i * 3);

		
		ft::vector<int> vft(lst.begin(), lst.end());
		std::vector<int> vstd(lst.begin(), lst.end());
		ft::vector<int> vft2(lst.begin(), lst.end());
		std::vector<int> vstd2(lst.begin(), lst.end());

		print_vector(vft, vstd);
		std::cout << std::endl << " vft2 and vstd2 :" << std::endl;
		print_vector(vft2, vstd2);

		std::cout << "vft <  vft2 : vstd <  vstd2    " << (vft < vft2)  << ":" <<(vstd < vstd2) << std::endl;
		std::cout << "vft <= vft2 : vstd <= vstd2    " << (vft <= vft2) << ":" <<(vstd <= vstd2) << std::endl;
		std::cout << "vft >  vft2 : vstd >  vstd2    " << (vft > vft2)  << ":" <<(vstd > vstd2) << std::endl;
		std::cout << "vft >= vft2 : vstd >= vstd2    " << (vft >= vft2) << ":" <<(vstd >= vstd2) << std::endl;
		std::cout << "vft == vft2 : vstd == vstd2    " << (vft == vft2) << ":" <<(vstd == vstd2) << std::endl;
		std::cout << "vft != vft2 : vstd != vstd2    " << (vft != vft2) << ":" <<(vstd != vstd2) << std::endl;

		std::cout << std::endl << " Push 42 on vft and vsyd" << std::endl << std::endl;
		vft.push_back(42);
		vstd.push_back(42);
		print_vector(vft, vstd);
		std::cout << std::endl << " vft2 and vstd2 :" << std::endl;
		print_vector(vft2, vstd2);
		std::cout << "vft <  vft2 : vstd <  vstd2    " << (vft < vft2)  << ":" <<(vstd < vstd2) << std::endl;
		std::cout << "vft <= vft2 : vstd <= vstd2    " << (vft <= vft2) << ":" <<(vstd <= vstd2) << std::endl;
		std::cout << "vft >  vft2 : vstd >  vstd2    " << (vft > vft2)  << ":" <<(vstd > vstd2) << std::endl;
		std::cout << "vft >= vft2 : vstd >= vstd2    " << (vft >= vft2) << ":" <<(vstd >= vstd2) << std::endl;
		std::cout << "vft == vft2 : vstd == vstd2    " << (vft == vft2) << ":" <<(vstd == vstd2) << std::endl;
		std::cout << "vft != vft2 : vstd != vstd2    " << (vft != vft2) << ":" <<(vstd != vstd2) << std::endl;

		std::cout << std::endl << " Push 84 on vft2 and vstd2" << std::endl << std::endl;
		vft2.push_back(84);
		vstd2.push_back(84);
		print_vector(vft, vstd);
		std::cout << std::endl << " vft2 and vstd2 :" << std::endl;
		print_vector(vft2, vstd2);
		std::cout << "vft <  vft2 : vstd <  vstd2    " << (vft < vft2)  << ":" <<(vstd < vstd2) << std::endl;
		std::cout << "vft <= vft2 : vstd <= vstd2    " << (vft <= vft2) << ":" <<(vstd <= vstd2) << std::endl;
		std::cout << "vft >  vft2 : vstd >  vstd2    " << (vft > vft2)  << ":" <<(vstd > vstd2) << std::endl;
		std::cout << "vft >= vft2 : vstd >= vstd2    " << (vft >= vft2) << ":" <<(vstd >= vstd2) << std::endl;
		std::cout << "vft == vft2 : vstd == vstd2    " << (vft == vft2) << ":" <<(vstd == vstd2) << std::endl;
		std::cout << "vft != vft2 : vstd != vstd2    " << (vft != vft2) << ":" <<(vstd != vstd2) << std::endl;

		std::cout << std::endl << " Push 84 on vft2 and vstd2" << std::endl << std::endl;
		vft2.push_back(84);
		vstd2.push_back(84);
		print_vector(vft, vstd);
		std::cout << std::endl << " vft2 and vstd2 :" << std::endl;
		print_vector(vft2, vstd2);
		std::cout << "vft <  vft2 : vstd <  vstd2    " << (vft < vft2)  << ":" <<(vstd < vstd2) << std::endl;
		std::cout << "vft <= vft2 : vstd <= vstd2    " << (vft <= vft2) << ":" <<(vstd <= vstd2) << std::endl;
		std::cout << "vft >  vft2 : vstd >  vstd2    " << (vft > vft2)  << ":" <<(vstd > vstd2) << std::endl;
		std::cout << "vft >= vft2 : vstd >= vstd2    " << (vft >= vft2) << ":" <<(vstd >= vstd2) << std::endl;
		std::cout << "vft == vft2 : vstd == vstd2    " << (vft == vft2) << ":" <<(vstd == vstd2) << std::endl;
		std::cout << "vft != vft2 : vstd != vstd2    " << (vft != vft2) << ":" <<(vstd != vstd2) << std::endl;
	}

	std::cout << "===================================" << std::endl;
	std::cout << "===      -> and *   operator    ===" << std::endl;
	std::cout << "===================================" << std::endl;
	{
		std::list<truc> lst;
		std::list<truc>::iterator lst_it;
		for (int i = 1; i < 5; ++i)
			lst.push_back(truc(i * 3));

		ft::vector<truc> vft(lst.begin(), lst.end());
		std::vector<truc> vstd(lst.begin(), lst.end());

		ft::vector<truc>::iterator	ftit = vft.begin();
		std::vector<truc>::iterator	stdit = vstd.begin();

		ftit->f();
		stdit->f();
		ftit++;
		stdit++;
		(*ftit).f();
		(*stdit).f();
	}

	std::cout << "===================================" << std::endl;
	std::cout << "===          rev iterator       ===" << std::endl;
	std::cout << "===================================" << std::endl;
	{
		std::list<int> lst;
		std::list<int>::iterator lst_it;
		for (int i = 1; i < 5; ++i)
			lst.push_back(i * 3);

		ft::vector<int> vft(lst.begin(), lst.end());
		std::vector<int> vstd(lst.begin(), lst.end());

		ft::vector<int>::const_reverse_iterator	ftrit = vft.rbegin();
		std::vector<int>::reverse_iterator		stdrit = vstd.rbegin();

		{
			ft::vector<int> vft2(ftrit, vft.rend());
			std::vector<int> vstd2(stdrit, vstd.rend());
			print_vector(vft2, vstd2);
		}
		// {
		// 	std::vector<int> vstd2(stdrit, vstd.rend());
		// 	ft::vector<int> vft2(ftrit, vft.rend());
		// 	print_vector(vstd2, vft2);
		// }

		// std::cout << 
	}
} // vector_test

void	stack_test(void)
{
	ft::stack<int> st1;
	std::stack<int> st2;
	ft::stack<int> st12;
	std::stack<int> st22;
	st12.push(123);
	st22.push(123);

	print_stack(st1, st2);
	st1.push(1);
	st2.push(1);
	print_stack(st1, st2);
	st1.push(2);
	st2.push(2);
	print_stack(st1, st2);
	st1.pop();
	st2.pop();
	print_stack(st1, st2);
	st1.push(3);
	st2.push(3);
	print_stack(st1, st2);

	ft::swap(st1, st12);
	std::swap(st2, st22);
	std::cout << "Afte swap :" << std::endl;
	print_stack(st1, st2);
}

void	map_test(void)
{
	return;
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


