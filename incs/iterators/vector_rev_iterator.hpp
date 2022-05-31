/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rev_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/05/26 19:05:56 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef vector_rev_iterator_HPP
# define vector_rev_iterator_HPP

namespace ft{

	template <typename T>
	class vector_rev_iterator {

	private:
		T *_p;

	public:
		vector_rev_iterator<T>( void );
		vector_rev_iterator<T>( T &val );
		~vector_rev_iterator( void ) {}

	};	//class vector_rev_iterator


};	//namespace ft


#endif