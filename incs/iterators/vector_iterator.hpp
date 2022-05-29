/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/05/26 19:11:17 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

namespace ft{

	template <typename T>
	class vector_iterator{

	private:
		

	public:
		vector_iterator<T>(void)
		{
			std::cout << "test vector_iterator" << std::endl;
		}
		vector_iterator<T>(T &val);
		~vector_iterator(void) {}


		
	

	};	//class vector_iterator


};	//namespace ft


#endif