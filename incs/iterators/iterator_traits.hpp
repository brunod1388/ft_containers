/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 01:48:05 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/05/31 04:29:19 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

namespace ft{

	template <class T>
	class iterator_traits{

	public :
		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef std::random_access_iterator_tag			iterator_category;

	private :
		pointer _p;
		iterator_traits() : _p(NULL) {}
		
	public :
		iterator_traits(pointer p) : _p(p) {}
		iterator_traits(const iterator_traits &ItT) : _p(ItT._p) {}
		~iterator_traits();

		iterator_traits& operator=(const iterator_traits& rhs)
		{
			_p = rhs._p;
			return *this;
		}

		bool	operator==(const iterator_traits& rhs) { return _p == rhs._p; }
		bool	operator!=(const iterator_traits& rhs) { return _p != rhs._p; }

		reference	operator*(void) const { return *_p; }
		pointer		operator->(void) const { return _p; }

		reference	operator++(void) { return *(++_p); }
		value_type	operator++(int) { return *_p++; }  //a tester

		reference	operator--(void) { return *(--_p); }
		value_type	operator--(int) { return *_p--; }  //a tester

		iterator_traits	operator+(difference_type n) { return iterator_traits(_p + n); }
		iterator_traits	operator-(difference_type n) { return iterator_traits(_p - n); }
		iterator_traits	operator-(iterator_traits rhs) { return iterator_traits(_p - rhs._p); }

		bool	operator<(const iterator_traits& rhs) { return _p < rhs._p; }
		bool	operator>(const iterator_traits& rhs) { return _p > rhs._p; }
		bool	operator<=(const iterator_traits& rhs) { return _p <= rhs._p; }
		bool	operator>=(const iterator_traits& rhs) { return _p >= rhs._p; }

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


	};	//class iterator_traits

	template <typename T>
	iterator_traits<T>	operator-(typename iterator_traits<T>::difference_type lhs, const iterator_traits<T>& rhs)
	{
		return iterator_traits<T>(lhs + &rhs[0]);
	}



	// TO DO LATER
	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last);

	template <class InputIterator, class Distance>
	void advance (InputIterator& it, Distance n);
}; // namespace ft

#endif
