/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/07/28 00:48:39 by brunodeoliv      ###   ########.fr       */
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

			pointer	base() const { return _p; }

			reference	operator*(void) const { return *_p; }
			pointer		operator->(void) const { return _p; }

			operator vector_iterator<const T>() const
			{
				return vector_iterator<const T>(_p);
			}

			vector_iterator&	operator++(void)
			{
				++_p;
				return *this;
			}

			vector_iterator	operator++(int)
			{
				return vector_iterator(_p++);
			}

			vector_iterator&	operator--(void)
			{
				--_p;
				return *this;
			}

			vector_iterator	operator--(int)
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

	template <typename T>
	vector_iterator<T>	operator+(typename vector_iterator<T>::difference_type lhs, const vector_iterator<T>& rhs)
	{
		return vector_iterator<T>(lhs + rhs[0]);
	}

};	//namespace ft

#endif