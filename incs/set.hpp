/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:44:04 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/17 08:37:55 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include "RBTree.hpp"

namespace ft
{
	template<
		class Key,
		class Compare = ft::less<Key>,
		class Allocator = std::allocator<Key> >
	class set : public ft::_RBTree<Key, Compare, Allocator>
	{
	private:
		typedef ft::_RBTree<Key, Compare, Allocator>	Base;
	public:

		typedef Compare                                 key_compare;
		typedef Key			                            key_type;

		// set() : Base() {}
		explicit set( const Compare& comp = key_compare(),
					  const Allocator& alloc = Allocator()) :
			Base(Compare(comp), alloc)
		{}

		template< class InputIt >
		set( InputIt first, InputIt last,
			const Compare& comp = Compare(),
			const Allocator& alloc = Allocator() ) :
			Base(first, last, comp, alloc)
		{}

		set( const set& other ) : Base(other) {}

		~set(void) {}

		set&	operator=(const set& rhs) { *this = rhs; return *this;}

		key_compare		value_comp() const { return this->_comp; }

	};	// class set

}	//namespace ft

#endif
