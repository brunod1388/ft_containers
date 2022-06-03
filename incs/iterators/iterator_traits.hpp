/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 01:48:05 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/06/02 22:06:50 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP
#include <typeinfo>

namespace ft{

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

	template< class Iter >
	class reverse_iterator {

		public :
			typedef Iter												iterator_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_traits<Iter>::pointer				pointer;
			typedef typename iterator_traits<Iter>::reference			reference;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;

		protected :
			Iter	current;

		public :

			reverse_iterator() : current(Iter()) {}
			explicit reverse_iterator( iterator_type x ) : current(x) {}
			template< class U >
			reverse_iterator( const reverse_iterator<U>& other ) : current(other.current) {}

			reverse_iterator& operator=(const reverse_iterator& rhs)
			{
				current = rhs.current;
				return *this;
			}

			iterator_type base() const { return current; }

			reference			operator*(void) const { return *current; }
			pointer				operator->(void) const { return current; }

			reference			operator[](size_t i) const { return current[current - 1 - i]; }

			reverse_iterator&	operator++()
			{
				current--;
				return *this;
			}

			reverse_iterator	operator++( int )
			{
				reverse_iterator prev(current--);
				return prev;
			}

			reverse_iterator&	operator--(void)
			{
				current++;
				return *this;
			}

			reverse_iterator	operator--( int )
			{
				reverse_iterator prev(current++);
				return prev;
			}

			reverse_iterator	operator+( difference_type n ) const
			{
				return reverse_iterator(current - n);
			}

			reverse_iterator	operator-( difference_type n ) const
			{
				return reverse_iterator(current + n);
			}

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

	}; // reverse_iterator

	template< class Iter >
	reverse_iterator<Iter>
	operator+( typename reverse_iterator<Iter>::difference_type n,
			   const reverse_iterator<Iter>& it )
	{
		return reverse_iterator<Iter>(n + it);
	}

	template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type
	operator-( const reverse_iterator<Iterator>& lhs,
			   const reverse_iterator<Iterator>& rhs )
	{
		return rhs - lhs;
	}

	template< class Iter1, class Iter2 >
	bool operator==( const ft::reverse_iterator<Iter1>& lhs,
					 const ft::reverse_iterator<Iter2>& rhs )
	{
		return lhs.base() == rhs.base();
	}

	template< class Iter1, class Iter2 >
	bool operator!=( const ft::reverse_iterator<Iter1>& lhs,
					 const ft::reverse_iterator<Iter2>& rhs )
	{
		return lhs.base() != rhs.base();
	}

	template< class Iter1, class Iter2 >
	bool operator<( const ft::reverse_iterator<Iter1>& lhs,
					 const ft::reverse_iterator<Iter2>& rhs )
	{
		return lhs.base() < rhs.base();
	}

	template< class Iter1, class Iter2 >
	bool operator<=( const ft::reverse_iterator<Iter1>& lhs,
					 const ft::reverse_iterator<Iter2>& rhs )
	{
		return lhs.base() <= rhs.base();
	}

	template< class Iter1, class Iter2 >
	bool operator>( const ft::reverse_iterator<Iter1>& lhs,
					 const ft::reverse_iterator<Iter2>& rhs )
	{
		return lhs.base() > rhs.base();
	}

	template< class Iter1, class Iter2 >
	bool operator>=( const ft::reverse_iterator<Iter1>& lhs,
					 const ft::reverse_iterator<Iter2>& rhs )
	{
		return lhs.base() >= rhs.base();
	}

	// // TO DO LATER
	template< class InputIt >
	typename iterator_traits<InputIt>::difference_type
	distance (InputIt first, InputIt last)
	{
		if (typeid(typename iterator_traits<InputIt>::iterator_category)
			== typeid(random_access_iterator_tag))
			return last - first;                            //maybe better with enable_if to choose
		typename iterator_traits<InputIt>::difference_type n = 0;
		while (first++ != last)
			n++;
		return n;
	}

	template <class InputIt, class Distance>
	void advance (InputIt& it, Distance n)
	{
		if (typeid(typename iterator_traits<InputIt>::iterator_category)
			== typeid(random_access_iterator_tag))
			it += n;
		else
			while (n--)
				it++;
	}
}; // namespace ft

#endif
