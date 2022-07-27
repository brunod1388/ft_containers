/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/07/28 00:34:55 by brunodeoliv      ###   ########.fr       */
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
			node_ptr	_p;
			node_ptr	_root;

		public :
			bidirectional_iterator(void) : _p(NULL) , _root(NULL) {}
			bidirectional_iterator(node_ptr p, node_ptr root) :
				_p(p),
				_root(root)
			{}

			bidirectional_iterator(const bidirectional_iterator& src) { *this = src; }
			~bidirectional_iterator(void) {}

			bidirectional_iterator& operator=(const bidirectional_iterator& rhs)
			{
				_p = rhs._p;
				_root = rhs._root;
				return *this;
			}

			node_ptr	base() const { return _p; }

			reference	operator*(void) const { return _p->content; }
			pointer		operator->(void) const {return &_p->content; }

			operator const_iterator() const
			{
				return const_iterator(_p, _root);
			}

			bidirectional_iterator&	operator++(void)
			{
				_p = _p->next();
				return *this;
			}

			bidirectional_iterator	operator++(int)
			{
				bidirectional_iterator tmp(_p, _root);
				_p = _p->next();
				return tmp;
			}

			bidirectional_iterator&	operator--(void)
			{
				if (!_p)
					_p = _root->maxi();
				else
					_p = _p->previous();
				return *this;
			}

			bidirectional_iterator	operator--(int)
			{
				bidirectional_iterator tmp(_p, _root);
				if (!_p)
					_p = _root->maxi();
				else
					_p = _p->previous();
				return tmp;
			}

			bool	operator==(const bidirectional_iterator rhs) const { return _p == rhs._p; }
			bool	operator!=(const bidirectional_iterator rhs) const { return _p != rhs._p; }

	};	//class bidirectional_iterator

};	//namespace ft

#endif