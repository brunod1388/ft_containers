/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 01:48:05 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/07/28 01:17:46 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP
#include <typeinfo>
#include <cstddef>

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



	template< class InputIt >
	typename InputIt::difference_type
	distance (InputIt first, InputIt last)
	{
		typename InputIt::difference_type n = 0;

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
