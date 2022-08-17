/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 01:48:05 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/17 06:54:29 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP
#include <typeinfo>
#include <cstddef>

namespace ft
{
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template < class Iter >
	class iterator_traits{

		public :
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::iterator_category	iterator_category;
	};	//class iterator_traits

	template <typename T>
	class RandomAccessIterator
	{
		public:
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef RandomAccessIterator<const T>	const_iterator;
			typedef ft::random_access_iterator_tag	iterator_category;

		private :
			pointer _p;

		public :
			RandomAccessIterator(void) : _p(NULL) {}
			RandomAccessIterator(pointer p) : _p(p) {}
			RandomAccessIterator(const RandomAccessIterator& src) { *this = src; }
			~RandomAccessIterator(void) {}

			RandomAccessIterator& operator=(const RandomAccessIterator& rhs)
			{
				_p = rhs._p;
				return *this;
			}

			operator RandomAccessIterator<const T>() const
			{
				return RandomAccessIterator<const T>(_p);
			}

			pointer	base() const { return _p; }

			reference	operator*(void) const { return *_p; }
			pointer		operator->(void) const { return _p; }

			RandomAccessIterator&	operator++( void )
			{
				++_p;
				return *this;
			}

			RandomAccessIterator	operator++( int )
			{
				return RandomAccessIterator(_p++);
			}

			RandomAccessIterator&	operator--( void )
			{
				--_p;
				return *this;
			}

			RandomAccessIterator	operator--( int )
			{
				return RandomAccessIterator(_p--);
			}

			RandomAccessIterator	operator+(const difference_type n) const { return RandomAccessIterator(_p + n); }
			RandomAccessIterator	operator-(const difference_type n) const { return RandomAccessIterator(_p - n); }
			difference_type	operator-(RandomAccessIterator rhs) const { return _p - rhs._p; }

			bool	operator==(const RandomAccessIterator& rhs) const { return _p == rhs._p; }
			bool	operator!=(const RandomAccessIterator& rhs) const { return _p != rhs._p; }
			bool	operator<(const RandomAccessIterator& rhs) const { return _p < rhs._p; }
			bool	operator>(const RandomAccessIterator& rhs) const { return _p > rhs._p; }
			bool	operator<=(const RandomAccessIterator& rhs) const { return _p <= rhs._p; }
			bool	operator>=(const RandomAccessIterator& rhs) const { return _p >= rhs._p; }

			RandomAccessIterator	operator+=(difference_type n)
			{
				_p += n;
				return *this;
			}

			RandomAccessIterator	operator-=(difference_type n)
			{
				_p -= n;
				return *this;
			}

			reference	operator[](size_t i) const { return _p[i]; }

	};	//class RandomAccessIterator

	template< class Iter >
	class RandomAccessIterator_reverse
	{
		public :
			typedef Iter								iterator_type;
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::const_iterator		const_Iter; //test
			typedef typename Iter::iterator_category	iterator_category;

		protected :
			Iter	current;

		public :
			RandomAccessIterator_reverse() : current(Iter()) {}
			RandomAccessIterator_reverse( iterator_type x ) : current(x) {}
			RandomAccessIterator_reverse( const RandomAccessIterator_reverse& src ) { *this = src; }
			~RandomAccessIterator_reverse() {}

			RandomAccessIterator_reverse& operator=(const RandomAccessIterator_reverse& rhs)
			{
				current = rhs.current;
				return *this;
			}

			operator RandomAccessIterator_reverse<const_Iter>() const
			{
				return RandomAccessIterator_reverse<const_Iter>(current);
			}

			pointer	base() const { return current.base(); }

			reference			operator*(void) const { return *current; }
			pointer				operator->(void) const { return current; }

			RandomAccessIterator_reverse&	operator++()
			{
				current--;
				return *this;
			}

			RandomAccessIterator_reverse	operator++( int )
			{
				return RandomAccessIterator_reverse(current--);
			}

