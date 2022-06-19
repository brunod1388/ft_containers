/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintree.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:52:57 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/06/18 04:12:37 by brunodeoliv      ###   ########.fr       */
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
	rb.insert(40);
	rb.insert(65);
	rb.insert(60);
	rb.insert(75);
	rb.insert(57);
	rb.print();

	return 0;
}