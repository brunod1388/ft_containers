/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/07/28 01:18:55 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_ITERATOR_HPP
# define RANDOMACCESSITERATOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft{

	template <typename T>
	class RandomAccessIterator
	{
		public:
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef RandomAccessIterator<const T>		const_iterator; // test
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

			bool	operator==(const RandomAccessIterator rhs) const { return _p == rhs._p; }
			bool	operator!=(const RandomAccessIterator rhs) const { return _p != rhs._p; }
			bool	operator<(const RandomAccessIterator rhs) const { return _p < rhs._p; }
			bool	operator>(const RandomAccessIterator rhs) const { return _p > rhs._p; }
			bool	operator<=(const RandomAccessIterator rhs) const { return _p <= rhs._p; }
			bool	operator>=(const RandomAccessIterator rhs) const { return _p >= rhs._p; }

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

			iterator_type	base() const { return current; }

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

			bool	operator==(const RandomAccessIterator_reverse rhs) const { return current == rhs.current; }
			bool	operator!=(const RandomAccessIterator_reverse rhs) const { return current != rhs.current; }
			bool	operator<(const RandomAccessIterator_reverse rhs) const { return current < rhs.current; }
			bool	operator>(const RandomAccessIterator_reverse rhs) const { return current > rhs.current; }
			bool	operator<=(const RandomAccessIterator_reverse rhs) const { return current <= rhs.current; }
			bool	operator>=(const RandomAccessIterator_reverse rhs) const { return current >= rhs.current; }

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

			reference			operator[](size_t i) const { return *(current - i - 1); }

	}; // class RandomAccessIterator_reverse

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

};	//namespace ft

#endif