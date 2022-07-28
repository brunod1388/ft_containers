/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BidirectionalIterator.hpp                         :+:      :+:    :+:   */
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
	class BidirectionalIterator
	{
		public:
			typedef Node*									node_ptr;
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef BidirectionalIterator<Node, const T>	const_iterator; // test
			typedef ft::bidirectional_iterator_tag			iterator_category;

		private :
			node_ptr	_p;
			node_ptr	_root;

		public :
			BidirectionalIterator(void) : _p(NULL) , _root(NULL) {}
			BidirectionalIterator(node_ptr p, node_ptr root) :
				_p(p),
				_root(root)
			{}

			BidirectionalIterator(const BidirectionalIterator& src) { *this = src; }
			~BidirectionalIterator(void) {}

			BidirectionalIterator& operator=(const BidirectionalIterator& rhs)
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

			BidirectionalIterator&	operator++(void)
			{
				_p = _p->next();
				return *this;
			}

			BidirectionalIterator	operator++(int)
			{
				BidirectionalIterator tmp(_p, _root);
				_p = _p->next();
				return tmp;
			}

			BidirectionalIterator&	operator--(void)
			{
				if(_p)
					_p = _p->previous();
				else
					_p = _root->maxi();
				return *this;
			}

			BidirectionalIterator	operator--(int)
			{
				BidirectionalIterator tmp(_p, _root);
				if(_p)
					_p = _p->previous();
				else
					_p = _root->maxi();
				return tmp;
			}

			bool	operator==(const BidirectionalIterator rhs) const { return _p == rhs._p; }
			bool	operator!=(const BidirectionalIterator rhs) const { return _p != rhs._p; }

	};	//class BidirectionalIterator

	template < class Iter >
	class BidirectionalIterator_reverse
	{
		public:
			typedef Iter								iterator_type;
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::const_iterator		const_iterator; //test
			typedef typename Iter::iterator_category	iterator_category;

		private :
			Iter	_current;

		public :
			BidirectionalIterator_reverse( void ) : _current() {}
			BidirectionalIterator_reverse( Iter src ) : _current(src) {}
			BidirectionalIterator_reverse( const BidirectionalIterator_reverse& src ) { *this = src; }
			~BidirectionalIterator_reverse( void ) {}

			BidirectionalIterator_reverse& operator=(const BidirectionalIterator_reverse& rhs)
			{
				_current = rhs._current;
				return *this;
			}

			operator BidirectionalIterator_reverse<const_iterator>() const
			{
				return BidirectionalIterator_reverse<const_iterator>(_current);
			}

			pointer	base() const { return _current.base(); }

			reference	operator*( void ) const { return *_current; }
			pointer		operator->( void ) const { return _current.base(); }

			BidirectionalIterator_reverse&	operator++( void ) { _current--; return *this; }
			BidirectionalIterator_reverse	operator++( int ) { return BidirectionalIterator_reverse(_current--); }
			BidirectionalIterator_reverse&	operator--( void ) { _current++; return *this; }
			BidirectionalIterator_reverse	operator--( int ) { return BidirectionalIterator_reverse(_current++); }

			bool	operator==( const BidirectionalIterator_reverse rhs ) const { return _current == rhs._current; }
			bool	operator!=( const BidirectionalIterator_reverse rhs ) const { return _current != rhs._current; }

	};	//class BidirectionalIterator_reverse

};	//namespace ft

#endif