			RandomAccessIterator_reverse&	operator--( void )
			{
				current++;
				return *this;
			}

			RandomAccessIterator_reverse	operator--( int )
			{
				return RandomAccessIterator_reverse(current++);
			}

			RandomAccessIterator_reverse	operator+( difference_type n ) const { return RandomAccessIterator_reverse(current - n); }
			RandomAccessIterator_reverse	operator-( difference_type n ) const { return RandomAccessIterator_reverse(current + n); }
			difference_type		operator-(RandomAccessIterator_reverse rhs) const { return current - rhs.current; }

			bool	operator==(const RandomAccessIterator_reverse& rhs) const { return current == rhs.current; }
			bool	operator!=(const RandomAccessIterator_reverse& rhs) const { return current != rhs.current; }
			bool	operator<(const RandomAccessIterator_reverse& rhs) const { return current < rhs.current; }
			bool	operator>(const RandomAccessIterator_reverse& rhs) const { return current > rhs.current; }
			bool	operator<=(const RandomAccessIterator_reverse& rhs) const { return current <= rhs.current; }
			bool	operator>=(const RandomAccessIterator_reverse& rhs) const { return current >= rhs.current; }

			RandomAccessIterator_reverse& operator+=( difference_type n )
			{
				current += n;
				return *this;
			}

			RandomAccessIterator_reverse& operator-=( difference_type n )
			{
				current -= n;
				return *this;
			}

			reference	operator[](size_t i) const { return *(current - i - 1); }

	}; // class RandomAccessIterator_reverse

	template <typename Node, typename T>
	class BidirectionalIterator
	{
		public:
			typedef Node*									node_ptr;
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef value_type*								pointer;
			typedef value_type&								reference;
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
				if (_p)
					_p = _p->next();
				else
					_p = _root->mini();
				return *this;
			}

			BidirectionalIterator	operator++(int)
			{
				BidirectionalIterator tmp(_p, _root);
				if (_p)
					_p = _p->next();
				else
					_p = _root->mini();
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

			bool	operator==(const BidirectionalIterator& rhs) const { return _p == rhs._p; }
			bool	operator!=(const BidirectionalIterator& rhs) const { return _p != rhs._p; }

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
			BidirectionalIterator_reverse( const Iter& src ) : _current(src) {}
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
			pointer		operator->( void ) const { return _current.operator->(); }

			BidirectionalIterator_reverse&	operator++( void ) { _current--; return *this; }
			BidirectionalIterator_reverse	operator++( int ) { return BidirectionalIterator_reverse(_current--); }
			BidirectionalIterator_reverse&	operator--( void ) { _current++; return *this; }
			BidirectionalIterator_reverse	operator--( int ) { return BidirectionalIterator_reverse(_current++); }

			bool	operator==( const BidirectionalIterator_reverse& rhs ) const { return _current == rhs._current; }
			bool	operator!=( const BidirectionalIterator_reverse& rhs ) const { return _current != rhs._current; }

	};	//class BidirectionalIterator_reverse

	template< class Iter >
	RandomAccessIterator_reverse<Iter>
	operator+( typename RandomAccessIterator_reverse<Iter>::difference_type n,
			   const RandomAccessIterator_reverse<Iter>& rhs )
	{
		return RandomAccessIterator_reverse<Iter>(n + rhs.base());
	}

	template <typename T>
	RandomAccessIterator<T>
	operator+( typename RandomAccessIterator<T>::difference_type lhs, 
			   const RandomAccessIterator<T>& rhs)
	{
		return RandomAccessIterator<T>(lhs + rhs[0]);
	}

	template< class InputIt >
	typename InputIt::difference_type
	distance (InputIt first, InputIt last)
	{
		typename InputIt::difference_type n = 0;

		while (first++ != last)
			n++;
		return n;
	}


}; // namespace ft

#endif
