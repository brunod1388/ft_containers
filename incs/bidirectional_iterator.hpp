/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator copy.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/06/16 03:15:33 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

#include "iterator_traits.hpp"
#include <typeinfo>

namespace ft{

	template <typename T>
	class bidirectional_iterator 
	{
		//===============================================================
		//
		//			TO DO : TOUT
		//
		//===============================================================
		public:
			typedef ptrdiff_t							difference_type;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef bidirectional_iterator<const T>		const_iterator; // test
			typedef ft::bidirectional_iterator_tag		iterator_category;

		private :
			pointer _p;

		public :
			bidirectional_iterator(void) : _p(NULL) {}
			bidirectional_iterator(pointer p) : _p(p) {}
			bidirectional_iterator(const bidirectional_iterator& src) { *this = src; }
			~bidirectional_iterator(void) {}

			bidirectional_iterator& operator=(const bidirectional_iterator& rhs);

			pointer	base() const;
			reference	operator*(void) const;
			pointer		operator->(void) const;
			operator bidirectional_iterator<const T>() const;
			bidirectional_iterator&	operator++(void);
			bidirectional_iterator	operator++(int);
			bidirectional_iterator&	operator--(void);
			bidirectional_iterator	operator--(int);

			bool	operator==(const bidirectional_iterator rhs) const { return _p == rhs._p; }
			bool	operator!=(const bidirectional_iterator rhs) const { return _p != rhs._p; }

	};	//class bidirectional_iterator

};	//namespace ft

#endif