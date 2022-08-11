/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintree.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:52:57 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/11 03:52:24 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TEST 1
#include "utility.hpp"
#include "RBTree.hpp"
#include <iostream>
#include <map>

template < typename T1, typename T2 >
std::ostream&	operator<<(std::ostream& os, const std::pair<T1, T2>& rhs)
{
	os << "(" << rhs.first << ", " << rhs.second << ")";
	return os;
}


int main(void)
{
	ft::_RBTree<int> rb;
	int				insertTab[22] = {55, 40, 65, 60, 75, 57, 13, 56, 98, 12,
									 8, 45, 5, 4, 3, 2, 1, 105, 104, 103,
									102, 101};
	int				deleteTab[5] = {40, 98, 57, 13, 8};

	for (int i = 0; i < 22; i++)
	{
		std::cout << i << " Insert " << insertTab[i] << std::endl;
		rb.insert(insertTab[i]);
		rb.printTree();
	}
	for (int i = 0; i < 22; i++)
	{
		std::cout << i << " Insert " << insertTab[i] << std::endl;
		rb.insert(insertTab[i] + 1000);
		rb.printTree();
	}
  	std::cout << std::endl << "After deleting----------------" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << i << " Delete " << deleteTab[i] << std::endl;
		rb.insert(deleteTab[i]);
		rb.printTree();
	}

	rb.clear();

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

	ft::_RBTree< ft::pair<int, std::string> > dicTree;
	for (size_t i = 0; i < 10; i++)
		dicTree.insert(dic[i]);
	dicTree.printTree();

	std::map<int, std::string> m;
	for (int i = 0; i < 10; i++)
		m.insert(std::pair<int, const std::string>(dic[i].first, dic[i].second));

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "iterator and operator != test" << std::endl << std::endl;
	std::cout << "ft :";
	for (ft::_RBTree<ft::pair<int, std::string> >::iterator i = dicTree.begin();
		i != dicTree.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl << "std:";
	for (std::map<int, std::string>::iterator i = m.begin();
		i != m.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	std::cout << "-----------------------------------" << std::endl;

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "const iterator and operator != test" << std::endl << std::endl;
	std::cout << "ft :";
	for (ft::_RBTree<ft::pair<int, std::string> >::const_iterator i = dicTree.begin();
		i != dicTree.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl << "std:";
	for (std::map<int, std::string>::const_iterator i = m.begin();
		i != m.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	std::cout << "-----------------------------------" << std::endl;

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "reverse iterator and operator != test" << std::endl << std::endl;
	std::cout << "ft :";
	for (ft::_RBTree<ft::pair<int, std::string> >::reverse_iterator i = dicTree.rbegin();
		i != dicTree.rend(); i++)
		std::cout << *i << " ";
	std::cout << std::endl << "std:";
	for (std::map<int, std::string>::reverse_iterator i = m.rbegin();
		i != m.rend(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	std::cout << "-----------------------------------" << std::endl;

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "const reverse iterator and operator != test" << std::endl << std::endl;
	std::cout << "ft :";
	for (ft::_RBTree<ft::pair<int, std::string> >::const_reverse_iterator i = dicTree.rbegin();
		i != dicTree.rend(); i++)
		std::cout << *i << " ";
	std::cout << std::endl << "std:";
	for (std::map<int, std::string>::const_reverse_iterator i = m.rbegin();
		i != m.rend(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "END" << std::endl;

	ft::_RBTree<ft::pair<int, std::string> > mcpy(dicTree);
	ft::_RBTree<ft::pair<int, std::string> > mcpy2 = dicTree;
	dicTree.insert(ft::pair<int, std::string>(12,"dadsd"));
	mcpy.printTree();
	
	mcpy2.printTree();
	dicTree.erase(ft::pair<int, std::string>(12,"dadsd"));
	dicTree.printTree();

	// while(42);
	return 0;
}