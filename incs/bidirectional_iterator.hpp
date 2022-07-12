/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/07/12 01:15:50 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

#include "iterator_traits.hpp"
#include <typeinfo>

namespace ft{

	template <typename Node, typename T>
	class bidirectional_iterator
	{
		//===============================================================
		//
		//			TO DO : TOUT
		//
		//===============================================================
		public:
			typedef ptrdiff_t								difference_type;
			typedef Node									node_type;
			typedef Node*									node_ptr;
			typedef T*										pointer;
			typedef T&										reference;
			typedef bidirectional_iterator<Node, const T>	const_iterator; // test
			typedef ft::bidirectional_iterator_tag			iterator_category;

		private :
			node_ptr _p;

		public :
			bidirectional_iterator(void) : _p(NULL) {}
			bidirectional_iterator(node_ptr p) : _p(p) {}
			bidirectional_iterator(const bidirectional_iterator& src) { *this = src; }
			~bidirectional_iterator(void) {}

			bidirectional_iterator& operator=(const bidirectional_iterator& rhs);

			node_ptr	base() const { return _p; }

			reference	operator*(void) const { return _p->content; }
			pointer		operator->(void) const {return &_p->content; }

			operator const_iterator() const  //replace by const_iterator
			{
				return const_iterator(_p);
			}

			bidirectional_iterator&	operator++(void) { _p = _p->next() ; return *this; }
			bidirectional_iterator	operator++(int)
			{
				bidirectional_iterator tmp(_p);
				_p = _p->next();
				return tmp;
			}

			bidirectional_iterator&	operator--(void) { _p = _p->previous() ; return *this; }
			bidirectional_iterator	operator--(int)
			{
				bidirectional_iterator tmp(_p);
				_p = _p->previous();
				return tmp;
			}

			bool	operator==(const bidirectional_iterator rhs) const { return _p == rhs._p; }
			bool	operator!=(const bidirectional_iterator rhs) const { return _p != rhs._p; }

			bool	operator<(const bidirectional_iterator rhs) const
			{
				return !rhs._p || (_p && _p->content < rhs._p->content);
			}

			bool	operator>(const bidirectional_iterator rhs) const
			{
				return !_p || (rhs._p && _p->content < rhs._p->content);
			}

			bool	operator<=(const bidirectional_iterator rhs) const
			{
				return !rhs._p || (_p && _p->content <= rhs._p->content);
			}

			bool	operator>=(const bidirectional_iterator rhs) const
			{
				return !_p || (rhs._p && _p->content >= rhs._p->content);
			}

	};	//class bidirectional_iterator

};	//namespace ft

#endif