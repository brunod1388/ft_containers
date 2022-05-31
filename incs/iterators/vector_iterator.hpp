/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/05/31 04:27:17 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP
#include "iterator_traits.hpp"


namespace ft{

	template <typename T>
	class vector_iterator {

	public:
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;

	private :
		pointer _p;
		vector_iterator(void) : _p(NULL) {}

	public :
		vector_iterator(pointer p) : _p(p) {}
		vector_iterator(const vector_iterator& src) { *this = src; }
		vector_iterator(T &p) : _p(p) {}
		~vector_iterator(void) {}

		vector_iterator& operator=(const vector_iterator& rhs)
		{
			_p = rhs._p;
			return *this;
		}

		bool	operator==(const vector_iterator& rhs) { return _p == rhs._p; }
		bool	operator!=(const vector_iterator& rhs) { return _p != rhs._p; }

		reference	operator*(void) const { return *_p; }
		pointer		operator->(void) const { return _p; }

		reference	operator++(void) { return *(++_p); }
		value_type	operator++(int) { return *_p++; }  //a tester

		reference	operator--(void) { return *(--_p); }
		value_type	operator--(int) { return *_p--; }  //a tester

		vector_iterator	operator+(difference_type n) { return vector_iterator(_p + n); }
		vector_iterator	operator-(difference_type n) { return vector_iterator(_p - n); }
		vector_iterator	operator-(vector_iterator rhs) { return vector_iterator(_p - rhs._p); }

		bool	operator<(const vector_iterator& rhs) { return _p < rhs._p; }
		bool	operator>(const vector_iterator& rhs) { return _p > rhs._p; }
		bool	operator<=(const vector_iterator& rhs) { return _p <= rhs._p; }
		bool	operator>=(const vector_iterator& rhs) { return _p >= rhs._p; }

		reference	operator+=(difference_type n)
		{
			_p += n;
			return *this;
		}

		reference	operator-=(difference_type n)
		{
			_p -= n;
			return *this;
		}

		reference	operator[](size_t i) const { return _p[i]; }

	};	//class vector_iterator

	template <typename T>
	vector_iterator<T>	operator-(typename vector_iterator<T>::difference_type lhs, const vector_iterator<T>& rhs)
	{
		return vector_iterator<T>(lhs + rhs[0]);
	}

};	//namespace ft


#endif