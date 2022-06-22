/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintree.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:52:57 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/06/23 01:52:09 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RBTree.hpp"
#include <iostream>
#include <map>


int main(void)
{
	ft::RBTree<int> rb;
	std::map<int, std::string> m;

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
	rb.insert(12);
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

	rb.deleteKey(40);
	rb.print();
	rb.deleteKey(98);
	rb.print();
	rb.clear();
	return 0;
}