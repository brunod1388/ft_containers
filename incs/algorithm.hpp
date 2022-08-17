/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/17 06:54:14 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{

	template< class InputIt1, class InputIt2 >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 )
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2!=last2);
	}

	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp )
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2!=last2);
	}

	template< class InputIt1, class InputIt2 >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
	{
		while(first1 != last1)
			if (*first1++ != *first2++)
				return false;
		return true;
	}

	template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
	{
		while(first1 != last1)
			if (!p(*first1++, *first2++))
				return false;
		return true;
	}

	template< class T >
	inline void swap( T& a, T& b )
	{
		T& c = a;

		a = b;
		b = c;
	}

} // namespace ft

#endif