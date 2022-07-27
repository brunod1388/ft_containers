/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintree.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:52:57 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/07/28 00:48:38 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.hpp"
#include "RBTree.hpp"
#include <iostream>
#include <map>

template < typename T1, typename T2 >
std::ostream&	operator<<(std::ostream& os, ft::pair<T1, T2>& rhs)
{
	os << "(" << rhs.first << ", " << rhs.second << ")";
	return os;
}

template < typename T1, typename T2 >
std::ostream&	operator<<(std::ostream& os, std::pair<T1, T2>& rhs)
{
	os << "(" << rhs.first << ", " << rhs.second << ")";
	return os;
}

int main(void)
{
	ft::RBTree<int> rb;
	// std::map<int, std::string> m;

	std::cout << "KIKOUrwer" << std::endl;
	rb.insert(55);
	rb.print();
	rb.insert(40);
	rb.print();
	rb.insert(65);
	rb.print();
	rb.insert(60);
	rb.print();
	rb.insert(75);
	rb.print();
	rb.insert(57);
	rb.insert(13);
	rb.insert(56);
	rb.insert(98);
	rb.insert(12);
	rb.insert(8);
	rb.insert(45);
	// rb.insert(12);
	rb.print();
	rb.insert(5);
	rb.insert(4);
	rb.insert(3);
	rb.insert(2);
	rb.insert(1);
	rb.print();
	rb.insert(105);
	rb.insert(104);
	rb.insert(103);
	rb.insert(102);
	rb.insert(101);
	rb.print();

  	std::cout << std::endl
     << "After deleting" << std::endl;
	rb.deleteKey(40);
	rb.print();
	rb.deleteKey(98);
	rb.print();
	rb.deleteKey(57);
	rb.print();
	rb.deleteKey(13);
	rb.print();
	rb.deleteKey(8);
	rb.print();
	// rb.deleteKey(60);
	// rb.print();
	// rb.deleteKey(104);
	// rb.print();
	// rb.deleteKey(105);
	// rb.print();
	// rb.deleteKey(1);
	// rb.print();
	
	rb.clear();

	for (int i = 0; i < 10; i++)
	{
		rb.insert(i);
		rb.insert(i*3);
	}

	ft::RBTree<int>::node*	nd = rb.first();
	rb.print();
	while (nd)
	{
		std::cout << nd->content << "  ";
		nd = nd->next();
	}
	std::cout << std::endl;

	nd = rb.last();
	while (nd)
	{
		std::cout << nd->content << "  ";
		nd = nd->previous();
	}

	std::cout << std::endl;

	ft::pair<int, std::string> dic[10] = {ft::pair<int, std::string>(0, "zero"),
										ft::pair<int, std::string>(1, "un"),
										ft::pair<int, std::string>(2, "deux"),
										ft::pair<int, std::string>(3, "trois"),
										ft::pair<int, std::string>(4, "quatre"),
										ft::pair<int, std::string>(5, "cinq"),
										ft::pair<int, std::string>(6, "six"),
										ft::pair<int, std::string>(7, "sept"),
										ft::pair<int, std::string>(8, "huit"),
										ft::pair<int, std::string>(9, "neuf")};
	
	ft::RBTree< ft::pair<int, std::string> > dicTree;
	for (size_t i = 0; i < 10; i++)
		dicTree.insert(dic[i]);
	dicTree.print();

	std::map<int, std::string> m;
	for (int i = 0; i < 10; i++)
		m.insert(std::pair<int, const std::string>(dic[i].first, dic[i].second));

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "iterator and operator != test" << std::endl << std::endl;
	std::cout << "ft :";
	for (ft::RBTree<ft::pair<int, std::string> >::iterator i = dicTree.begin();
		i != dicTree.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl << "std:";
	for (std::map<int, std::string>::iterator i = m.begin();
		i != m.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	std::cout << "-----------------------------------" << std::endl;

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "iterator and operator != test" << std::endl << std::endl;
	std::cout << "ft :";
	for (ft::RBTree<ft::pair<int, std::string> >::const_iterator i = dicTree.begin();
		i != dicTree.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl << "std:";
	for (std::map<int, std::string>::const_iterator i = m.begin();
		i != m.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	std::cout << "-----------------------------------" << std::endl;


	// while(42);
	return 0;
}