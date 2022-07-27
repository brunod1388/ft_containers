/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/07/28 01:18:55 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft{

	template <typename T>
	class vector_iterator
	{
		public:
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef vector_iterator<const T>		const_iterator; // test
			typedef ft::random_access_iterator_tag	iterator_category;

		private :
			pointer _p;

		public :
			vector_iterator(void) : _p(NULL) {}
			vector_iterator(pointer p) : _p(p) {}
			vector_iterator(const vector_iterator& src) { *this = src; }
			~vector_iterator(void) {}

			vector_iterator& operator=(const vector_iterator& rhs)
			{
				_p = rhs._p;
				return *this;
			}

			operator vector_iterator<const T>() const
			{
				return vector_iterator<const T>(_p);
			}

			pointer	base() const { return _p; }

			reference	operator*(void) const { return *_p; }
			pointer		operator->(void) const { return _p; }

			vector_iterator&	operator++( void )
			{
				++_p;
				return *this;
			}

			vector_iterator	operator++( int )
			{
				return vector_iterator(_p++);
			}

			vector_iterator&	operator--( void )
			{
				--_p;
				return *this;
			}

			vector_iterator	operator--( int )
			{
				return vector_iterator(_p--);
			}

			vector_iterator	operator+(const difference_type n) const { return vector_iterator(_p + n); }
			vector_iterator	operator-(const difference_type n) const { return vector_iterator(_p - n); }
			difference_type	operator-(vector_iterator rhs) const { return _p - rhs._p; }

			bool	operator==(const vector_iterator rhs) const { return _p == rhs._p; }
			bool	operator!=(const vector_iterator rhs) const { return _p != rhs._p; }
			bool	operator<(const vector_iterator rhs) const { return _p < rhs._p; }
			bool	operator>(const vector_iterator rhs) const { return _p > rhs._p; }
			bool	operator<=(const vector_iterator rhs) const { return _p <= rhs._p; }
			bool	operator>=(const vector_iterator rhs) const { return _p >= rhs._p; }

			vector_iterator	operator+=(difference_type n)
			{
				_p += n;
				return *this;
			}

			vector_iterator	operator-=(difference_type n)
			{
				_p -= n;
				return *this;
			}

			reference	operator[](size_t i) const { return _p[i]; }

	};	//class vector_iterator

	template< class Iter >
	class reverse_iterator
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
			reverse_iterator() : current(Iter()) {}
			reverse_iterator( iterator_type x ) : current(x) {}
			reverse_iterator( const reverse_iterator& src ) { *this = src; }
			~reverse_iterator() {}

			reverse_iterator& operator=(const reverse_iterator& rhs)
			{
				current = rhs.current;
				return *this;
			}

			operator reverse_iterator<const_Iter>() const
			{
				return reverse_iterator<const_Iter>(current);
			}

			iterator_type	base() const { return current; }

			reference			operator*(void) const { return *current; }
			pointer				operator->(void) const { return current; }

			reverse_iterator&	operator++()
			{
				current--;
				return *this;
			}

			reverse_iterator	operator++( int )
			{
				return reverse_iterator(current--);
			}

			reverse_iterator&	operator--( void )
			{
				current++;
				return *this;
			}

			reverse_iterator	operator--( int )
			{
				return reverse_iterator(current++);
			}

			reverse_iterator	operator+( difference_type n ) const { return reverse_iterator(current - n); }
			reverse_iterator	operator-( difference_type n ) const { return reverse_iterator(current + n); }
			difference_type		operator-(reverse_iterator rhs) const { return current - rhs.current; }

			bool	operator==(const reverse_iterator rhs) const { return current == rhs.current; }
			bool	operator!=(const reverse_iterator rhs) const { return current != rhs.current; }
			bool	operator<(const reverse_iterator rhs) const { return current < rhs.current; }
			bool	operator>(const reverse_iterator rhs) const { return current > rhs.current; }
			bool	operator<=(const reverse_iterator rhs) const { return current <= rhs.current; }
			bool	operator>=(const reverse_iterator rhs) const { return current >= rhs.current; }

			reverse_iterator& operator+=( difference_type n )
			{
				current += n;
				return *this;
			}

			reverse_iterator& operator-=( difference_type n )
			{
				current -= n;
				return *this;
			}

			reference			operator[](size_t i) const { return *(current - i - 1); }

	}; // class reverse_iterator

	template< class Iter >
	reverse_iterator<Iter>
	operator+( typename reverse_iterator<Iter>::difference_type n,
			   const reverse_iterator<Iter>& rhs )
	{
		return reverse_iterator<Iter>(n + rhs.base());
	}

	template <typename T>
	vector_iterator<T>
	operator+( typename vector_iterator<T>::difference_type lhs, 
			   const vector_iterator<T>& rhs)
	{
		return vector_iterator<T>(lhs + rhs[0]);
	}

};	//namespace ft

#endif